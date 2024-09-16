/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** TextureManager.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TEXTUREMANAGER_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TEXTUREMANAGER_HPP
    #include "RayLib.hpp"
    #include <unordered_map>

namespace rl
{
    class TextureManager {
    public:
        static TextureManager &getInstance();
        Texture2D loadTexture(const std::string &filename, bool flipVertical = false) const;
        TextureCubemap loadTexture3D(const std::string &filename, bool flipVertical = false) const;
        void removeTexture(const std::string &filename);
    private:
        union CachedTexture {
            Texture2D texture2D;
            TextureCubemap texture3D;
        };

        TextureManager();
        ~TextureManager();
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;

        CachedTexture loadFromCache(const std::string &filename, bool flipVertical, bool is3D = false) const;

        std::unordered_map<std::string, CachedTexture> _textureCache;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TEXTUREMANAGER_HPP*/
