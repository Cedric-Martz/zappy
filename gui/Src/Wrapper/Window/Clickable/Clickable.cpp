/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Clickable.cpp
*/

#include "Clickable.hpp"

namespace rl
{
    Clickable::Clickable() {}

    Clickable::~Clickable() {}

    bool Clickable::isClicked(const MouseButton button)
    {
        return isHovered() && Mouse::getInstance().isButtonPressed(button);
    }
};
