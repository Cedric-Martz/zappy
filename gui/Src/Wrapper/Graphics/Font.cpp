/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Font.cpp
*/

#include "Font.hpp"

namespace rl
{
    CustomFont::CustomFont()
        : _hasFontLoaded(false)
    {}

    CustomFont::CustomFont(const std::string &filename)
        : _hasFontLoaded(true)
    {
        loadFromFile(filename);
    }

    CustomFont::~CustomFont()
    {
        if (isReady() && _hasFontLoaded)
            UnloadFont(_font);
    }

    void CustomFont::loadFromFile(const std::string &filename)
    {
        if (_hasFontLoaded)
            UnloadFont(_font);
        _font = LoadFont(filename.c_str());
    }

    bool CustomFont::isReady() const
    {
        return _hasFontLoaded;
    }

    const Font &CustomFont::getSource() const
    {
        return _font;
    }
};
