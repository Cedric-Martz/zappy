/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Movements.cpp
*/

#include "Transform.hpp"

namespace rl
{
    Transform &Transform::translate(float x, float y)
    {
        Transform transform;

        if (_hasTranslated)
            return *this;
        _hasTranslated = true;
        transform._type = Type::TRANSLATION;
        transform._position = Vector3(x, y, 0);
        transform._matrix = MatrixTranslate(x, y, 0);
        _transforms.push_back(transform);
        return *this;
    }

    Transform &Transform::translate(const Vector2 &vector)
    {
        return translate(vector.x, vector.y);
    }

    Transform &Transform::rotate(const float angle)
    {
        Transform transform;

        if (_hasRotated)
            return *this;
        _hasRotated = true;
        transform._type = Type::ROTATION;
        transform._rotation = angle;
        _transforms.push_back(transform);
        return *this;
    }

    Transform &Transform::scale(float radius)
    {
        return scale(radius, radius);
    }

    Transform &Transform::scale(float x, float y)
    {
        Transform transform;

        if (_hasScaled)
            return *this;
        _hasScaled = true;
        transform._type = Type::SCALE;
        transform._scale = Vector3(x, y, 0);
        _transforms.push_back(transform);
        return *this;
    }

    Transform &Transform::scale(const Vector2 &vector)
    {
        return scale(vector.x, vector.y);
    }
};
