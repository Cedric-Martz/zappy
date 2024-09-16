/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Cube.cpp
*/

#include "Cube.hpp"
#include "TextureManager.hpp"

namespace rl
{
    Cube::Cube()
        : Model3(),
        _hasTextureLoaded(false),
        _hasMeshLoaded(false),
        _hasModelLoaded(false)
    {
        _position = Vector3(0, 0, 0);
        _size = Vector3(1, 1, 1);
        _rotation = 0;
        _model = LoadModelFromMesh(GenMeshCube(_size.x, _size.y, _size.z));
        _hasMeshLoaded = true;
    }

    Cube::Cube(const std::string &textureFilepath)
        : Model3(),
        _hasTextureLoaded(false),
        _hasMeshLoaded(false),
        _hasModelLoaded(false)
    {
        _position = Vector3(0, 0, 0);
        _size = Vector3(1, 1, 1);
        _rotation = 0;
        _model = LoadModelFromMesh(GenMeshCube(_size.x, _size.y, _size.z));
        _hasMeshLoaded = true;
        loadTextureFromFile(textureFilepath);
    }

    Cube::~Cube() {}

    void Cube::draw()
    {
        if (!_hasTextureLoaded) {
            DrawCubeV(_position, _size, _color);
            DrawCubeWiresV(_position, _size, _wiresColor);
            return;
        }
        DrawModelEx(_model, _position, _rotationAxis, _rotation, _scale, _color);
    }

    void Cube::applyTransform([[maybe_unused]] Transform &transform) {}

    void Cube::update(double deltaTime)
    {
        updateRainbow(deltaTime);
    }

    void Cube::loadTextureFromFile(const std::string &filepath)
    {
        _texture = TextureManager::getInstance().loadTexture(filepath);
        _textureRect = Rectangle(0, 0, _texture.width, _texture.height);
        _hasTextureLoaded = !(_texture.width == 0 || _texture.height == 0);
        if (_hasTextureLoaded)
            updateModelTexture(_texture, MATERIAL_MAP_ALBEDO);
    }

    void Cube::setSize(const Vector3 &size)
    {
        _size = size;
        createTextured();
    }

    void Cube::setSize(const float x, const float y, const float z)
    {
        setSize(Vector3(x, y, z));
    }

    Vector3 Cube::getSize()
    {
        return _size;
    }

    Color Cube::getWiresColor()
    {
        return _wiresColor;
    }

    void Cube::setWiresColor(const Color color)
    {
        _wiresColor = color;
    }

    void Cube::createTextured()
    {
        if (!_hasTextureLoaded)
            return;
        if (_hasModelLoaded)
            UnloadModel(_model);
        _model = LoadModelFromMesh(GenMeshCube(_size.x, _size.y, _size.z));

        _material = LoadMaterialDefault();
        _material.maps[MATERIAL_MAP_DIFFUSE].texture = _texture;

        _model.materials[0] = _material;
        _hasModelLoaded = true;
    }

    VisualElement::Type Cube::getType() const
    {
        return VisualElement::Type::CUBE;
    }

    bool Cube::isHovered()
    {
        _ray = GetScreenToWorldRay(Mouse::getInstance().getPosition(), _camera->getSource());
        _collision = GetRayCollisionBox(_ray,
            BoundingBox(
                    Vector3(_position.x - _size.x / 2,
                            _position.y - _size.y / 2,
                            _position.z - _size.z / 2),
                    Vector3(
                            _position.x + _size.x / 2,
                            _position.y + _size.y / 2,
                            _position.z + _size.z / 2)
            )
        );
        return _collision.hit;
    }
};
