/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** TextureManager.cpp
*/

#include "TextureManager.hpp"

namespace rl
{
    TextureManager::TextureManager() {}

    TextureManager::~TextureManager() {}

    TextureManager &TextureManager::getInstance()
    {
        static TextureManager textureManager;
        return textureManager;
    }

    TextureManager::CachedTexture TextureManager::loadFromCache(const std::string &filename,
                                       bool flipVertical,
                                       bool is3D) const
    {
        auto it = _textureCache.find(filename);
        if (it != _textureCache.end())
            return it->second;
        CachedTexture cachedTexture;
        Image image = LoadImage(filename.c_str());
        if (flipVertical)
            ImageFlipVertical(&image);
        if (is3D)
            cachedTexture.texture3D = LoadTextureCubemap(image, CUBEMAP_LAYOUT_LINE_VERTICAL);
        else
            cachedTexture.texture2D = LoadTextureFromImage(image);
        UnloadImage(image);
        const_cast<std::unordered_map <std::string, CachedTexture> &>(_textureCache)[filename] = cachedTexture;
        return cachedTexture;
    }

    Texture2D TextureManager::loadTexture(const std::string &filename, bool flipVertical) const
    {
        return loadFromCache(filename, flipVertical).texture2D;
    }

    TextureCubemap TextureManager::loadTexture3D(const std::string &filename, bool flipVertical) const
    {
        return loadFromCache(filename, flipVertical, true).texture3D;
    }

    void TextureManager::removeTexture(const std::string &filename)
    {
        if (!_textureCache.contains(filename))
            return;
        _textureCache.erase(filename);
    }
};
