/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** VisualElement.cpp
*/

#include "VisualElement.hpp"
#include "Rainbow.hpp"
#include "Color.hpp"

namespace rl
{
    VisualElement::VisualElement()
        : _texture({.id = 0, .width = 0, .height = 0, .mipmaps = 1, .format = 0}),
          _textureRect({0, 0, 0, 0}),
          _color(WHITE),
          _origin(Vector2(0, 0)),
          _size({1, 1, 1}),
          _isRainbow(false),
          _rainbowTimeBank(0),
          _rainbowSpeed(0.5f),
          _displayed(true)
    {}

    VisualElement::~VisualElement() {}

    void VisualElement::draw() {}

    void VisualElement::setTexture(const Texture texture)
    {
        _texture = texture;
    }

    void VisualElement::setTextureRect(const Rectangle textureRect)
    {
        _textureRect = textureRect;
    }

    void VisualElement::setColor(const Color color)
    {
        _color = color;
    }

    void VisualElement::setOrigin(const Vector2 &vector)
    {
        _origin = vector;
    }

    void VisualElement::setOrigin(int x, int y)
    {
        setOrigin({static_cast<float>(x), static_cast<float>(y)});
    }

    Texture VisualElement::getTexture() const
    {
        return _texture;
    }

    Rectangle VisualElement::getTextureRect() const
    {
        return _textureRect;
    }

    Color VisualElement::getColor() const
    {
        return _color;
    }

    Vector2 VisualElement::getOrigin() const
    {
        return _origin;
    }

    VisualElement::Dimension VisualElement::getDimension() const
    {
        return VisualElement::Dimension::DIMENSION2;
    }

    bool VisualElement::isRainbow() const
    {
        return _isRainbow;
    }

    void VisualElement::setRainbowStatus(const bool status)
    {
        _isRainbow = status;
    }

    double VisualElement::getRainbowSpeed() const
    {
        return _rainbowSpeed;
    }

    void VisualElement::setRainbowSpeed(const double speed)
    {
        _rainbowSpeed = speed;
    }

    void VisualElement::updateRainbow(double deltaTime)
    {
        if (!_isRainbow)
            return;
        _rainbowTimeBank += (deltaTime * 1000000.f);
        Color color = Rainbow::getColorByTime(_rainbowTimeBank.asSeconds(), _rainbowSpeed);
        if (_color != color)
            _color = color;
    }

    void VisualElement::setDisplayed(const bool state)
    {
        _displayed = state;
    }

    bool VisualElement::getDisplayed() const
    {
        return _displayed;
    }
};
