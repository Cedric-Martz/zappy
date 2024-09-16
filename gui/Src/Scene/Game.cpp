/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** MainMenu
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include "Game.hpp"
#include "Factory.hpp"
#include "SceneManager.hpp"
#include "Cube.hpp"
#include "MainMenu.hpp"
#include "NetworkManager.hpp"
#include "ArgumentParser.hpp"
#include "Vector.hpp"
#include "Pause.hpp"
#include "SettingsValue.hpp"

namespace rl
{
    Game::Game()
        : _camera(std::make_shared<Camera3>(Vector3{-26.9f, 69.4f, 38.0f},
                                            Vector3{-24.3f, 66.1f, 38.1f},
                                            Vector3{0.0f, 1.0f, 0.0f},
                                            60.0f,
                                            CAMERA_PERSPECTIVE)),
        _speed(1),
        _mapSize({0, 0}),
        _bctCount(0),
        _lastMct(std::chrono::steady_clock::now()),
        _levels{},
        _canMove(true)
    {
        NetworkManager &network = NetworkManager::getInstance();
        AudioManager &audio = AudioManager::getInstance();
        ArgumentParser &parser = ArgumentParser::getInstance();
        RenderWindow &window = RenderWindow::getInstance();
        TextureManager &texture = TextureManager::getInstance();

        _villagerTextures = {
            "Assets/Models/villager/textures/villager.png",
            "Assets/Models/villager/textures/farmer.png",
            "Assets/Models/villager/textures/shepherd.png",
            "Assets/Models/villager/textures/butcher.png",
            "Assets/Models/villager/textures/smith.png",
            "Assets/Models/villager/textures/librarian.png",
            "Assets/Models/villager/textures/priest.png"
        };

        if (!parser.getPort().empty())
            network.setPort(std::stoi(parser.getPort()));
        std::string bin;
        network >> bin;
        network.init();
        _camera->setMode(CAMERA_FIRST_PERSON);

        float near = 0.1f;
        float aspect = 16.0f / 9.0f;
        float top = near * tanf(_camera->getSource().fovy * 0.5f * DEG2RAD);
        _camera->setMatrixUtils(
            near,
            10000000.0f,
            aspect,
            top,
            top * aspect
        );

        // _sky.loadConfig(1000, 10000.0f, 50.0f, {0, 0, 0}, {100, 1000}, 0.0125f, _camera, true, 8);
        _sky.loadConfig(1000, 2000000.0f, 50.0f, {0, 0, 0}, {10000, 100000}, 0.0125f, _camera);

        audio.loadSound("Assets/Sounds/Salut_les_teks.mp3", "salut_les_teks");
        audio.loadSound("Assets/Sounds/enderdragon.mp3", "enderdragon");
        audio.loadSound("Assets/Sounds/achievement.mp3", "achievement");
        audio.loadSound("Assets/Sounds/orb.mp3", "orb");
        audio.loadSound("Assets/Sounds/happy_wheels_victory.mp3", "victory");
        audio.playJukebox(*this);

        addText(
            "speed",
            "Speed: " + std::to_string(_speed),
            20,
            WHITE,
            {80, window.getSize().y - 170}
        );
        addButton(
            "IncrementSpeedButton",
            {160, window.getSize().y - 115},
            {60, 60},
            WHITE,
            [&]() {
                _speed += 10;
                std::string speedStr = std::to_string(_speed);
                getElement<Text>("speed")->setString("Speed: " + speedStr);
                network << "sst " + speedStr + "\n";
            },
            "Assets/Imgs/buttons/buttonPlus.png",
            "Assets/Imgs/buttons/hoverPlus.png"
        );
        addButton(
            "DecreaseSpeedButton",
            {75, window.getSize().y - 115},
            {60, 60},
            WHITE,
            [&]() {
                if (_speed > 1) {
                    _speed -= 10;
                    std::string speedStr = std::to_string(_speed);
                    getElement<Text>("speed")->setString("Speed: " + speedStr);
                    network << "sst " + speedStr + "\n";
                }
            },
            "Assets/Imgs/buttons/buttonMinus.png",
            "Assets/Imgs/buttons/hoverMinus.png"
        );

        addText(
            "toggleResourcesButtonText",
            "Toggle tile info = OFF",
            20,
            WHITE,
            {20, window.getSize().y - 280}
        );
        getElement<Text>("toggleResourcesButtonText")->setCenterState(false);
    addButton(
            "toggleResourcesHoverButton",
            {75, window.getSize().y - 220},
            {60, 60},
            WHITE,
            [&]() {
                _tiles.toggleTextDisplay();
                getElement<Text>("toggleResourcesButtonText")->setString(std::string("Toggle tile info = ") + (_tiles.geTextDisplayState() ? "ON" : "OFF"));
            },
            "Assets/Imgs/buttons/buttonInfo.png",
            "Assets/Imgs/buttons/hoverInfo.png"
        );

        for (int i = 0; i < 7; ++i)
            _nbRessources[static_cast<ItemType>(i)] = 0;

        addText(
            "mapInfoDisplay",
            "Display map informations = ON",
            20,
            WHITE,
            {20, window.getSize().y - 380}
        );
        getElement<Text>("mapInfoDisplay")->setCenterState(false);
        addButton(
            "mapInfoButton",
            {75, window.getSize().y - 320},
            {60, 60},
            WHITE,
            [&]() {
                for (auto &[key, _] : _nbRessources) {
                    std::shared_ptr<Text> text = getElement<Text>(Inventory::itemToStr(key) + "_count");
                    text->setDisplayed(!text->getDisplayed());
                }
                for (int i = 0; i < 8; ++i) {
                    std::shared_ptr<Text> text = getElement<Text>(std::string("level_") + std::to_string(i + 1));
                    text->setDisplayed(!text->getDisplayed());
                }
                getElement<Text>("mapInfoDisplay")->setString(std::string("Display map informations = ") + (getElement<Text>("level_1")->getDisplayed() ? "ON" : "OFF"));
            },
            "Assets/Imgs/buttons/buttonMap.png",
            "Assets/Imgs/buttons/hoverMap.png"
        );

        addText(
            "mapSize",
            "Map size: ? x ?",
            20,
            WHITE,
            {window.getSize().x - 120, 20}
        );

        addText(
            "Food_count",
            "Food: 0",
            20,
            WHITE,
            {window.getSize().x - 500, window.getSize().y - 240}
        );
        addText(
            "Linemate_count",
            "Linemate: 0",
            20,
            WHITE,
            {window.getSize().x - 500, window.getSize().y - 220}
            );
        addText(
            "Deraumere_count",
            "Deraumere: 0",
            20,
            WHITE,
            {window.getSize().x - 500, window.getSize().y - 200}
            );
        addText(
            "Sibur_count",
            "Sibur: 0",
            20,
            WHITE,
            {window.getSize().x - 500, window.getSize().y - 180}
            );
        addText(
            "Mendiane_count",
            "Mendiane: 0",
            20,
            WHITE,
            {window.getSize().x - 500, window.getSize().y - 160}
            );
        addText(
            "Phiras_count",
            "Phiras: 0",
            20,
            WHITE,
            {window.getSize().x - 500, window.getSize().y - 140}
            );
        addText(
            "Thystame_count",
            "Thystame: 42",
            20,
            WHITE,
            {window.getSize().x - 500, window.getSize().y - 120}
            );
        addText(
            "level_1",
            "Level 1: 0",
            20,
            WHITE,
            {window.getSize().x - 200, window.getSize().y - 260}
            );
        addText(
            "level_2",
            "Level 2: 0",
            20,
            WHITE,
            {window.getSize().x - 200, window.getSize().y - 240}
            );
        addText(
            "level_3",
            "Level 3: 0",
            20,
            WHITE,
            {window.getSize().x - 200, window.getSize().y - 220}
            );
        addText(
            "level_4",
            "Level 4: 0",
            20,
            WHITE,
            {window.getSize().x - 200, window.getSize().y - 200}
            );
        addText(
            "level_5",
            "Level 5: 0",
            20,
            WHITE,
            {window.getSize().x - 200, window.getSize().y - 180}
            );
        addText(
            "level_6",
            "Level 6: 0",
            20,
            WHITE,
            {window.getSize().x - 200, window.getSize().y - 160}
            );
        addText(
            "level_7",
            "Level 7: 0",
            20,
            WHITE,
            {window.getSize().x - 200, window.getSize().y - 140}
        );
        addText(
            "level_8",
            "Level 8: 0",
            20,
            WHITE,
            {window.getSize().x - 200, window.getSize().y - 120}
        );

        getElement<Text>("Food_count")->setCenterState(false);
        getElement<Text>("Linemate_count")->setCenterState(false);
        getElement<Text>("Deraumere_count")->setCenterState(false);
        getElement<Text>("Sibur_count")->setCenterState(false);
        getElement<Text>("Mendiane_count")->setCenterState(false);
        getElement<Text>("Phiras_count")->setCenterState(false);
        getElement<Text>("Thystame_count")->setCenterState(false);
        getElement<Text>("level_1")->setCenterState(false);
        getElement<Text>("level_2")->setCenterState(false);
        getElement<Text>("level_3")->setCenterState(false);
        getElement<Text>("level_4")->setCenterState(false);
        getElement<Text>("level_5")->setCenterState(false);
        getElement<Text>("level_6")->setCenterState(false);
        getElement<Text>("level_7")->setCenterState(false);
        getElement<Text>("level_8")->setCenterState(false);

        const float planetSize = 10000.0f;
        const Vector3 pos(0.0f, -planetSize, 0.0f);

        audio.loadSpeaker("Assets/Musics/Maxwell/maxwell.mp3", "maxwell", pos);
        addPlanet(
            "trantor",
            "Assets/Imgs/planets/textures/Planet_barren_baseColor.png",
            pos,
            planetSize,
            WHITE,
            _camera
        );
        std::shared_ptr<Planet> trantor = getElement<Planet>("trantor");
        trantor->adjust();
        trantor->setTextureRotating(false);

        Vector3 maxwellPos(0.0f, -planetSize, 0.0f);

        audio.loadSpeaker("Assets/Musics/Maxwell/maxwell.mp3", "maxwell0", pos);
        std::shared_ptr<Planet> moon0 = Factory::createElement<Planet>(
            "moon0",
            "Assets/Models/maxwell/scene.obj",
            maxwellPos,
            100.0f,
            WHITE,
            _camera,
            planetSize * 1.5f,
            0.25f,
            StellarObject::OrbitAxis::Z
        );
        std::shared_ptr<Planet> sun = Factory::createElement<Planet>(
                "sun",
                Vector3{0.0f, 0.0f, 0.0f},
                100000.0f,
                ORANGE,
                _camera,
                planetSize * 50.0f,
                0.1f
        );
        moon0->updateModelTexture(texture.loadTexture("Assets/Models/maxwell/textures/maxwell.png"));
        moon0->setTextureRotationSpeed(500.0f);
        trantor->addSatellite(moon0, trantor);
        trantor->addSatellite(sun, trantor);

        Vector2 ws = window.getSize();
        float wsx = ws.x;
        float wsy = ws.y;
        float wsf = wsx;

        SettingsValue &settings = SettingsValue::getInstance();
        addInputText(
            "adminInput",
            {0.5f * wsx, 0.9f * wsy, 0.3125f * wsx, 0.0694f * wsy - 30},
            20,
            0.0234f * wsf,
            LIGHTGRAY,
            "",
            "",
            [&](Text &input, size_t &cursorPos) {
                std::string command = input.getString();
                if (command.empty())
                    return;
                NetworkManager::getInstance() << (command + "\n");
                input.setString("");
                cursorPos = 0;
            },
            [&]() {
                _canMove = false;
            },
            [&]() {
                _canMove = true;
            }
        );
        addText("adminCommandResultText", settings.getLastAdminResult(), 20, WHITE, {0.5f * wsx, 0.85f * wsy});

        const float coeffSpeed = 2.0f;

        addSatellite(
            "continental",
            sun,
            "Assets/Imgs/planets/textures/Planet_continental_baseColor.png",
            {0.0f, 0.0f, 0.0f},
            20000.0f,
            WHITE,
            _camera,
            300000.0f,
            0.1f * coeffSpeed
        );
        sun->getSatellite("continental")->adjust();

        addSatellite(
            "frozen",
            sun,
            "Assets/Imgs/planets/textures/Planet_frozen_baseColor.png",
            {0.0f, 0.0f, 0.0f},
            28000.0f,
            WHITE,
            _camera,
            900000.0f,
            0.01f * coeffSpeed
        );
        sun->getSatellite("frozen")->adjust();

        addSatellite(
            "gas",
            sun,
            "Assets/Imgs/planets/textures/Planet_gas_baseColor.png",
            {0.0f, 0.0f, 0.0f},
            20000.0f,
            WHITE,
            _camera,
            200000.0f,
            0.12f * coeffSpeed
        );
        sun->getSatellite("gas")->adjust();

        addSatellite(
            "lava",
            sun,
            "Assets/Imgs/planets/textures/Planet_lava_baseColor.png",
            {0.0f, 0.0f, 0.0f},
            50000.0f,
            WHITE,
            _camera,
            500000.0f,
            0.06f * coeffSpeed
        );
        sun->getSatellite("lava")->adjust();

        addSatellite(
            "smac",
            sun,
            "Assets/Imgs/planets/textures/Planet_smac_baseColor.png",
            {0.0f, 0.0f, 0.0f},
            20000.0f,
            WHITE,
            _camera,
            700000.0f,
            0.2f * coeffSpeed
        );
        sun->getSatellite("smac")->adjust();

        addSatellite(
                "smacMoon",
                sun->getSatellite("frozen"),
                {0.0f, 0.0f, 0.0f},
                7500.0f,
                GRAY,
                _camera,
                70000.0f,
                0.5f * coeffSpeed
        );
        sun->getSatellite("frozen")->getSatellite("smacMoon")->adjust();
    }

