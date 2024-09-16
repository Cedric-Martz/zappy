/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** TilesWrapper
*/

#ifndef TILE_WRAPPER_HPP_
    #define TILE_WRAPPER_HPP_

    #include <array>
    #include "Tile.hpp"

namespace std {
    template <>
    struct hash<Vector2> {
        size_t operator()(const Vector2& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };

    template <>
    struct hash<std::pair<std::string, std::string>> {
        size_t operator()(const std::pair<std::string, std::string>& p) const {
            return hash<std::string>()(p.first) ^ (hash<std::string>()(p.second) << 1);
        }
    };
}

namespace rl
{
    class TilesWrapper {
        public:
            TilesWrapper();
            ~TilesWrapper();

            void render() const;
            void renderText(Camera3 &camera) const;
            void update(const double deltaTime);

            void addTile(
                std::shared_ptr<Camera3> camera,
                const Vector2 pos,
                const Vector3 size
            );
            bool updateTile(const std::vector<std::string> &data);

            void toggleTextDisplay();
            bool geTextDisplayState();

            std::shared_ptr<Tile> getTile(const Vector2 &vector);

        private:
            std::unordered_map<Vector2, std::shared_ptr<Tile>> _tiles;
            std::array<std::unique_ptr<Cube>, 7> _collectibles;
            std::array<std::string, 7> _collectiblesTexture;
            bool _displayText;
    };
}

#endif /* TILE_WRAPPER_HPP_ */
