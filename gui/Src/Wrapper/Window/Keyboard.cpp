/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Keyboard.cpp
*/

#include "Keyboard.hpp"

namespace rl
{
    Keyboard::Keyboard()
        : _Azerty({
            {KeyboardKey::KEY_PERIOD,        {KeyboardKey::KEY_COMMA, true, '.'}},
            {KeyboardKey::KEY_SLASH,         {KeyboardKey::KEY_PERIOD, true, '/'}},
            {KeyboardKey::KEY_MINUS,         {KeyboardKey::KEY_SIX, false, '-'}},
            {KeyboardKey::KEY_ZERO,          {KeyboardKey::KEY_ZERO, true, '0'}},
            {KeyboardKey::KEY_ONE,           {KeyboardKey::KEY_ONE, true, '1'}},
            {KeyboardKey::KEY_TWO,           {KeyboardKey::KEY_TWO, true, '2'}},
            {KeyboardKey::KEY_THREE,         {KeyboardKey::KEY_THREE, true, '3'}},
            {KeyboardKey::KEY_FOUR,          {KeyboardKey::KEY_FOUR, true, '4'}},
            {KeyboardKey::KEY_FIVE,          {KeyboardKey::KEY_FIVE, true, '5'}},
            {KeyboardKey::KEY_SIX,           {KeyboardKey::KEY_SIX, true, '6'}},
            {KeyboardKey::KEY_SEVEN,         {KeyboardKey::KEY_SEVEN, true, '7'}},
            {KeyboardKey::KEY_EIGHT,         {KeyboardKey::KEY_EIGHT, true, '8'}},
            {KeyboardKey::KEY_NINE,          {KeyboardKey::KEY_NINE, true, '9'}},
            {KeyboardKey::KEY_EQUAL,         {KeyboardKey::KEY_EQUAL, false, '='}},
            {KeyboardKey::KEY_A,             {KeyboardKey::KEY_Q, false, 'a'}},
            {KeyboardKey::KEY_B,             {KeyboardKey::KEY_B, false, 'b'}},
            {KeyboardKey::KEY_C,             {KeyboardKey::KEY_C, false, 'c'}},
            {KeyboardKey::KEY_D,             {KeyboardKey::KEY_D, false, 'd'}},
            {KeyboardKey::KEY_E,             {KeyboardKey::KEY_E, false, 'e'}},
            {KeyboardKey::KEY_F,             {KeyboardKey::KEY_F, false, 'f'}},
            {KeyboardKey::KEY_G,             {KeyboardKey::KEY_G, false, 'g'}},
            {KeyboardKey::KEY_H,             {KeyboardKey::KEY_H, false, 'h'}},
            {KeyboardKey::KEY_I,             {KeyboardKey::KEY_I, false, 'i'}},
            {KeyboardKey::KEY_J,             {KeyboardKey::KEY_J, false, 'j'}},
            {KeyboardKey::KEY_K,             {KeyboardKey::KEY_K, false, 'k'}},
            {KeyboardKey::KEY_Q,             {KeyboardKey::KEY_A, false, 'q'}},
            {KeyboardKey::KEY_L,             {KeyboardKey::KEY_L, false, 'l'}},
            {KeyboardKey::KEY_M,             {KeyboardKey::KEY_SEMICOLON, false, 'm'}},
            {KeyboardKey::KEY_N,             {KeyboardKey::KEY_N, false, 'n'}},
            {KeyboardKey::KEY_O,             {KeyboardKey::KEY_O, false, 'o'}},
            {KeyboardKey::KEY_P,             {KeyboardKey::KEY_P, false, 'p'}},
            {KeyboardKey::KEY_R,             {KeyboardKey::KEY_R, false, 'r'}},
            {KeyboardKey::KEY_S,             {KeyboardKey::KEY_S, false, 's'}},
            {KeyboardKey::KEY_T,             {KeyboardKey::KEY_T, false, 't'}},
            {KeyboardKey::KEY_U,             {KeyboardKey::KEY_U, false, 'u'}},
            {KeyboardKey::KEY_V,             {KeyboardKey::KEY_V, false, 'v'}},
            {KeyboardKey::KEY_W,             {KeyboardKey::KEY_Z, false, 'w'}},
            {KeyboardKey::KEY_X,             {KeyboardKey::KEY_X, false, 'x'}},
            {KeyboardKey::KEY_Y,             {KeyboardKey::KEY_Y, false, 'y'}},
            {KeyboardKey::KEY_Z,             {KeyboardKey::KEY_W, false, 'z'}},
            {KeyboardKey::KEY_SPACE,         {KeyboardKey::KEY_SPACE, false, ' '}},
            {KeyboardKey::KEY_ENTER,         {KeyboardKey::KEY_ENTER, false, '\0'}},
            {KeyboardKey::KEY_TAB,           {KeyboardKey::KEY_TAB, false, '\0'}},
            {KeyboardKey::KEY_BACKSPACE,     {KeyboardKey::KEY_BACKSPACE, false, '\0'}},
            {KeyboardKey::KEY_DELETE,        {KeyboardKey::KEY_DELETE, false, '\0'}},
            {KeyboardKey::KEY_RIGHT,         {KeyboardKey::KEY_RIGHT, false, '\0'}},
            {KeyboardKey::KEY_LEFT,          {KeyboardKey::KEY_LEFT, false, '\0'}},
            {KeyboardKey::KEY_DOWN,          {KeyboardKey::KEY_DOWN, false, '\0'}},
            {KeyboardKey::KEY_UP,            {KeyboardKey::KEY_UP, false, '\0'}},
            {KeyboardKey::KEY_PAGE_UP,       {KeyboardKey::KEY_PAGE_UP, false, '\0'}},
            {KeyboardKey::KEY_PAGE_DOWN,     {KeyboardKey::KEY_PAGE_DOWN, false, '\0'}},
            {KeyboardKey::KEY_CAPS_LOCK,     {KeyboardKey::KEY_CAPS_LOCK, false, '\0'}},
            {KeyboardKey::KEY_F1,            {KeyboardKey::KEY_F1, false, '\0'}},
            {KeyboardKey::KEY_F2,            {KeyboardKey::KEY_F2, false, '\0'}},
            {KeyboardKey::KEY_F3,            {KeyboardKey::KEY_F3, false, '\0'}},
            {KeyboardKey::KEY_F4,            {KeyboardKey::KEY_F4, false, '\0'}},
            {KeyboardKey::KEY_F5,            {KeyboardKey::KEY_F5, false, '\0'}},
            {KeyboardKey::KEY_F6,            {KeyboardKey::KEY_F6, false, '\0'}},
            {KeyboardKey::KEY_F7,            {KeyboardKey::KEY_F7, false, '\0'}},
            {KeyboardKey::KEY_F8,            {KeyboardKey::KEY_F8, false, '\0'}},
            {KeyboardKey::KEY_F9,            {KeyboardKey::KEY_F9, false, '\0'}},
            {KeyboardKey::KEY_F10,           {KeyboardKey::KEY_F10, false, '\0'}},
            {KeyboardKey::KEY_F11,           {KeyboardKey::KEY_F11, false, '\0'}},
            {KeyboardKey::KEY_F12,           {KeyboardKey::KEY_F12, false, '\0'}},
            {KeyboardKey::KEY_LEFT_SHIFT,    {KeyboardKey::KEY_LEFT_SHIFT, false, '\0'}},
            {KeyboardKey::KEY_LEFT_CONTROL,  {KeyboardKey::KEY_LEFT_CONTROL, false, '\0'}},
            {KeyboardKey::KEY_LEFT_ALT,      {KeyboardKey::KEY_LEFT_ALT, false, '\0'}},
            {KeyboardKey::KEY_RIGHT_SHIFT,   {KeyboardKey::KEY_RIGHT_SHIFT, false, '\0'}},
            {KeyboardKey::KEY_RIGHT_CONTROL, {KeyboardKey::KEY_RIGHT_CONTROL, false, '\0'}},
            {KeyboardKey::KEY_RIGHT_ALT,     {KeyboardKey::KEY_RIGHT_ALT, false, '\0'}},
            {KeyboardKey::KEY_NULL,          {KeyboardKey::KEY_NULL, false, '\0'}}
        }),
        _Beopy({
        })
    {}

