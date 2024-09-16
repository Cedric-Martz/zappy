/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Texture.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPRITE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPRITE_HPP
    #include "VisualElement.hpp"

namespace rl
{
    class Sprite : public VisualElement {
    public:
        Sprite(const Texture &texture);
        Sprite(const Texture &texture, const Rectangle &rectangle);
        ~Sprite();

        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;
        VisualElement::Type getType() const override;

        void flip();
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPRITE_HPP*/
