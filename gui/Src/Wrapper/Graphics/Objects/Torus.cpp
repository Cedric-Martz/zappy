/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Torus.cpp
*/

#include "Torus.hpp"
#include "RayLib.hpp"
#include "TextureManager.hpp"

namespace rl
{
    Torus::Torus(const float radius,
                 const float size,
                 const int radSeg,
                 const int sides)
        : Object(),
        _hasTextureLoaded(false)
    {
        _model = LoadModelFromMesh(GenMeshTorus(radius, size, radSeg, sides));
    }

    Torus::Torus(const float radius,
                 const float size,
                 const int radSeg,
                 const int sides,
                 const std::string &textureFilepath)
                 : _hasTextureLoaded(false)
    {
        _model = LoadModelFromMesh(GenMeshTorus(radius, size, radSeg, sides));
        loadTextureFromFile(textureFilepath);
    }

    Torus::~Torus() {}

    void Torus::draw()
    {
        DrawModel(_model, _position, _scale.x, _color);
    }

    void Torus::applyTransform([[maybe_unused]] Transform &transform) {}

    void Torus::update(double deltaTime)
    {
        updateRainbow(deltaTime);
    }

    VisualElement::Type Torus::getType() const
    {
        return VisualElement::Type::TORUS;
    }

    void Torus::loadTextureFromFile(const std::string &filepath)
    {
        if (_hasTextureLoaded)
            return;
        Texture2D texture = TextureManager::getInstance().loadTexture(filepath);
        if (texture.width == 0 || texture.height == 0)
            return;
        _hasTextureLoaded = true;
        _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    }
};