    Game::~Game()
    {
        NetworkManager::getInstance().stop();
    }

    std::string Game::getId() const
    {
        return "GameScene";
    }

    std::shared_ptr<Camera3> &Game::getCamera()
    {
        return _camera;
    }

    void Game::events()
    {
        SetExitKey(KEY_NULL);

        if (Keyboard::getInstance().isKeyPressed(KeyboardKey::KEY_ESCAPE)) {
            TakeScreenshot("MenuBackground.png");
            SceneManager::getInstance().setTransitionSpeed(1.0f);
            SceneManager::getInstance().pushScene(std::unique_ptr<Pause>(new Pause()));
        }
    }

    void Game::updateMapValues()
    {
        for (auto &[key, value] : _nbRessources)
            value = 0;

        for (float y = 0; y < _mapSize.y; y++) {
            for (float x = 0; x < _mapSize.x; x++) {
                std::shared_ptr<rl::Tile>tile = getTiles().getTile({x * 10, y * 10});
                for (auto &[key, value] : _nbRessources)
                    value += tile->getResources(key);
            }
        }

        for (auto &[key, value] : _nbRessources)
            getElement<Text>(Inventory::itemToStr(key) + "_count")->setString(Inventory::itemToStr(key) + ": " + std::to_string(value));

        _levels.fill(0);

        for (auto &[_, player] : _players) {
            int level = player->getLevel() - 1;
            for (int i = 0; i < 8; i++)
                if (i == level)
                    _levels[i]++;
        }

        for (size_t i = 1; i <= 8; ++i)
            getElement<Text>(std::string("level_") + std::to_string(i))->setString(std::string("Level ") + std::to_string(i) + ": " + std::to_string(_levels[i - 1]));
    }

