/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Item.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_ITEM_HPP
#define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_ITEM_HPP

#include "Sprite.hpp"
#include "Text.hpp"

namespace rl
{
    class Item : public Sprite {
    public:
        Item() = default;
        Item(const Texture &texture);
        Item(const Texture &texture, const Rectangle &rectangle);
        ~Item();

        void update(double deltaTime) override;
        void draw() override;

        void setAmount(int amount);
        int getAmount();

        Text getText();

    private:
        int _amount;
        Text _text;
        Text _text_shadow;
    };
}

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_ITEM_HPP*/
