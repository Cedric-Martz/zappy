/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Splash.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPLASH_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPLASH_HPP
    #include "Text.hpp"

namespace rl
{
    class Splash : public Text {
    public:
        Splash(const Color color,
               const float rotation = -20.0f);
        ~Splash();

        void draw() override;

        VisualElement::Type getType() const override;

    private:
        bool _changeSize;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPLASH_HPP*/
