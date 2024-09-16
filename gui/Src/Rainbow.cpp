/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Rainbow.cpp
*/

#include "Rainbow.hpp"
#include <cmath>

namespace rl
{
    Color Rainbow::getColorByTime(const double time, const double speed)
    {
        double r = std::sin(speed * time) * 127 + 128;
        double g = std::sin(speed * time + 2 * M_PI / 3) * 127 + 128;
        double b = std::sin(speed * time + 4 * M_PI / 3) * 127 + 128;

        return Color(
                static_cast<unsigned char>(r),
                static_cast<unsigned char>(g),
                static_cast<unsigned char>(b),
                255);
    }
};
