/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** drawTextMenu
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include "AScene.hpp"
    #include "InputText.hpp"
    #include "Text.hpp"
    #include "Wrapper.hpp"
    #include "Camera3.hpp"
    #include "Grid.hpp"
    #include "Notification.hpp"
    #include "RenderWindow.hpp"
    #include "Player.hpp"
    #include "Tile.hpp"
    #include "Sky.hpp"
    #include "Planet.hpp"
    #include "Egg.hpp"
    #include "TilesWrapper.hpp"
    #include <functional>
    #include <deque>
    #include <chrono>

namespace rl
{
    class Game : public AScene {
        public:
            Game();
            ~Game();

            std::string getId() const override;
            std::shared_ptr<Camera3> &getCamera();

            void events() override;
            void update(double deltaTime) override;
            void render() override;

            void sendNotification(const std::string &title, const std::string &message = "");
            void getNotification();
            void updateNotifications();

            Vector2 getMapSize() const;
            void setMapSize(const Vector2 &size);

            TilesWrapper &getTiles();

            void addPlayerAI(const std::string &id,
                           const Vector3 position,
                           const int orientation,
                           const int incantationLevel,
                           const std::string &teamName,
                           const std::string &modelFilepath);
            std::shared_ptr<Player> getPlayerById(const std::string &id);
            void removePlayerById(const std::string &id);
            void displayPlayerBoundingBoxByTeamName(const std::string &objectElementName);

            void setSpeed(const int speed);
            int getSpeed() const;

            void addTeam(const std::string &name);
            size_t getTeamSize() const;

            std::string getVillagerTexture(int index);

            void increaseBctCount();

            void addEgg(const std::string &eggId);
            void removeEgg(const std::string &eggId);
            std::shared_ptr<Egg> getEgg(const std::string &eggId);

        private:
            void updateCamera3(float deltaTime);
            void updateMapValues();
            void renderStackedElems();

            std::shared_ptr<Camera3> _camera;
            std::deque<Notification> _notifications;
            int _speed;
            Sky _sky;
            Vector2 _mapSize;
            std::unordered_map<std::string, std::shared_ptr<Player>> _players;
            TilesWrapper _tiles;
            std::vector<std::string> _teams;
            std::unordered_map<std::string, std::shared_ptr<Egg>> _eggs;
            size_t _bctCount;
            std::chrono::steady_clock::time_point _lastMct;
            std::array<std::string, 7> _villagerTextures;
            std::unordered_map<ItemType, int> _nbRessources;
            std::array<int, 8> _levels;
            bool _canMove;
    };
}

#endif /* !GAME_HPP_ */