    void Game::update(double deltaTime)
    {
        AudioManager &audio = AudioManager::getInstance();
        NetworkManager &network = NetworkManager::getInstance();
        Clock::getInstance().updateDeltaTime().asSeconds();

        audio.updateJukebox(*this);

        network.init();

        for (auto &[teamNameStr, element] : _elements) {
            element->update(deltaTime);
            if (teamNameStr.starts_with("team;"))
                displayPlayerBoundingBoxByTeamName(teamNameStr);
        }

        getElement<Text>("adminCommandResultText")->setString(SettingsValue::getInstance().getLastAdminResult());

        updateCamera3(deltaTime);

        updateNotifications();

        network.readSocketInput(*this);

        for (auto &[_, player] : _players)
            player->update(deltaTime);

        updateMapValues();

        if (_players.size() != 0) {
            static const std::array<std::string, 3> pCommands = {"ppo ", "plv ", "pin "};
            for (auto &[_, player] : _players) {
                if (!player->getServerResponseFlag()) {
                    player->setServerResponseFlag(true);
                    std::string command{};
                    for (auto &c : pCommands)
                        command += c + player->getId() + "\n";
                    network << command;
                }
            }
        }

        audio.setSpeakerPosition("maxwell0", getElement<Planet>("trantor")->getSatellite("moon0")->getTransformedPosition());
        audio.updateSpeakers(_camera->getSource().position, 15000.0f);

        if (_bctCount > _mapSize.x * (_mapSize.y - 1)) {
            auto currentTime = std::chrono::steady_clock::now();
            auto timeSinceLastMct = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastMct);

            if (timeSinceLastMct >= SettingsValue::getInstance().getTileRefreshInterval()) {
                if (_players.size() != 0)
                    _bctCount = 0;
                network << "mct\n";
                _lastMct = currentTime;
                for (auto &[key, player] : _players)
                    player->setServerResponseFlag(false);
            }
        }

