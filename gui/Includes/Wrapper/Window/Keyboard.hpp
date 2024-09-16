/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Keyboard.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_KEYBOARD_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_KEYBOARD_HPP
    #include "RayLib.hpp"

namespace rl
{
    struct KeyMap {
        int key = KeyboardKey::KEY_NULL;
        bool withShift = false;
        char ch = 0;
    };

    class Keyboard {
    public:
        enum class Layout {
            QWERTY,
            AZERTY,
            BEOPY
        };

        static Keyboard &getInstance();

        bool isKeyPressed(const int key, const Layout layout = Layout::AZERTY);
        bool isKeyDown(const int key, const Layout layout = Layout::AZERTY);
        KeyMap getCharPressed(const Layout layout = Layout::AZERTY);
        std::vector<int> getCharPressedList() const;

        const std::unordered_map<int, KeyMap> &getAzerty() const;
        const std::unordered_map<int, KeyMap> &getBeopy() const;
    private:
        Keyboard();
        ~Keyboard();
        Keyboard(const Keyboard&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;

        std::unordered_map<int, KeyMap> _Azerty;
        std::unordered_map<int, KeyMap> _Beopy;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_KEYBOARD_HPP*/
