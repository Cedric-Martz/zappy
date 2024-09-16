/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

namespace rl
{
    Tile::Tile()
    {
        for (int i = 0; i < 7; i++) {
            _resources[i] = 0;
        }
        _resourceName[ItemType::FOOD] = "Food: ";
        _resourceName[ItemType::LINEMATE] = "Linemate: ";
        _resourceName[ItemType::DERAUMERE] = "Deraumere: ";
        _resourceName[ItemType::SIBUR] = "Sibur: ";
        _resourceName[ItemType::MENDIANE] = "Mendiane: ";
        _resourceName[ItemType::PHIRAS] = "Phiras: ";
        _resourceName[ItemType::THYSTAME] = "Thystame: ";

        _tileResources[ItemType::FOOD].setString("Food: ");
        _tileResources[ItemType::LINEMATE].setString("Linemate: ");
        _tileResources[ItemType::DERAUMERE].setString("Deraumere: ");
        _tileResources[ItemType::SIBUR].setString("Sibur: ");
        _tileResources[ItemType::MENDIANE].setString("Mendiane: ");
        _tileResources[ItemType::PHIRAS].setString("Phiras: ");
        _tileResources[ItemType::THYSTAME].setString("Thystame: ");
        _tileResources[ItemType::FOOD].setColor(YELLOW);
        _tileResources[ItemType::LINEMATE].setColor({90, 90, 86, 255});
        _tileResources[ItemType::DERAUMERE].setColor({0, 40, 255, 255});
        _tileResources[ItemType::SIBUR].setColor({7, 108, 7, 255});
        _tileResources[ItemType::MENDIANE].setColor({63, 147, 232, 255});
        _tileResources[ItemType::PHIRAS].setColor({209, 43, 189, 255});
        _tileResources[ItemType::THYSTAME].setColor({133, 28, 154, 255});

        _cube.loadTextureFromFile("Assets/Imgs/ground.png");
    }

    Tile::~Tile() {}

    void Tile::draw()
    {
        Object::draw();
    }

    void Tile::update(double deltaTime)
    {
        Object::update(deltaTime);
    }

    void Tile::applyTransform(Transform &transform)
    {
        Object::applyTransform(transform);
    }

    VisualElement::Type Tile::getType() const
    {
        return VisualElement::Type::TILE;
    }

    void Tile::setResources(ItemType resource, int value)
    {
        _resources[static_cast<int>(resource)] = value;
    }

    int Tile::getResources(ItemType resource) const
    {
        return _resources[static_cast<int>(resource)];
    }

    Cube &Tile::getCube()
    {
        return _cube;
    }

    std::unordered_map<ItemType, Text> &Tile::getText()
    {
        return _tileResources;
    }

    std::string Tile::getResourcesName(ItemType resource)
    {
        for (auto &[resourceEnum, resourceType] : _resourceName)
            if (resourceEnum == resource)
                return resourceType;
        return "";
    }

    void Tile::manageText(Camera3D &camera)
    {
        for (auto &[tileEnum, tileText] : _tileResources) {
            Vector2 screenPos = GetWorldToScreen((Vector3){_cube.getPosition3().x,
            _cube.getPosition3().y + ((6 - static_cast<int>(tileEnum)) * 3),_cube.getPosition3().z}, camera);
            tileText.setPosition(screenPos);
            std::string ress = getResourcesName(tileEnum) + std::to_string(getResources(tileEnum));
            tileText.setString(ress);
            tileText.setRotation(0);
        }
    }

    void Tile::addPlayer(const std::string &playerId)
    {
        _playersId.push_back(playerId);
    }

    void Tile::removePlayer(const std::string &playerId)
    {
        auto it = std::find(_playersId.begin(), _playersId.end(), playerId);

        if (it == _playersId.end())
            return;
        _playersId.erase(it);
    }

    size_t Tile::getPlayersNumber() const
    {
        return _playersId.size();
    }

    bool Tile::isPlayerOnTile(const std::string &playerId) const
    {
        return std::find(_playersId.begin(), _playersId.end(), playerId) != _playersId.end();
    }
}
