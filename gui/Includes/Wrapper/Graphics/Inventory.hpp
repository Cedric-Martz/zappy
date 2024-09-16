/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Inventory.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_INVENTORY_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_INVENTORY_HPP

#include "VisualElement.hpp"
#include "TextureManager.hpp"
#include "Item.hpp"
#include <iostream>
#include <map>

namespace rl
{
    enum class ItemType {
        FOOD = 0,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };
};

namespace rl
{
    class Inventory : public VisualElement {
    public:
        Inventory();
        ~Inventory();

        void draw() override;
        void update(double deltaTime) override;
        VisualElement::Type getType() const override;
        void applyTransform(Transform &transform) override;

        void addItem(ItemType item);
        void removeItem(ItemType item);
        Item &getItem(ItemType item);

        void setAmount(ItemType item, int amount);
        int getAmount(ItemType item);
        std::unordered_map<ItemType, std::unique_ptr<Item>> &getInventory();

        static std::string itemToStr(const ItemType item);
    private:
        std::unordered_map<ItemType, std::unique_ptr<Item>> _items;
        std::unique_ptr<Sprite> _background;
    };
}

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_INVENTORY_HPP*/
