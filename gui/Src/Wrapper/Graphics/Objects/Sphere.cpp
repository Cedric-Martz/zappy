/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"
#include "TextureManager.hpp"
#include "Color.hpp"

namespace rl
{
    Sphere::Sphere()
        : Model3(),
        _hasModelLoaded(false),
        _wiresColor(TRANSPARENT),
        _rings(32),
        _slices(32)
    {
        updateModel();
    }

    Sphere::Sphere(const float scale, const int rings, const int slices)
        : Model3(),
        _hasModelLoaded(false),
        _wiresColor(TRANSPARENT),
        _rings(rings),
        _slices(slices)
    {
        _size.x = scale;
        updateModel();
    }

    Sphere::Sphere(const float scale, const int rings, const int slices,
                   const std::string &filepath)
        : Model3(),
          _hasModelLoaded(false),
          _wiresColor(TRANSPARENT),
          _rings(rings),
          _slices(slices)
    {
        _modelFilepath = filepath;
        _size.x = scale;
        updateModel();
        updateModelTexture(TextureManager::getInstance().loadTexture(filepath));
    }

    Sphere::~Sphere() {}

    void Sphere::draw()
    {
        if (_color != TRANSPARENT && _hasModelLoaded)
            DrawModel(_model, _position, _size.x, _color);
        if (_wiresColor != TRANSPARENT && _hasModelLoaded)
            DrawSphereWires(_position, _size.x, 10, 10, _wiresColor);
    }

    void Sphere::applyTransform([[maybe_unused]] Transform &transform) {}

    void Sphere::update(double deltaTime)
    {
        updateRainbow(deltaTime);
    }

    void Sphere::setSize(const float radius)
    {
        _size.x = radius;
    }

    float Sphere::getSize() const
    {
        return _size.x;
    }

    void Sphere::setWiresColor(const Color color)
    {
        _wiresColor = color;
    }

    Color Sphere::getWiresColor()
    {
        return _wiresColor;
    }

    VisualElement::Type Sphere::getType() const
    {
        return VisualElement::Type::SPHERE;
    }

    void Sphere::updateModel()
    {
        if (_hasModelLoaded)
            UnloadModel(_model);
        _model = LoadModelFromMesh(GenMeshSphere(_scale.x, _rings, _slices));
        if (!_hasModelLoaded)
            _hasModelLoaded = true;
    }

    void Sphere::adjust()
    {
        _rings = std::min(std::max(32, 32 * ((int)_size.x / 100)), 67);
        _slices = std::min(std::max(32, 32 * ((int)_size.x / 100)), 67);
        Texture2D texture = _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture;
        updateModel();
        updateModelTexture(texture);
    }
};
