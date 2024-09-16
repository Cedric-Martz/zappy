/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Transform.cpp
*/

#include "Transform.hpp"

namespace rl
{
    Transform::Transform()
        : _hasTranslated(false), _hasRotated(false), _hasScaled(false)
    {
        identity();
    }

    Transform::~Transform() {}

    void Transform::clear()
    {
        identity();
        clearCheckers();
    }

    void Transform::clearCheckers()
    {
        _hasTranslated = false;
        _hasRotated = false;
        _hasScaled = false;
    }

    Transform Transform::getInverse() const
    {
        Transform transform;

        transform._matrix = MatrixInvert(transform._matrix);
        return transform;
    }

    Transform::Type Transform::getType() const
    {
        return _type;
    }

    std::vector<Transform> const &Transform::getTransforms() const
    {
        return _transforms;
    }

    Transform &Transform::combine(const Transform &transform)
    {
        _matrix = MatrixMultiply(_matrix, transform._matrix);
        return *this;
    }

    Vector2 Transform::transformPoint2D(float x, float y) const
    {
        return {_matrix.m0 * x + _matrix.m4 * y + _matrix.m12,
                _matrix.m1 * x + _matrix.m5 * y + _matrix.m13};
    }

    Vector2 Transform::transformPoint2D(const Vector2 &vector) const
    {
        return transformPoint2D(vector.x, vector.y);
    }

    void Transform::identity()
    {
        _matrix = MatrixIdentity();
    }
};
