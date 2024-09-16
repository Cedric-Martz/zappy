/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Mouse.cpp
*/

#include "Mouse.hpp"

namespace rl
{
    Mouse::Mouse() {}

    Mouse::~Mouse() {}

    Mouse &Mouse::getInstance()
    {
        static Mouse mouse;
        return mouse;
    }

    bool Mouse::isButtonPressed(const MouseButton button) const
    {
        return IsMouseButtonPressed(button);
    }

    Vector2 Mouse::getPosition() const
    {
        return GetMousePosition();
    }

    Vector2 Mouse::getMouseWheelMove() const
    {
        return GetMouseWheelMoveV();
    }

    void Mouse::setPosition(int x, int y)
    {
        SetMousePosition(x, y);
    }

    void Mouse::setPosition(const Vector2 &vector)
    {
        SetMousePosition(vector.x, vector.y);
    }

    void Mouse::setCursor(const MouseCursor cursor)
    {
        SetMouseCursor(cursor);
    }
};
