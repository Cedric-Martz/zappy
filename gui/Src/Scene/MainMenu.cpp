/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** MainMenu
*/

#include <iostream>
#include <random>
#include "SceneManager.hpp"
#include "MainMenu.hpp"
#include "Factory.hpp"
#include "MainSetting.hpp"
#include "NetworkManager.hpp"
#include "Game.hpp"
#include "Star.hpp"
#include "ArgumentParser.hpp"

namespace rl
{
    MainMenu::MainMenu()
        : _camera(std::make_shared<Camera3>(Vector3{0.0f, 0.0f, 5.0f},
                                            Vector3{0.0f, 0.0f, 0.0f},
                                            Vector3{0.0f, 1.0f, 0.0f},
                                            60.0f,
                                            CAMERA_PERSPECTIVE)),
        _canDisplayMenu(false),
        _alpha(0),
        _starsTimebank(0),
        _cameraMoveSpeed(0.01f),
        _titleCharOffset(30),
        _onduloscopeMode(false),
        _boomKeys({
            KeyboardKey::KEY_B,
            KeyboardKey::KEY_O,
            KeyboardKey::KEY_O,
            KeyboardKey::KEY_M
        }),
        _boomIndex(0)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-0.03, 0.03);
        std::uniform_real_distribution<> dis_rotate(0.01, 0.03);

        RenderWindow &window = RenderWindow::getInstance();
        AudioManager &audio = AudioManager::getInstance();
        ArgumentParser &parser = ArgumentParser::getInstance();
        NetworkManager &network = NetworkManager::getInstance();

        float near = 0.1f;
        float aspect = 16.0f / 9.0f;
        float top = near * tanf(_camera->getSource().fovy * 0.5f * DEG2RAD);
        _camera->setMatrixUtils(
                near,
                10000.0f,
                aspect,
                top,
                top * aspect
        );

        _sky.loadConfig(200, 5.0f, 0.02f, {0, 0, 0}, {1, 3}, 0.0125f, _camera);

        Vector2 ws = window.getSize();
        float wsx = ws.x;
        float wsy = ws.y;
        float wsf = wsx;

        Vector2 start(window.getSize().x / 2.0f, 0.3 * wsy);

        addSplash("splash", {wsx * 0.76f, wsy * 0.28f}, ColorAlpha(YELLOW, 0.0f));
        addSprite("Z", "Assets/Imgs/letter/Z.png", {start.x - 0.2f * wsx, start.y}, {0.00035f * wsf, 0.00035f * wsf},
                          ColorAlpha(WHITE, 0));
        addSprite("A", "Assets/Imgs/letter/A.png", {start.x - 0.08f * wsx, start.y + 0.014f * wsy}, {0.00035f * wsf, 0.00035f * wsf},
                          ColorAlpha(WHITE, 0));
        addSprite("P1", "Assets/Imgs/letter/P.png", {start.x + 0.01f * wsx, start.y - 0.042f * wsy}, {0.00042f * wsf, 0.00042f * wsf},
                          ColorAlpha(WHITE, 0));
        addSprite("P2", "Assets/Imgs/letter/P.png", {start.x + 0.1f * wsx, start.y - 0.042f * wsy}, {0.00042f * wsf, 0.00042f * wsf},
                          ColorAlpha(WHITE, 0));
        addSprite("Y", "Assets/Imgs/letter/Y.png", {start.x + 0.2f * wsx, start.y - 0.1f * wsy}, {0.00069f * wsf, 0.00069f * wsf},
                          ColorAlpha(WHITE, 0));

        addText("ipText", "IP :", 0.039 * wsf, ColorAlpha(WHITE, 0), {0.286f * wsx, 0.555f * wsy});
        addText("portText", "PORT :", 0.039 * wsf, ColorAlpha(WHITE, 0), {0.25f * wsx, 0.694f * wsy});
        addInputText(
            "ipInput",
            {0.5f * wsx, 0.555f * wsy, 0.3125f * wsx, 0.0694f * wsy},
            20,
            0.0234f * wsf,
            ColorAlpha(LIGHTGRAY, 0)
        );
        addInputText(
            "portInput",
            {0.5f * wsx, 0.694f * wsy, 0.3125f * wsx, 0.0694f * wsy},
            20,
            0.0234f * wsf,
            ColorAlpha(LIGHTGRAY, 0)
        );

        addButton(
                "button",
                {wsx / 2, 0.833f * wsy},
                {0.156f * wsx, 0.0694f * wsy},
                ColorAlpha(WHITE, 0),
                [&]() {
                    audio.stopJukebox(*this);
                    SceneManager::getInstance().setTransitionSpeed(0.01);
                    if (getElement<InputText>("ipInput")->getText().getString() != "") {
                        network.setIp(getElement<InputText>("ipInput")->getText().getString());
                    }
                    if (getElement<InputText>("portInput")->getText().getString() != "") {
                        network.setPort(std::stoi(getElement<InputText>("portInput")->getText().getString()));
                    }
                    audio.loadSound("Assets/Sounds/Windows XP Startup.mp3", "windowsXP");
                    audio.playSound("windowsXP");
                    SceneManager::getInstance().pushScene(std::make_unique<Game>());
                },
                "Assets/Imgs/buttons/startButton.png",
                "Assets/Imgs/buttons/startButtonHovered.png"
        );
        addButton(
                "Setting button",
                Vector2{0.0625f * wsx, 0.11f * wsy},
                Vector2{0.0625f * wsx, 0.11f * wsy},
                ColorAlpha(RED, 0),
                [&]() {
                    SceneManager::getInstance().setTransitionSpeed(0.1);
                    SceneManager::getInstance().pushScene(std::make_unique<MainSetting>());
                },
                "Assets/Imgs/buttons/posefduesi.png",
                "Assets/Imgs/buttons/posefduesi.png"
        );
        addSphere(
                "supernova",
                {0, 0, 0},
                0,
                WHITE,
                TRANSPARENT,
                "Assets/Imgs/focus.png"
        );
        zoom = false;
        audio.setJukeboxIndex(1, *this);
        audio.playJukebox(*this);

        _transforms["Z"].rotate(dis(gen)).translate(dis(gen), dis(gen)).scale(dis_rotate(gen));
        _transforms["A"].rotate(dis(gen)).translate(dis(gen), dis(gen)).scale(dis_rotate(gen));
        _transforms["P1"].rotate(dis(gen)).translate(dis(gen), dis(gen)).scale(dis_rotate(gen));
        _transforms["P2"].rotate(dis(gen)).translate(dis(gen), dis(gen)).scale(dis_rotate(gen));
        _transforms["Y"].rotate(dis(gen)).translate(dis(gen), dis(gen)).scale(dis_rotate(gen));
        _firstWindowPosition = window.getPosition();

        getElement<InputText>("portInput")->getText().setString(parser.getPort());
        getElement<InputText>("ipInput")->getText().setString(parser.getIp());

        addButton(
                "Onduloscope button",
                Vector2{0.8975f * wsx, 0.88f * wsy},
                Vector2{0.1500f * wsx, 0.11f * wsy},
                ColorAlpha(WHITE, 0),
                [this]() {
                    AudioManager &audio = AudioManager::getInstance();
                    this->_onduloscopeMode = !this->_onduloscopeMode;
                    if (this->_onduloscopeMode) {
                        audio.playMusic("Z_outer");
                        audio.playMusic("A_outer");
                        audio.playMusic("P1_outer");
                        audio.playMusic("P2_outer");
                        audio.playMusic("Y_outer");
                    } else {
                        audio.stopMusic("Z_outer");
                        audio.stopMusic("A_outer");
                        audio.stopMusic("P1_outer");
                        audio.stopMusic("P2_outer");
                        audio.stopMusic("Y_outer");
                    }
                },
                "Assets/Imgs/buttons/signalscope.png",
                "Assets/Imgs/buttons/signalscope.png"
        );
        audio.loadMusic("Assets/Musics/OuterWilds/chert.mp3", "Z_outer");
        audio.loadMusic("Assets/Musics/OuterWilds/esker.mp3", "A_outer");
        audio.loadMusic("Assets/Musics/OuterWilds/feldspar.mp3", "P1_outer");
        audio.loadMusic("Assets/Musics/OuterWilds/gabbro.mp3", "P2_outer");
        audio.loadMusic("Assets/Musics/OuterWilds/riebeck.mp3", "Y_outer");

        audio.setVolumeMusic("Z_outer", 0.0);
        audio.setVolumeMusic("A_outer", 0.0);
        audio.setVolumeMusic("P1_outer", 0.0);
        audio.setVolumeMusic("P2_outer", 0.0);
        audio.setVolumeMusic("Y_outer", 0.0);
    }

    MainMenu::~MainMenu()
    {
    }

    std::string MainMenu::getId() const
    {
        return "MainMenuScene";
    }

    void MainMenu::events()
    {
        SetExitKey(KEY_ESCAPE);
    }

    void MainMenu::update(double deltaTime)
    {
        AudioManager &audio = AudioManager::getInstance();

        Vector2 mousePos = Mouse::getInstance().getPosition();

        std::shared_ptr<Splash> splash = getElement<Splash>("splash");
        Vector2 scale = splash->getScale2();
        zoom = scale.x >= 1.2f || zoom;
        zoom = scale.x >= 1.0f && zoom;
        scale.x += !zoom ? 0.005 : -0.005;
        splash->setScale(scale);

        for (auto &[_, element] : _elements)
            element->update(deltaTime);

        for (auto &[transformId, transformMatrix] : _transforms)
            _elements[transformId]->applyTransform(transformMatrix);

        Vector2 winSize = RenderWindow::getInstance().getSize();

        for (auto &[key, element] : _elements) {
            if (key == "Z" || key == "A" || key == "P1" || key == "P2" || key == "Y") {
                if (element->getPosition2().x > winSize.x + 200 || element->getPosition2().x < -200)
                    element->setPosition(Vector2{element->getPosition2().x > winSize.x ? -200 : winSize.x + 200, element->getPosition2().y});
                if (element->getPosition2().y > winSize.y + 200 || element->getPosition2().y < -200)
                    element->setPosition(Vector2{element->getPosition2().x, element->getPosition2().y > winSize.y ? -200 : winSize.y + 200});
                if (!_onduloscopeMode)
                    continue;
                Vector2 pos = element->getPosition2();
                double dist = std::sqrt(std::pow(pos.x - mousePos.x, 2) + std::pow(pos.y - mousePos.y, 2));
                double volume = (dist > 800) ? 0.0f : 1.0 - (dist / 800);

                std::string soundKey = key + "_outer";
                audio.setVolumeMusic(soundKey, volume);
            }
        }

        if (IsKeyPressed(KEY_SPACE))
            _starsTimebank = 4.0f;
        if (!_onduloscopeMode)
            audio.updateJukebox(*this);
        else {
            audio.updateMusic("Z_outer");
            audio.updateMusic("A_outer");
            audio.updateMusic("P1_outer");
            audio.updateMusic("P2_outer");
            audio.updateMusic("Y_outer");
        }

        if (_starsTimebank <= 3.0f) {
            _starsTimebank += Clock::getInstance().updateDeltaTime().asSeconds();
            _camera->getSource().target.y -= _cameraMoveSpeed;
            if (_cameraMoveSpeed > 0)
                _cameraMoveSpeed -= 0.00006f;
        } else {
            if (!_canDisplayMenu) {
                _canDisplayMenu = true;
            }
        }

        if (_canDisplayMenu && _alpha <= 1.0f) {
            updateAlphaElements(_alpha);
            _alpha += 0.01f;
        }

        updateTitleByWindow(deltaTime);
        _sky.update(deltaTime);
        detectBoomShortcut();
    }

    void MainMenu::updateTitleByWindow([[maybe_unused]] double deltaTime)
    {
        RenderWindow &window = RenderWindow::getInstance();

        _windowOffset = Vector2(window.getPosition().x - _firstWindowPosition.x,
                                window.getPosition().y - _firstWindowPosition.y);
        _firstWindowPosition = window.getPosition();
    }

    void MainMenu::render()
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
            _sky.draw();
        }
        for (auto &[_, element] : _elements)
            if (element->getDimension() == VisualElement::Dimension::DIMENSION2) {
                if (!element->getDisplayed())
                    continue;
                if (element->getType() == VisualElement::Type::SPRITE)
                    element->setPosition(element->getPosition2() - _windowOffset);
                element->draw();
            }
    }

    void MainMenu::updateAlphaElements(const float alpha)
    {
        if (alpha < 0.0f || alpha > 1.0f)
            return;
        for (auto &[_, element] : _elements)
            element->setColor(ColorAlpha(element->getColor(), alpha));
    }

    void MainMenu::detectBoomShortcut()
    {
        Keyboard &keyboard = Keyboard::getInstance();

        if (_boomIndex == _boomKeys.size()) {
            std::shared_ptr<Sphere> supernova = getElement<Sphere>("supernova");
            if (supernova && supernova->getSize() < 5.0f)
                supernova->setSize(supernova->getSize() + 0.01f);
            else {
                _boomIndex = 0;
                supernova->setSize(0);
            }
        } else {
            if (keyboard.isKeyPressed(_boomKeys[_boomIndex]))
                ++_boomIndex;
        }
    }
}
