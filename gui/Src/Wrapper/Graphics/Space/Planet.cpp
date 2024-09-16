/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Planet.cpp
*/

#include "Planet.hpp"
#include "Cube.hpp"
#include "TextureManager.hpp"

namespace rl
{
    Planet::Planet()
        : StellarObject(),
        _textureRotating(true),
        _textureRotation(0.0f),
        _textureRotationSpeed(25.0f)
    {
        _isSatellite = false;
        _rotationAxis = Vector3(0, 0, 0);
        _bboxColor = TRANSPARENT;
    }

    Planet::Planet(const std::string &id,
                   const Vector3 &position,
                   const float size,
                   const Color color,
                   const std::shared_ptr<Camera3> &camera,
                   const float orbitRadius,
                   const float rotationSpeed,
                   const StellarObject::OrbitAxis orbitAxis)
        : StellarObject(),
        _textureRotating(true),
        _textureRotation(0.0f),
        _textureRotationSpeed(25.0f)
    {
        _position = position;
        _size.x = size;
        _color = color;
        _camera = camera;
        _isSatellite = false;
        _rotationAxis = Vector3(0, 0, 0);
        _bboxColor = TRANSPARENT;
        _orbitRotation = 0.0f;
        _orbitRadius = orbitRadius;
        _rotationSpeed = rotationSpeed;
        _orbitAxis = orbitAxis;
        _id = id;
    }

    Planet::Planet(const std::string &id,
                   const std::string &modelFilepath,
                   const Vector3 &position,
                   const float size,
                   const Color color,
                   const std::shared_ptr<Camera3> &camera,
                   const float orbitRadius,
                   const float rotationSpeed,
                   const StellarObject::OrbitAxis orbitAxis)
        : StellarObject(),
        _textureRotating(true),
        _textureRotation(0.0f),
        _textureRotationSpeed(25.0f)
    {
        _position = position;
        _size.x = size;
        _color = color;
        _camera = camera;
        _isSatellite = false;
        _rotationAxis = Vector3(0, 0, 0);
        _bboxColor = TRANSPARENT;
        _orbitRotation = 0.0f;
        _orbitRadius = orbitRadius;
        _rotationSpeed = rotationSpeed;
        _orbitAxis = orbitAxis;
        _id = id;
        loadFromFile(modelFilepath);
    }

    Planet::~Planet() {}

    void Planet::update(double deltaTime)
    {
        for (auto &[_, object] : _objects)
            object->update(deltaTime);
        if (_isSatellite)
            _orbitRotation += 365.0f / 360.0f * (5.0f * _rotationSpeed) * _rotationSpeed;

        if (_textureRotating)
            _textureRotation += _textureRotationSpeed * deltaTime;
    }

    void Planet::draw()
    {
        rlPushMatrix();
        if (!_isSatellite) {
            rlRotatef(_orbitRotation, 0.25f, 1.0f, 0.0f);
            _transformedPosition = _position * rlGetMatrixTransform();

            rlTranslatef(_position.x, _position.y, _position.z);
            rlRotatef(_textureRotation, 0.0f, 1.0f, 0.0f);
            rlTranslatef(-_position.x, -_position.y, -_position.z);

            Sphere::draw();
        }

        for (auto &[_, object] : _objects)
            object->draw();

        if (_isSatellite) {
            _parent->applyTransformations();

            rlTranslatef(_position.x, _position.y, _position.z);
            rlRotatef(_orbitRotation + (_index * (360.0f / static_cast<float>(_parent->getSatellitesNumber()))),
                      0.0f,
                      _orbitAxis == OrbitAxis::Y,
                      _orbitAxis == OrbitAxis::Z);
            rlTranslatef(_orbitRadius, 0.0f, 0.0f);
            _transformedPosition = _position * rlGetMatrixTransform();

            rlRotatef(_textureRotation, 0.0f, 1.0f, 0.0f);

            Sphere::draw();
        }
        rlPopMatrix();
    }

    void Planet::applyTransform([[maybe_unused]] Transform &transform) {}

    VisualElement::Dimension Planet::getDimension() const
    {
        return VisualElement::Dimension::DIMENSION3;
    }

    VisualElement::Type Planet::getType() const
    {
        return VisualElement::Type::PLANET;
    }

    void Planet::setTextureRotating(const bool state)
    {
        _textureRotating = state;
    }

    void Planet::setTextureRotationSpeed(const float speed)
    {
        _textureRotationSpeed = speed;
    }
};