    Keyboard::~Keyboard() {}

    bool Keyboard::isKeyPressed(const int key, const Layout layout)
    {
        KeyMap map;
        int newKey;

        switch (layout) {
            case (Keyboard::Layout::QWERTY):
                newKey = key;
                break;
            case (Keyboard::Layout::AZERTY):
                map = _Azerty[key];
                newKey = map.key;
                break;
            case (Keyboard::Layout::BEOPY):
                map = _Beopy[key];
                newKey = map.key;
                break;
        }
        if (map.key == KeyboardKey::KEY_NULL)
            newKey = key;
        if (map.withShift)
            return IsKeyPressed(newKey) && (IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT) || IsKeyDown(KeyboardKey::KEY_RIGHT_SHIFT));
        return IsKeyPressed(newKey) && !(IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT) || IsKeyDown(KeyboardKey::KEY_RIGHT_SHIFT));
    }

    bool Keyboard::isKeyDown(const int key, const Layout layout)
    {
        KeyMap map;
        int newKey;

        switch (layout) {
            case (Keyboard::Layout::QWERTY):
                newKey = key;
                break;
            case (Keyboard::Layout::AZERTY):
                map = _Azerty[key];
                newKey = map.key;
                break;
            case (Keyboard::Layout::BEOPY):
                map = _Beopy[key];
                newKey = map.key;
                break;
        }
        if (map.key == KeyboardKey::KEY_NULL)
            newKey = key;
        if (map.withShift)
            return IsKeyDown(newKey) && (IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT) || IsKeyDown(KeyboardKey::KEY_RIGHT_SHIFT));
        return IsKeyDown(newKey) && !(IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT) || IsKeyDown(KeyboardKey::KEY_RIGHT_SHIFT));
    }

    KeyMap Keyboard::getCharPressed(const Keyboard::Layout layout)
    {
        KeyMap map{};

        for (const auto &[key, _] : getAzerty()) {
            switch (layout) {
                case (Keyboard::Layout::QWERTY):
                    map.key = key;
                    break;
                case (Keyboard::Layout::AZERTY):
                    map = _Azerty[key];
                    break;
                case (Keyboard::Layout::BEOPY):
                    map = _Beopy[key];
                    break;
            }

            if (IsKeyPressed(map.key)) {
                if (map.withShift) {
                    if (IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT) || IsKeyDown(KeyboardKey::KEY_RIGHT_SHIFT))
                        return map;
                } else {
                    if (!IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT) && !IsKeyDown(KeyboardKey::KEY_RIGHT_SHIFT))
                        return map;
                }
            }
        }
        return KeyMap();
    }

    std::vector<int> Keyboard::getCharPressedList() const
    {
        int c = -1;
        std::vector<int> charList{};

        while ((c = GetCharPressed()) != 0)
            charList.push_back(c);
        return charList;
    }

    Keyboard &Keyboard::getInstance()
    {
        static Keyboard keyboard;
        return keyboard;
    }

    const std::unordered_map<int, KeyMap> &Keyboard::getAzerty() const
    {
        return _Azerty;
    }

    const std::unordered_map<int, KeyMap> &Keyboard::getBeopy() const
    {
        return _Beopy;
    }
};
