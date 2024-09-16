/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** TilesWrapper
*/

#include "TilesWrapper.hpp"

namespace rl
{
    TilesWrapper::TilesWrapper()
        : _tiles({}),
        _collectiblesTexture({
            "Assets/Imgs/ressources/food-texture.png",
            "Assets/Imgs/ressources/linemate-texture.png",
            "Assets/Imgs/ressources/deraumere-texture.png",
            "Assets/Imgs/ressources/sibure-texture.png",
            "Assets/Imgs/ressources/mendiane-texture.png",
            "Assets/Imgs/ressources/phiras-texture.png",
            "Assets/Imgs/ressources/thystame-texture.png"
        }),
        _displayText(false)
    {
        for (int i = 0; i < 7; ++i) {
            _collectibles[i] = std::make_unique<Cube>(_collectiblesTexture[i]);
            _collectibles[i]->setSize(1, 1, 1);
            _collectibles[i]->setRotationAxis(Vector3(1.0f, 0.0f, 0.0f));
            _collectibles[i]->setRotation(-90);
        }
    }

    TilesWrapper::~TilesWrapper()
    {
    }

    void TilesWrapper::render() const
    {
        int size = 0;

        for (auto &[tilePos, tile] : _tiles) {
            Cube &cube = tile->getCube();
            cube.draw();
            Vector3 pos(tilePos.x - 4.5, 5.5, tilePos.y - 4.5);

            Vector3 shift(0, 0, 0);

            for (int i = 0; i < 7; ++i) {
                size = tile->getResources(static_cast<ItemType>(i));
                for (int j = 0; j < size; ++j) {
                    shift.x = (j % 100) % 10;
                    shift.y = j / 100 - 5;
                    shift.z = (j % 100) / 10;

                    Vector3 collectiblePos = pos;
                    collectiblePos.x += shift.x;
                    collectiblePos.y += shift.y;
                    collectiblePos.z += shift.z;

                    _collectibles[i]->setPosition(collectiblePos);
                    _collectibles[i]->draw();
                }
            }
        }
    }

    void TilesWrapper::renderText(Camera3 &camera) const
    {
        if (!_displayText)
            return;
        for (auto &[_, tile] : _tiles) {
            tile->manageText(camera.getSource());
            if (tile->getCube().isHovered()) {
               for (auto &[_, text] : tile->getText())
                   text.draw();
                break;
            }
        }
    }

    void TilesWrapper::update(const double deltaTime)
    {
        for (auto &[key, tile] : _tiles)
            tile->update(deltaTime);
    }

    void TilesWrapper::addTile(
        std::shared_ptr<Camera3> camera,
        const Vector2 pos,
        const Vector3 size
    )
    {
        _tiles[pos] = std::make_shared<Tile>();
        Cube &cube = _tiles[pos]->getCube();
        cube.setCamera(camera);
        cube.setPosition(pos.x, -5.0f, pos.y);
        cube.setSize(size);
        cube.setWiresColor(WHITE);
    }

    bool TilesWrapper::updateTile(const std::vector<std::string> &data)
    {
        Vector2 pos(std::stoi(data[0]) * 10, std::stoi(data[1]) * 10);

        if (!_tiles.contains(pos))
            return false;

        Tile &tile = *_tiles[pos];
        tile.setPosition(pos);
        tile.setResources(ItemType::FOOD, std::stoi(data[2]));
        tile.setResources(ItemType::LINEMATE, std::stoi(data[3]));
        tile.setResources(ItemType::DERAUMERE, std::stoi(data[4]));
        tile.setResources(ItemType::SIBUR, std::stoi(data[5]));
        tile.setResources(ItemType::MENDIANE, std::stoi(data[6]));
        tile.setResources(ItemType::PHIRAS, std::stoi(data[7]));
        tile.setResources(ItemType::THYSTAME, std::stoi(data[8]));

        return true;
    }

    void TilesWrapper::toggleTextDisplay()
    {
        _displayText = !_displayText;
    }

    bool TilesWrapper::geTextDisplayState()
    {
        return _displayText;
    }

    std::shared_ptr<Tile> TilesWrapper::getTile(const Vector2 &vector)
    {
        if (!_tiles.contains(vector))
            return nullptr;
        return _tiles[vector];
    }
}
