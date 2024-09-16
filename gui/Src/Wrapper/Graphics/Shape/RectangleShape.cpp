/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** RectangleShape.cpp
*/

#include "Transform.hpp"
#include "RectangleShape.hpp"

namespace rl
{
    RectangleShape::RectangleShape(const Rectangle rectangle, const Color color)
        : Shape()
    {
        _size = {rectangle.width, rectangle.height, 0};
        _position.x = rectangle.x;
        _position.y = rectangle.y;
        _origin.x = _size.x / 2.0f;
        _origin.y = _size.y / 2.0f;
        _color = color;
        _textureRect.width = 0.0f;
        _textureRect.height = 0.0f;
        _rotation = 0.0f;
    }

    Rectangle RectangleShape::getBounds() const
    {
        return Rectangle(_position.x - _origin.x,
                         _position.y - _origin.y,
                         _size.x,
                         _size.y);
    }

    Vector2 RectangleShape::getSize() const
    {
        return Vector2(_size.x, _size.y);
    }

    VisualElement::Type RectangleShape::getType() const
    {
        return VisualElement::Type::RECTANGLE;
    }

    void RectangleShape::setBounds(const Rectangle rectangle)
    {
        _position.x = rectangle.x;
        _position.y = rectangle.y;
        _size.x = rectangle.width;
        _size.y = rectangle.height;
    }

    void RectangleShape::setSize(const Vector2 &size)
    {
        _size.x = size.x;
        _size.y = size.y;
    }

    void RectangleShape::setSize(const float x, const float y)
    {
        setSize(Vector2(x, y));
    }

    void RectangleShape::draw()
    {
        if (_textureRect.width == 0 || _textureRect.height == 0)
            DrawRectanglePro(
                    Rectangle(_position.x, _position.y, _size.x, _size.y),
                    _origin,
                    _rotation,
                    _color
            );
        else {
            DrawTextureEx(
                    _texture,
                    getPosition2() - _origin,
                    _rotation,
                    getScale2().x,
                    _color
            );
        }
    }

    void RectangleShape::applyTransform(Transform &transform)
    {
        for (Transform const &tr : transform.getTransforms()) {
            switch (tr.getType()) {
                case Transform::Type::TRANSLATION: {
                    Vector2 pos = tr.transformPoint2D(getPosition2());
                    _position.x = pos.x;
                    _position.y = pos.y;
                    break;
                }
                case Transform::Type::ROTATION: {
                    _rotation += tr.getRotation();
                    break;
                }
                case Transform::Type::SCALE:
                    _size.x += tr.getScale2().x;
                    _size.y += tr.getScale2().y;
                    break;
                default:
                    break;
            }
        }
        transform.clearCheckers();
    }

    void RectangleShape::update(double deltaTime)
    {
        updateRainbow(deltaTime);
    }

    bool RectangleShape::isHovered()
    {
        return CheckCollisionPointRec(Mouse::getInstance().getPosition(), getBounds());
    }
};
