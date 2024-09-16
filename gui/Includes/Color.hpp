/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** RayLib.hpp
*/

#ifndef COLOR_HPP
    #define COLOR_HPP

    #include <raylib.h>

static bool operator==(const Color &a, const Color &b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

static bool operator!=(const Color &a, const Color &b)
{
    return !(a == b);
}

#endif /*!COLOR_HPP*/
