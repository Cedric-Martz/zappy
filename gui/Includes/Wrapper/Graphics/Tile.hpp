/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Tile.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TILE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TILE_HPP

#include <array>
#include "Inventory.hpp"
#include "Cube.hpp"

namespace rl {
    class Tile : public Object {
    public:
        Tile();
        ~Tile();

        void draw() override;
        void update(double deltaTime) override;
        void applyTransform(Transform &transform) override;
        VisualElement::Type getType() const override;

        void setResources(ItemType resource, int value);
        int getResources(ItemType resource) const;

        Cube &getCube();

        std::unordered_map<ItemType, Text> &getText();

        void manageText(Camera3D &camera);

        std::string getResourcesName(ItemType resource);

        void addPlayer(const std::string &playerId);
        void removePlayer(const std::string &playerId);
        size_t getPlayersNumber() const;
        bool isPlayerOnTile(const std::string &playerId) const;

    private:
        std::array<int, 7> _resources;
        Cube _cube;
        std::unordered_map<ItemType, std::string> _resourceName;
        std::unordered_map<ItemType, Text> _tileResources;
        std::vector<std::string> _playersId;
    };
}

#endif /* B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TILE_HPP */
