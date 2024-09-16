/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Texture.cpp
*/

#include "Sprite.hpp"

namespace rl
{
    Sprite::Sprite(const Texture &texture)
        : VisualElement()
    {
        _texture = texture;
        _textureRect = Rectangle(0, 0, _texture.width, _texture.height);
        _size.x = _textureRect.width;
        _size.y = _texture.height;
        _origin.x = (float)_texture.width / 2.0f;
        _origin.y = (float)_texture.height / 2.0f;
        _color = WHITE;
    }

    Sprite::Sprite(const Texture &texture, const Rectangle &rectangle)
    {
        _texture = texture;
        _textureRect = rectangle;
        _size.x = _textureRect.width;
        _size.y = _texture.height;
        _origin.x = rectangle.width;
        _origin.y = rectangle.height;
        _color = WHITE;
    }

    Sprite::~Sprite() {}

    void Sprite::draw()
    {
        Rectangle dest(_position.x, _position.y, _size.x * _scale.x, _size.y * _scale.y);

        DrawTexturePro(_texture, _textureRect, dest, _origin, _rotation, _color);
    }

    void Sprite::applyTransform(Transform &transform)
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
    }

    void Sprite::update(double deltaTime)
    {
        updateRainbow(deltaTime);
    }

    VisualElement::Type Sprite::getType() const
    {
        return VisualElement::Type::SPRITE;
    }

    void Sprite::flip()
    {
        Image image = LoadImageFromTexture(_texture);

        ImageFlipVertical(&image);
        UpdateTexture(_texture, image.data);
    }
};
