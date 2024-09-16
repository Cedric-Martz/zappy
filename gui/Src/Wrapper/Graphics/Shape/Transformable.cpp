/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Transformable.cpp
*/

#include "Transformable.hpp"

namespace rl
{
    Transformable::Transformable()
        : _position(Vector3(0, 0, 0)), _rotation(0), _scale(Vector3(1, 1, 1))
    {}

    Transformable::~Transformable() {}

    /* 2D SECTION */

    void Transformable::setPosition(float x, float y)
    {
        _position.x = x;
        _position.y = y;
    }

    void Transformable::setPosition(const Vector2 &vector)
    {
        setPosition(vector.x, vector.y);
    }

    void Transformable::setRotation(float angle)
    {
        if (angle < 0)
            angle += 360;
        if (angle > 359)
            angle -= 360;
        _rotation = angle;
    }

    void Transformable::setScale(float x, float y)
    {
        _scale.x = x;
        _scale.y = y;
    }

    void Transformable::setScale(const Vector2 &vector)
    {
        setScale(vector.x, vector.y);
    }

    void Transformable::setScale(const float scale)
    {
        setScale(scale, scale, scale);
    }

    Vector2 Transformable::getPosition2() const
    {
        return Vector2(_position.x, _position.y);
    }

    float Transformable::getRotation() const
    {
        return _rotation;
    }

    Vector2 Transformable::getScale2() const
    {
        return Vector2(_scale.x, _scale.y);
    }

    /* 3D SECTION */

    void Transformable::setPosition(float x, float y, float z)
    {
        _position.x = x;
        _position.y = y;
        _position.z = z;
    }

    void Transformable::setPosition(const Vector3 &vector)
    {
        setPosition(vector.x, vector.y, vector.z);
    }

    void Transformable::setScale(float x, float y, float z)
    {
        _scale.x = x;
        _scale.y = y;
        _scale.z = z;
    }

    void Transformable::setScale(const Vector3 &vector)
    {
        setScale(vector.x, vector.y, vector.z);
    }

    Vector3 Transformable::getPosition3() const
    {
        return _position;
    }

    Vector3 Transformable::getScale3() const
    {
        return _scale;
    }
};
