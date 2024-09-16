/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Item.cpp
*/

#include "Item.hpp"

namespace rl
{
    Item::Item(const Texture &texture)
        : Sprite(texture), _amount(0)
    {
        _text.setColor(WHITE);
        _text.setCharacterSize(25);
        _text_shadow.setColor(BLACK);
        _text_shadow.setCharacterSize(25);
    }

    Item::Item(const Texture &texture, const Rectangle &rectangle)
        : Sprite(texture, rectangle)
    {
    }

    Item::~Item()
    {
    }

    void Item::update([[maybe_unused]] double deltaTime)
    {
        _text.setPosition(_position.x + 5, 120);
        _text.setString(std::to_string(_amount));
        _text_shadow.setPosition(_position.x + 4, 120);
        _text_shadow.setString(std::to_string(_amount));
    }

    void Item::draw()
    {
        Sprite::draw();
        _text_shadow.draw();
        _text.draw();
    }

    void Item::setAmount(int amount)
    {
        _amount = amount;
    }

    int Item::getAmount()
    {
        return _amount;
    }

    Text Item::getText()
    {
        return _text;
    }
}
