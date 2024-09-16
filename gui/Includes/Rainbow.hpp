/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Rainbow.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RAINBOW_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RAINBOW_HPP
    #include "RayLib.hpp"

namespace rl
{
    class Rainbow {
    public:
        static Color getColorByTime(const double time, const double speed = 0.5f);
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RAINBOW_HPP*/
