/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Notification.cpp
*/

#include "Notification.hpp"
#include "TextureManager.hpp"
#include "AudioManager.hpp"

namespace rl
{
    Notification::Notification(Vector2 position, std::string title, std::string message) :
        _position(position)
    {
        Rectangle rect{};

        if (message.size() > 30) {
            for (int i = 27; i < 30; i++)
                message.insert(message.begin() + i, '.');
            message.insert(message.begin() + 30, '\0');
        }
        if (title.size() > 30) {
            for (int i = 27; i < 30; i++)
                title.insert(title.begin() + i, '.');
            title.insert(title.begin() + 30, '\0');
        }

        _size = Vector2(300, 140);
        rect = Rectangle{position.x, position.y, _size.x, _size.y};
        _rectangle = RectangleShape(rect);
        if (message != "") {
            AudioManager::getInstance().playSound("achievement");
            _rectangle.setTexture(TextureManager::getInstance().loadTexture("Assets/Imgs/interface/achievement.png"));
        } else {
            AudioManager::getInstance().playSound("orb");
            _rectangle.setTexture(TextureManager::getInstance().loadTexture("Assets/Imgs/interface/server_message.png"));
        }
        _rectangle.setTextureRect(Rectangle{0, 0, _size.x, _size.y});
        _rectangle.setScale(1.5);
        _title = Text(title, 20);
        _title.setColor(YELLOW);
        _title.setCenterState(false);
        _message = Text(message, 20);
        _message.setColor(WHITE);
        _message.setCenterState(false);
        _timeBank = 0;
    }

    Notification::~Notification() {}

    void Notification::draw(Vector2 position)
    {
        _rectangle.setPosition(position);
        _title.setPosition(position.x - 70, position.y - 45);
        _message.setPosition(position.x - 70, position.y - 15);

        _rectangle.draw();
        _title.draw();
        _message.draw();
    }

    void Notification::update()
    {
        _timeBank += Clock::getInstance().getDeltaTime().asSeconds();
    }
}