        _tiles.update(deltaTime);
        _sky.update(deltaTime);
    }

    void Game::renderStackedElems()
    {
        std::unordered_map<Vector2, float> stackedOffsets{};

        for (auto &[_, player] : _players) {
            Vector3 playerPos = player->getPosition3();
            float playerY = playerPos.y;
            if (stackedOffsets.contains({playerPos.x, playerPos.z})) {
                playerPos.y += stackedOffsets[{playerPos.x, playerPos.z}];
                player->setPosition({playerPos});
                stackedOffsets[{playerPos.x, playerPos.z}] += player->getSize().y;
            } else {
                stackedOffsets[{playerPos.x, playerPos.z}] = player->getSize().y;
            }
            player->draw();
            playerPos.y = playerY;
            player->setPosition(playerPos);
        }

        for (auto &[_, egg] : _eggs) {
            Vector3 eggPos = egg->getPosition3();
            float eggY = eggPos.y;
            if (stackedOffsets.contains({eggPos.x, eggPos.z})) {
                eggPos.y += stackedOffsets[{eggPos.x, eggPos.z}];
                egg->setPosition({eggPos});
                stackedOffsets[{eggPos.x, eggPos.z}] += egg->getSize().y * 2.0f;
            } else {
                stackedOffsets[{eggPos.x, eggPos.z}] = egg->getSize().y * 2.0f;
            }
            egg->draw();
            eggPos.y = eggY;
            egg->setPosition(eggPos);
        }
    }

    void Game::render()
    {
        RenderWindow::getInstance().clear(BLACK);
        {
            Scoped scoped(_camera);
            for (auto &[_, element] : _elements) {
                if (!element->getDisplayed())
                    continue;
                if (element->getDimension() == VisualElement::Dimension::DIMENSION3)
                    element->draw();
            }

            renderStackedElems();

            _tiles.render();
            _sky.draw();
        }
        for (auto &[_, element] : _elements) {
            if (!element->getDisplayed())
                continue;
            if (element->getDimension() == VisualElement::Dimension::DIMENSION2)
                element->draw();
        }

        for (auto &[_, element] : _players) {
            if (element->isClicked()) {
                element->drawInventory();
                break;
            }
        }

        _tiles.renderText(*_camera);

        getNotification();
        DrawFPS(10, 10);
    }

    void Game::sendNotification(const std::string &title, const std::string &message)
    {
        if (_notifications.size() >= 6)
            _notifications.pop_front();
        Notification notification = Notification(Vector2(0, 0), title, message);
        _notifications.push_back(notification);
    }

    void Game::getNotification()
    {
        for (Notification &notification : _notifications) {
            if (notification.getTimeBank() <= 3.8f) {
                notification.draw(notification.getPosition());
            } else {
                Notification tmp = _notifications.front();
                _notifications.pop_front();
                for (Notification &notification2 : _notifications)
                    notification2.setPosition(Vector2(notification2.getPosition().x, notification2.getPosition().y - tmp.getPosition().y));
            }
        }
    }

    void Game::updateNotifications()
    {
        RenderWindow &window = RenderWindow::getInstance();
        size_t index = 0;

        for (Notification &notification : _notifications) {
            Vector2 position = {window.getSize().x - 330, 0};
            position.y = 120 + (130 * index);

            float timeBank = notification.getTimeBank();
            if (timeBank >= 3.5)
                position.y -= 300 * (timeBank - 3.5);
            notification.setPosition(position);
            notification.update();
            ++index;
        }
    }

    void Game::updateCamera3(float deltaTime)
    {
        if (!_canMove)
            return;

        Keyboard &k = Keyboard::getInstance();
        SettingsValue &settings = SettingsValue::getInstance();
        std::unordered_map<std::string, int> keys = settings.getKeyBind();
        Camera3D &camera = _camera->getSource();

        float moveSpeed = SettingsValue::getInstance().getMoveSpeed() * deltaTime;
        float rotateSpeed = 2.0f * deltaTime;

        Vector3 direction = Vector3Normalize(camera.target - camera.position);

        if (k.isKeyDown(static_cast<KeyboardKey>(keys["downKey"]))) {
            camera.position = camera.position + direction * -moveSpeed;
            camera.target = camera.target + direction * -moveSpeed;
        }
        if (k.isKeyDown(static_cast<KeyboardKey>(keys["upKey"]))) {
            camera.position = camera.position + direction * moveSpeed;
            camera.target = camera.target + direction * moveSpeed;
        }

        Vector3 right = Vector3Normalize(Vector3CrossProduct(direction, camera.up));

        if (k.isKeyDown(static_cast<KeyboardKey>(keys["leftKey"]))) {
            camera.position = camera.position + right * -moveSpeed;
            camera.target = camera.target + right * -moveSpeed;
        }
        if (k.isKeyDown(static_cast<KeyboardKey>(keys["rightKey"]))) {
            camera.position = camera.position + right * moveSpeed;
            camera.target = camera.target + right * moveSpeed;
        }

        if (k.isKeyDown(KEY_SPACE)) {
            camera.position.y += moveSpeed;
            camera.target.y += moveSpeed;
        }
        if (k.isKeyDown(KEY_LEFT_CONTROL)) {
            camera.position.y -= moveSpeed;
            camera.target.y -= moveSpeed;
        }

        Quaternion rotation = QuaternionIdentity();

        if (k.isKeyDown(static_cast<KeyboardKey>(keys["downCam"]))) {
            Quaternion pitch = QuaternionFromAxisAngle(right, -rotateSpeed);
            rotation = QuaternionMultiply(rotation, pitch);
        }
        if (k.isKeyDown(static_cast<KeyboardKey>(keys["upCam"]))) {
            Quaternion pitch = QuaternionFromAxisAngle(right, rotateSpeed);
            rotation = QuaternionMultiply(rotation, pitch);
        }

        if (k.isKeyDown(static_cast<KeyboardKey>(keys["leftCam"]))) {
            Quaternion yaw = QuaternionFromAxisAngle({0, 1, 0}, rotateSpeed);
            rotation = QuaternionMultiply(rotation, yaw);
        }
        if (k.isKeyDown(static_cast<KeyboardKey>(keys["rightCam"]))) {
            Quaternion yaw = QuaternionFromAxisAngle({0, 1, 0}, -rotateSpeed);
            rotation = QuaternionMultiply(rotation, yaw);
        }

        if (k.isKeyDown(static_cast<KeyboardKey>(keys["rightRoll"]))) {
            Quaternion roll = QuaternionFromAxisAngle(direction, rotateSpeed);
            rotation = QuaternionMultiply(rotation, roll);
        }
        if (k.isKeyDown(static_cast<KeyboardKey>(keys["leftRoll"]))) {
            Quaternion roll = QuaternionFromAxisAngle(direction, -rotateSpeed);
            rotation = QuaternionMultiply(rotation, roll);
        }

        if (k.isKeyPressed(static_cast<KeyboardKey>(keys["resetCam"]))) {
            Vector3 globalUp = {0, 1, 0};
            Vector3 axis = Vector3CrossProduct(camera.up, globalUp);
            float angle = acosf(Vector3DotProduct(camera.up, globalUp));
            Quaternion rollReset = QuaternionFromAxisAngle(axis, angle);
            rotation = QuaternionMultiply(rotation, rollReset);
        }

        direction = Vector3RotateByQuaternion(direction, rotation);
        camera.target = camera.position + direction;

        camera.up = Vector3RotateByQuaternion(camera.up, rotation);
    }

    Vector2 Game::getMapSize() const
    {
        return _mapSize;
    }

    void Game::setMapSize(const Vector2 &size)
    {
        _mapSize = size;
    }

    TilesWrapper &Game::getTiles()
    {
        return _tiles;
    }

    void Game::addPlayerAI(const std::string &id,
                         const Vector3 position,
                         const int orientation,
                         const int incantationLevel,
                         const std::string &teamName,
                         const std::string &modelFilepath)
    {
        std::shared_ptr<Player> player = Factory::createElement<Player>(modelFilepath, _camera);

        player->setId(id);
        player->setPosition(position);
        player->setOrientation(orientation);
        player->setRotation(0);
        player->setLevel(incantationLevel);
        player->setTeamName(teamName);
        player->setRotationAxis({0, 1, 0});
        player->setColor(WHITE);
        player->setBoundingBoxColor(BLUE);
        player->setRainbowStatus(false);
        _players[id] = player;
    }

    void Game::removePlayerById(const std::string &id)
    {
        if (!_players.contains(id))
            return;
        _players.erase(id);
    }

    void Game::displayPlayerBoundingBoxByTeamName(const std::string &key)
    {
        Mouse &mouse = Mouse::getInstance();
        std::string teamName = key.substr(5, key.size() - 1);
        std::shared_ptr<Text> teamNameText = getElement<Text>(key);

        if (teamNameText->isClicked())
            for (auto &[_, player] : _players)
                if (player->getTeamName() == teamName)
                    player->setBoundingBoxVisibility(true);
        if (mouse.isButtonPressed() && !teamNameText->isHovered())
            for (auto &[_, player] : _players)
                if (player->getTeamName() == teamName)
                    player->setBoundingBoxVisibility(false);
    }

    std::shared_ptr<Player> Game::getPlayerById(const std::string &id)
    {
        if (!_players.contains(id))
            return nullptr;
        return _players[id];
    }

    void Game::setSpeed(const int speed)
    {
        _speed = speed;
    }

    int Game::getSpeed() const
    {
        return _speed;
    }

    void Game::addTeam(const std::string &name)
    {
        _teams.push_back(name);
    }

    size_t Game::getTeamSize() const
    {
        return _teams.size();
    }

    void Game::increaseBctCount()
    {
        ++_bctCount;
    }

    void Game::addEgg(const std::string &eggId)
    {
        if (_eggs.contains(eggId))
            return;
        std::shared_ptr<Egg> egg = Factory::createElement<Egg>(eggId, "Assets/Models/dragon_egg/egg.obj", _camera);
        _eggs[eggId] = egg;
    }

    void Game::removeEgg(const std::string &eggId)
    {
        if (!_eggs.contains(eggId))
            return;
        _eggs.erase(eggId);
    }

    std::shared_ptr<Egg> Game::getEgg(const std::string &eggId)
    {
        if (!_eggs.contains(eggId))
            return nullptr;
        return _eggs[eggId];
    }

    std::string Game::getVillagerTexture(int index)
    {
        return _villagerTextures[index];
    }
}
