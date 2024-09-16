/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Camera2.cpp
*/

#include "Camera2.hpp"

namespace rl
{
    Camera2::Camera2() {}

    Camera2::~Camera2() {}

    Camera2D &Camera2::getSource()
    {
        return _camera;
    }
};
