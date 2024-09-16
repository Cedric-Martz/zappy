/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Font.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_FONT_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_FONT_HPP
    #include "RayLib.hpp"

namespace rl
{
    class CustomFont {
    public:
        CustomFont();
        CustomFont(const std::string &filename);
        ~CustomFont();

        void loadFromFile(const std::string &filename);
        bool isReady() const;

        const Font &getSource() const;

    private:
        Font _font;
        bool _hasFontLoaded;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_FONT_HPP*/
