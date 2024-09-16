/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Notification.hpp
*/

#include "RectangleShape.hpp"
#include "Text.hpp"
#include "Clock.hpp"

namespace rl
{
    class Notification {
    public:
        Notification(Vector2 position, std::string title, std::string message);

        ~Notification();

        void draw(Vector2 position);
        void update();

        RectangleShape getRectangle() { return _rectangle; }
        Text getTitle() { return _title; }
        Text getMessage() { return _message; }
        Vector2 getPosition() { return _position; }
        void setPosition(Vector2 position) { _position = position; }
        float getTimeBank() { return _timeBank; }
        void setSize(Vector2 size) { _size = size; }
        Vector2 getSize() { return _size; }

        bool operator==(const Notification& other) const {
            return _timeBank == other._timeBank;
        }
    private:
        Vector2 _position;
        RectangleShape _rectangle;
        Text _title;
        Text _message;
        float _timeBank;
        Vector2 _size;
    };
}