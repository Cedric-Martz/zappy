/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** StellarObject.cpp
*/

#include "StellarObject.hpp"

namespace rl
{
    StellarObject::StellarObject()
        : Sphere(),
          _orbitRotation(0.0f),
          _orbitRadius(0.0f),
          _rotationSpeed(0.0f),
          _orbitAxis(OrbitAxis::Y),
          _transformedPosition({0, 0, 0}),
          _index(0)
    {}

    StellarObject::~StellarObject() {}

    void StellarObject::addSatellite(std::shared_ptr<StellarObject> planet,
                                     std::shared_ptr<StellarObject> parent)
    {
        const std::string &id = planet->getId();

        if (_objects.contains(id))
            return;
        planet->_parent = parent;
        planet->_index = _objects.size();
        _objects[id] = planet;
        setSatelliteState(id, true);

    }

    void StellarObject::setSatelliteState(const std::string &id, const bool status)
    {
        if (!_objects.contains(id))
            return;
        _objects[id]->_isSatellite = status;
    }

    std::shared_ptr<StellarObject> StellarObject::getSatellite(const std::string &id)
    {
        if (!_objects.contains(id))
            return nullptr;
        return _objects[id];
    }

    size_t StellarObject::getSatellitesNumber() const
    {
        return _objects.size();
    }

    std::string StellarObject::getId() const
    {
        return _id;
    }

    VisualElement::Type StellarObject::getType() const
    {
        return VisualElement::Type::STELLAR_OBJECT;
    }

    Vector3 StellarObject::getTransformedPosition() const
    {
        return _transformedPosition;
    }

    void StellarObject::setOrbitRadius(const float orbitRadius)
    {
        _orbitRadius = orbitRadius;
    }

    float StellarObject::getOrbitRadius() const
    {
        return _orbitRadius;
    }

    void StellarObject::setRotationSpeed(const float rotationSpeed)
    {
        _rotationSpeed = rotationSpeed;
    }

    float StellarObject::getRotationSpeed() const
    {
        return _rotationSpeed;
    }

    void StellarObject::setOrbitAxis(const StellarObject::OrbitAxis orbitAxis)
    {
        _orbitAxis = orbitAxis;
    }

    StellarObject::OrbitAxis StellarObject::getOrbitAxis() const
    {
        return _orbitAxis;
    }

    void StellarObject::applyTransformations() {
        if (_isSatellite && _parent) {
            _parent->applyTransformations();
            rlTranslatef(_position.x, _position.y, _position.z);
            rlRotatef(_orbitRotation + (_index * (360.0f / static_cast<float>(_parent->getSatellitesNumber()))),
                      0.0f,
                      _orbitAxis == OrbitAxis::Y ? 1.0f : 0.0f,
                      _orbitAxis == OrbitAxis::Z ? 1.0f : 0.0f);
            rlTranslatef(_orbitRadius, 0.0f, 0.0f);
        }
    }
}
