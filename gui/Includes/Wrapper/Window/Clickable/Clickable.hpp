/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Clickable.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CLICKABLE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CLICKABLE_HPP
    #include "Mouse.hpp"

namespace rl
{
    class Clickable {
    public:
        virtual ~Clickable();

        virtual bool isHovered() = 0;
        bool isClicked(const MouseButton button = MouseButton::MOUSE_BUTTON_LEFT);

    protected:
        Clickable();
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CLICKABLE_HPP*/
