/*
** EPITECH PROJECT, 2024
** Global-Game-Jam---2024---Make-Me-Laugh
** File description:
** Button.cpp
*/

#include "Button.hpp"
#include "TextureManager.hpp"
#include "AudioManager.hpp"

namespace rl
{
    Button::Button(
            const Rectangle rectangle,
            const Color color,
            std::function<void()> onClick,
            const std::string &texture,
            const std::string &textureOnHover
    )
            : RectangleShape(rectangle, color),
              _onClickFunction(onClick),
              _isHovered(false),
              _hasGeneralTextureLoaded(false),
              _hasOnHoverTextureLoaded(false)
    {
        _position.x = rectangle.x;
        _position.y = rectangle.y;
        _size.x = rectangle.width;
        _size.y = rectangle.height;
        _origin.x = _size.x / 2.0f;
        _origin.y = _size.y / 2.0f;
        _color = color;
        if (texture.size() != 0) {
            _generalTexture = TextureManager::getInstance().loadTexture(texture);
            if (_generalTexture.width == 0 || _generalTexture.height == 0)
                return;
            _hasGeneralTextureLoaded = true;
            setTexture(_generalTexture);
            setTextureRect({0, 0,
                            static_cast<float>(_texture.width),
                            static_cast<float>(_texture.height)});
        }
        if (textureOnHover.size() != 0) {
            _textureOnHover = TextureManager::getInstance().loadTexture(textureOnHover);
            if (_textureOnHover.width == 0 || _textureOnHover.height == 0)
                return;
            _hasOnHoverTextureLoaded = true;
        }
        AudioManager::getInstance().loadSound("Assets/Sounds/minecraft_click.mp3", "button_click");
    }

    Button::~Button() {}

    void Button::draw()
    {
        if (!_hasGeneralTextureLoaded || !_hasOnHoverTextureLoaded) {
            RectangleShape::draw();
            return;
        }
        Rectangle dest(_position.x, _position.y, _size.x, _size.y);
        DrawTexturePro(_texture, _textureRect, dest, _origin, _rotation, _color);
    }

    void Button::update(double deltaTime)
    {
        updateRainbow(deltaTime);
        if (isClicked()) {
            AudioManager::getInstance().playSound("button_click");
            _onClickFunction();
        }
        if (RectangleShape::isHovered() && !_isHovered) {
            _isHovered = true;
            setTexture(_textureOnHover);
        }
        if (!RectangleShape::isHovered() && _isHovered) {
            _isHovered = false;
            setTexture(_generalTexture);
        }
    }
}