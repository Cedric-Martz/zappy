/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Mouse.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MOUSE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MOUSE_HPP
    #include "RayLib.hpp"

namespace rl
{
    class Mouse {
    public:
        static Mouse &getInstance();

        bool isButtonPressed(const MouseButton button = MouseButton::MOUSE_BUTTON_LEFT) const;

        Vector2 getPosition() const;
        Vector2 getMouseWheelMove() const;

        void setPosition(int x, int y);
        void setPosition(const Vector2 &vector);
        void setCursor(const MouseCursor cursor);
    private:
        Mouse();
        ~Mouse();
        Mouse(const Mouse&) = delete;
        Mouse& operator=(const Mouse&) = delete;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MOUSE_HPP*/
