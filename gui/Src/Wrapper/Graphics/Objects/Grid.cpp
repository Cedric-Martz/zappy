/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Grid.cpp
*/

#include "Grid.hpp"
#include "RayLib.hpp"

namespace rl
{
    Grid::Grid(const int size, const float spacing)
        : _size(size), _spacing(spacing)
    {}

    Grid::~Grid() {}

    int Grid::getSize() const
    {
        return _size;
    }

    float Grid::getSpacing() const
    {
        return _spacing;
    }

    void Grid::setSize(const int size)
    {
        _size = size;
    }

    void Grid::setSpacing(const float spacing)
    {
        _spacing = spacing;
    }

    void Grid::draw()
    {
        DrawGrid(_size, _spacing);
    }
};
