/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Player.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_PLAYER_HPP
#define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_PLAYER_HPP

#include "Model3.hpp"
#include "Inventory.hpp"
#include "Sphere.hpp"
#include <queue>

namespace rl {
    class Player : public Model3 {
    public:
        Player();
        Player(const std::string &modelFilepath, std::shared_ptr<Camera3> camera);
        ~Player();

        void update(double deltaTime) override;
        void draw() override;
        bool isClicked();
        void drawInventory();

        int getLevel() const;
        void setLevel(const int level);

        std::string getId() const;
        void setId(const std::string &id);

        void setOrientation(const int orientation);

        std::string getTeamName() const;
        void setTeamName(const std::string &name);

        void setResourceAmount(ItemType type, int amount);
        void collectResource(const ItemType type);
        void dropResource(const ItemType type);

        void setTalkStatus(const bool status);
        bool isTalking() const;

        Sphere &getBroadcastSphere();

        void setServerResponseFlag(bool value);
        bool getServerResponseFlag() const;

        void addWalkGoal(const Vector2 &goal);
        Vector2 getCurrentWalkGoal() const;
        void removeCurrentWalkGoal();
        void clearWalkGoal();

        void setTilePosition(const Vector2 &position);
        Vector2 getTilePosition() const;

    private:
        Inventory _inventory;
        Text _levelText;
        Sphere _broadcastSphere;
        bool _hasBeenClicked;
        bool _isBroadcasting;
        int _lvl;
        std::string _id;
        std::string _teamName;
        bool _waitingForServerResponse;
        float _walkTimebank;
        std::queue<Vector2> _walkQueue;
        Vector2 _tilePosition;
    };
}

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_PLAYER_HPP*/
