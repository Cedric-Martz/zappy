/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Text.cpp
*/

#include "Text.hpp"

namespace rl
{
    Text::Text()
        : VisualElement(),
        _characterSize(15),
        _hasFontLoaded(false),
        _spacing(3),
        _isCentered(true)
    {
        updateOrigin();
    }

    Text::Text(const std::string &string, const unsigned int characterSize)
        : _string(string),
        _characterSize(characterSize),
        _hasFontLoaded(false),
        _spacing(3),
        _isCentered(true)
    {
        updateOrigin();
        _color = BLACK;
        _rotation = 0;
    }

    Text::Text(const std::string &string, const CustomFont &font, const unsigned int characterSize)
        : _string(string),
        _characterSize(characterSize),
        _font(font),
        _hasFontLoaded(true),
        _spacing(3),
        _isCentered(true)
    {
        updateOrigin();
        _color = BLACK;
        _rotation = 0;
    }

    std::string Text::getString() const
    {
        return _string;
    }

    unsigned int Text::getCharacterSize() const
    {
        return _characterSize;
    }

    CustomFont Text::getFont() const
    {
        return _font;
    }

    Vector2 Text::getSize() const
    {
        return Vector2(_size.x, _size.y);
    }

    float Text::getSpacing() const
    {
        return _spacing;
    }

    void Text::setString(const std::string &string)
    {
        _string = string;
        if (_isCentered)
            updateOrigin();
    }

    void Text::setCharacterSize(const unsigned int characterSize)
    {
        _characterSize = characterSize;
        if (_isCentered)
            updateOrigin();
    }

    void Text::setFont(const CustomFont &font)
    {
        _font = font;
        if (_isCentered)
            updateOrigin();
    }

    void Text::setSize(const Vector2 &size)
    {
        _size.x = size.x;
        _size.y = size.y;
    }

    void Text::setSpacing(const float spacing)
    {
        _spacing = spacing;
    }

    bool Text::isEmpty() const
    {
        return _string.size() == 0;
    }

    bool Text::isCentered() const
    {
        return _isCentered;
    }

    void Text::setCenterState(const bool isCentered)
    {
        _isCentered = isCentered;
        if (_isCentered)
            updateOrigin();
        else
            _origin = Vector2(0, 0);
    }

    void Text::draw()
    {
        if (_hasFontLoaded)
            DrawTextPro(_font.getSource(), _string.c_str(), getPosition2(), _origin, _rotation, _characterSize * _scale.x, _spacing, _color);
        else {
            DrawTextPro(GetFontDefault(), _string.c_str(), getPosition2(), _origin, _rotation, _characterSize * _scale.x, _spacing, _color);
        }
    }

    void Text::applyTransform(Transform &transform)
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
                    _characterSize += tr.getScale2().x;
                    break;
                default:
                    break;
            }
        }
    }

    void Text::update(double deltaTime)
    {
        updateRainbow(deltaTime);
    }

    VisualElement::Type Text::getType() const
    {
        return VisualElement::Type::TEXT;
    }

    bool Text::isHovered()
    {
        Rectangle rectangle(_position.x - _origin.x,
                            _position.y - _origin.y,
                            _size.x,
                            _size.y);
        return CheckCollisionPointRec(Mouse::getInstance().getPosition(), rectangle);
    }

    void Text::updateOrigin()
    {
        if (_hasFontLoaded) {
            Vector2 size = MeasureTextEx(_font.getSource(), _string.c_str(), _characterSize, _spacing);
            _size.x = size.x;
            _size.y = size.y;
            _origin.x = _size.x / 2.0f;
            _origin.y = _size.y / 2.0f;
        } else {
            Vector2 size = MeasureTextEx(GetFontDefault(), _string.c_str(), _characterSize, _spacing);
            _size.x = size.x;
            _size.y = size.y;
            _origin.x = _size.x / 2.0f;
            _origin.y = _size.y / 2.0f;
        }
    }
};
