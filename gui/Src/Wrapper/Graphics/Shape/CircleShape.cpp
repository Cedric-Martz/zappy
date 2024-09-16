/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** CircleShape.cpp
*/

#include "CircleShape.hpp"

namespace rl
{
    CircleShape::CircleShape(const Vector2 position,
                             const float radius,
                             const Color color)
        : Shape(),
        _radius(radius)
    {
        _position.x = position.x;
        _position.y = position.y;
        _color = color;
    }

    void CircleShape::setRadius(const float radius)
    {
        _radius = radius;
    }

    float CircleShape::getRadius()
    {
        return _radius;
    }

    VisualElement::Type CircleShape::getType() const
    {
        return VisualElement::Type::CIRCLE;
    }

    void CircleShape::draw()
    {
        DrawCircle(_position.x, _position.y, _radius, _color);
    }

    void CircleShape::applyTransform(Transform &transform)
    {
        for (Transform const &tr : transform.getTransforms()) {
            switch (tr.getType()) {
                case Transform::Type::TRANSLATION: {
                    Vector2 pos = tr.transformPoint2D(getPosition2());
                    _position.x = pos.x;
                    _position.y = pos.y;
                    break;
                }
                case Transform::Type::ROTATION:
                    break;
                case Transform::Type::SCALE:
                    _radius += tr.getScale2().x;
                    break;
                default:
                    break;
            }
        }
        transform.clearCheckers();
    }
};
