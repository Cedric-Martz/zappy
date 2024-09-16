/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Splash.cpp
*/

#include "Splash.hpp"
#include "SplashScreenManager.hpp"
#include "RenderWindow.hpp"

namespace rl
{
    Splash::Splash(const Color color,
                   const float rotation)
        : Text()
    {
        _changeSize = true;
        setRotation(rotation);
        _color = color;

        Vector2 ws = RenderWindow::getInstance().getSize();
        setCharacterSize(0.0195 * ws.x);
        setString(SplashScreenManager::getInstance().run("Assets/splash.splash"));
    }

    Splash::~Splash() {}

    void Splash::draw()
    {
        Text::draw();
        if (_size.x >= 50)
            _changeSize = false;
        else if (_size.x <= 25)
            _changeSize = true;
        if (_changeSize) {
            _size.x += 1;
            _size.y += 1;
        } else {
            _size.x -= 1;
            _size.y -= 1;
        }
    }

    VisualElement::Type Splash::getType() const
    {
        return VisualElement::Type::SPLASH;
    }
};
