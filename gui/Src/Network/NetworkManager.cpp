/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** NetworkManager.cpp
*/

#include "NetworkManager.hpp"
#include "Factory.hpp"
#include "Game.hpp"
#include "SettingsValue.hpp"

namespace rl
{
    NetworkManager::NetworkManager()
        : _fd(-1),
        _isConnected(false),
        _port(0),
        _serverAddress{},
        _commands({
            {"msz", [&](const std::vector<std::string> &parts, Game &scene) {
                scene.setMapSize(Vector2(
                        static_cast<float>(std::stoi(parts[0])),
                        static_cast<float>(std::stoi(parts[1]))
                ));
                scene.getElement<Text>("mapSize")->setString("Map size: " +
                    std::to_string(static_cast<int>(scene.getMapSize().x)) + " × " +
                    std::to_string(static_cast<int>(scene.getMapSize().y)));

                Vector3 size = {10, 10, 10};
                for (int y = 0; y < scene.getMapSize().y; ++y)
                    for (int x = 0; x < scene.getMapSize().x; ++x)
                        scene.getTiles().addTile(
                            scene.getCamera(),
                            {
                                static_cast<float>(x) * size.x,
                                static_cast<float>(y) * size.z
                            },
                            size
                        );
            }},
            {"bct", [&](const std::vector<std::string> &parts, Game &scene) {
                scene.getTiles().updateTile(parts);
                scene.increaseBctCount();
            }},
            {"tna", [&](const std::vector<std::string> &parts, Game &scene) {
                std::string teamName = parts[0];
                scene.addTeam(teamName);
                scene.addText("team;" + teamName,
                              teamName,
                              25,
                              WHITE,
                              {20, static_cast<float>(300 + (30 * scene.getTeamSize()))});
                scene.getElement<Text>("team;" + teamName)->setOrigin({0, 0});
            }},
            {"pnw", [&](const std::vector<std::string> &parts, Game &scene) {
                scene.addPlayerAI(
                        parts[0],
                        Vector3(
                            std::stoi(parts[1]) * 10,
                            17.0f,
                            std::stoi(parts[2]) * 10
                        ),
                        std::stoi(parts[3]),
                        std::stoi(parts[4]),
                        parts[5],
                        "Assets/Models/villager/model.obj"
                );
                scene.getPlayerById(parts[0])->updateModelTexture(TextureManager::getInstance().loadTexture("Assets/Models/villager/textures/villager.png"));
            }},
            {"ppo", [&](const std::vector<std::string> &parts, Game &scene) {
                std::shared_ptr<Player> player = scene.getPlayerById(parts[0]);
                if (!player)
                    return;
                const std::string playerId = player->getId();
                std::shared_ptr<Tile> tile = scene.getTiles().getTile({
                    static_cast<float>(std::stoi(parts[1]) * 10),
                    static_cast<float>(std::stoi(parts[2]) * 10)
                });
                if (!tile)
                    return;
                Vector3 newPlayerPos(
                    static_cast<float>(tile->getPosition3().x),
                    17.0f,
                    static_cast<float>(tile->getPosition3().y)
                );
                Vector2 newPlayerTilePos(
                        newPlayerPos.x,
                        newPlayerPos.z
                );
                if (newPlayerTilePos == player->getTilePosition())
                    return;
                if (player->getPosition3() == Vector3(-1, -1, -1))
                    player->setPosition(newPlayerPos);
                player->setOrientation(std::stoi(parts[3]));
                if (std::abs(newPlayerTilePos.x - player->getPosition3().x) == (scene.getMapSize().x - 1) * 10 ||
                    std::abs(newPlayerTilePos.y - player->getPosition3().z) == (scene.getMapSize().y - 1) * 10) {
                    player->setPosition(newPlayerPos);
                    player->setTilePosition(newPlayerTilePos);
                    player->clearWalkGoal();
                    return;
                }
                player->addWalkGoal(newPlayerTilePos);
                player->setTilePosition(newPlayerTilePos);
            }},
            {"plv", [&](const std::vector<std::string> &parts, Game &scene) {
                std::shared_ptr<Player> player = scene.getPlayerById(parts[0]);
                if (!player)
                    return;
                player->setLevel(std::stoi(parts[1]));
                if (player->getLevel() < 8)
                    player->updateModelTexture(TextureManager::getInstance().loadTexture(scene.getVillagerTexture(player->getLevel() - 1)));
                if (player->getLevel() == 8)
                    player->setRainbowStatus(true);
            }},
            {"pin", [&](const std::vector<std::string> &parts, Game &scene) {
                std::shared_ptr<Player> player = scene.getPlayerById(parts[0]);
                if (!player)
                    return;
                player->setServerResponseFlag(false);
                for (size_t i = 3; i < parts.size(); ++i)
                    player->setResourceAmount(static_cast<ItemType>(i - 3), std::stoi(parts[i]));
            }},
            {"pex", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                scene.sendNotification("YEET");
            }},
            {"pbc", [&](const std::vector<std::string> &parts, Game &scene) {
                std::shared_ptr<Player> player = scene.getPlayerById(parts[0]);
                if (!player)
                    return;
                player->setTalkStatus(true);
                AudioManager::getInstance().playSound("salut_les_teks");
                scene.sendNotification("Salut les teks!");
            }},
            {"pic", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                Vector2 pos(std::stoi(parts[0]) * 10, std::stoi(parts[1]) * 10);

                std::shared_ptr<rl::Tile> tile = scene.getTiles().getTile(pos);
                if (!tile)
                    return;
                tile->getCube().loadTextureFromFile("Assets/Imgs/focus.png");

                scene.sendNotification("Incantation started");
            }},
            {"pie", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                Vector2 pos(std::stoi(parts[0]) * 10, std::stoi(parts[1]) * 10);

                std::shared_ptr<rl::Tile> tile = scene.getTiles().getTile(pos);
                if (!tile)
                    return;
                tile->getCube().loadTextureFromFile("Assets/Imgs/ground.png");

                scene.sendNotification("Achievement", "Incantation ended");
            }},
            {"pfk", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                scene.sendNotification("Player is laying an egg");
            }},
            {"pdr", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {}},
            {"pgt", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {}},
            {"pdi", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                scene.removePlayerById(parts[0]);
            }},
            {"enw", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                Vector2 pos(std::stoi(parts[2]) * 10, std::stoi(parts[3]) * 10);

                scene.sendNotification("Egg was laid by player");
                scene.addEgg(parts[0]);
                std::shared_ptr<Egg> egg = scene.getEgg(parts[0]);
                if (!egg)
                    return;
                egg->setPosition({pos.x, 0.0f, pos.y});
                egg->setScale(2);
            }},
            {"ens", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                Vector2 pos(std::stoi(parts[1]) * 10, std::stoi(parts[2]) * 10);

                scene.addEgg(parts[0]);
                std::shared_ptr<Egg> egg = scene.getEgg(parts[0]);
                if (!egg)
                    return;
                egg->setPosition({pos.x, 0.0f, pos.y});
                egg->setScale(2);
            }},
            {"ebo", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                scene.sendNotification("Player connection for an egg");
                scene.removeEgg(parts[0]);
            }},
            {"edi", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                scene.removeEgg(parts[0]);
            }},
            {"sgt", [&](const std::vector<std::string> &parts, Game &scene) {
                scene.setSpeed(std::stoi(parts[0]));
                scene.getElement<Text>("speed")->setString("Speed: " + std::to_string(scene.getSpeed()));
            }},
            {"sst", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {}},
            {"seg", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                scene.sendNotification("End of Game! GG!");
                AudioManager::getInstance().playSound("victory");
            }},
            {"smg", [&](const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                scene.sendNotification("Message from server", parts[0]);
            }},
            {"suc", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                SettingsValue &settings = SettingsValue::getInstance();
                settings.setLastGuiResult("Bad GUI Command");
            }},
            {"sbp", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                SettingsValue &settings = SettingsValue::getInstance();
                settings.setLastGuiResult("Bad GUI syntaxe");
            }},
            {"ko", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                SettingsValue &settings = SettingsValue::getInstance();
                settings.setLastAdminResult("Bad Admin Command");
            }},
            {"ok", [&]([[maybe_unused]] const std::vector<std::string> &parts, [[maybe_unused]] Game &scene) {
                SettingsValue &settings = SettingsValue::getInstance();
                settings.setLastAdminResult("Good Admin Command");
            }}
        })
    {}

    NetworkManager::~NetworkManager()
    {
        stop();
    }

    bool NetworkManager::setSocket()
    {
        if (!_isConnected || _fd == -1)
            return false;
        FD_ZERO(&_readFds);
        FD_SET(_fd, &_readFds);

        struct timeval tv = {.tv_sec = 0, .tv_usec = 1000};
        if (select(_fd + 1, &_readFds, &_writeFds, NULL, &tv) < 0)
            return false;

        return true;
    }

    int NetworkManager::getFd() const
    {
        return _fd;
    }

    std::string &NetworkManager::readToBuffer()
    {
        *this >> _buffer;
        return _buffer;
    }

    int NetworkManager::getBufferLen() const
    {
        return _buffer.size();
    }

    void NetworkManager::clearBuffer()
    {
        _buffer.clear();
    }

    std::string NetworkManager::getBuffer()
    {
        return _buffer;
    }

    NetworkManager &NetworkManager::getInstance()
    {
        static NetworkManager instance;
        return instance;
    }

    void NetworkManager::init()
    {
        if (_isConnected)
            return;

        _fd = socket(AF_INET, SOCK_STREAM, 0);
        if (_fd == -1) {
            return;
        }

        _serverAddress.sin_family = AF_INET;
        _serverAddress.sin_port = htons(_port);
        _serverAddress.sin_addr.s_addr = inet_addr(_ip == "localhost" ? "127.0.0.1" : _ip.c_str());

        if (connect(_fd, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress)) < 0) {
            close(_fd);
            _fd = -1;
            return;
        }
        _isConnected = true;
        *this << "GRAPHIC\n"<< "msz\n" << "sgt\n" << "tna\n" << "mct\n" << "/login MIAOU\n";
    }

    void NetworkManager::stop()
    {
        if (_isConnected) {
            shutdown(_fd, SHUT_RDWR);
            close(_fd);
            _fd = -1;
            _isConnected = false;
        }
    }

    uint16_t NetworkManager::getPort()
    {
        return _port;
    }

    void NetworkManager::setPort(const uint16_t port)
    {
        _port = port;
    }

    void NetworkManager::setIp(const std::string &ip)
    {
        _ip = ip;
    }

    std::string NetworkManager::getIp()
    {
        return _ip;
    }

    NetworkManager &NetworkManager::operator<<(const std::string &string)
    {
        if (!_isConnected || _fd == -1)
            return *this;

        FD_SET(_fd, &_writeFds);
        if (!FD_ISSET(_fd, &_writeFds))
            return *this;

        ssize_t s = write(_fd, string.c_str(), string.size());
        if (s < (int)string.size())
            std::cerr << "Write failed" << std::endl;

        FD_CLR(_fd, &_writeFds);

        return *this;
    }

    NetworkManager &NetworkManager::operator>>(std::string &string)
    {
        if (!setSocket())
            return *this;

        if (!FD_ISSET(_fd, &_readFds))
            return *this;

        char buffer[65535] = {0};
        ssize_t bytesRead = read(_fd, buffer, sizeof(buffer) - 1);

        if (bytesRead < 0) {
            std::cerr << "Network: read: error" << std::endl;
            return *this;
        }
        buffer[bytesRead] = '\0';
        string = buffer;
        return *this;
    }

    void NetworkManager::interpretCommand(const std::string &buffer,
                                          Game &scene)
    {
        if (buffer.size() == 0)
            return;

        std::istringstream iss(buffer);
        std::string cmd;
        iss >> cmd;
        std::vector<std::string> parts;
        std::string part;

        while (iss >> part)
            parts.push_back(part);
        if (_commands.contains(cmd))
            _commands[cmd](parts, scene);
    }

    void NetworkManager::readSocketInput(Game &scene)
    {
        if (!setSocket())
            return;

        std::string &b = readToBuffer();
        size_t index{};

        while ((index = b.find('\n')) != std::string::npos) {
            std::string command = b.substr(0, index);
            interpretCommand(command, scene);
            b.erase(0, index + 1);
        }
    }
};
