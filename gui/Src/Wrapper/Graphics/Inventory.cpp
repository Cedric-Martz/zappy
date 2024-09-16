/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Inventory.cpp
*/

#include "Inventory.hpp"
#include "Sprite.hpp"

namespace rl
{
    Inventory::Inventory()
        : VisualElement()
    {
        TextureManager &manager = TextureManager::getInstance();

        std::unique_ptr<Item> food = std::make_unique<Item>(manager.loadTexture("Assets/Imgs/ressources/food.png"));
        food->setPosition(Vector2(105, 105));
        food->setScale(Vector2(0.7, 0.7));

        std::unique_ptr<Item> linemate = std::make_unique<Item>(manager.loadTexture("Assets/Imgs/ressources/linemate.png"));
        linemate->setPosition(Vector2(220, 120));
        linemate->setScale(Vector2(0.5, 0.5));

        std::unique_ptr<Item> deraumere = std::make_unique<Item>(manager.loadTexture("Assets/Imgs/ressources/deraumere.png"));
        deraumere->setPosition(Vector2(325, 120));
        deraumere->setScale(Vector2(0.5, 0.5));

        std::unique_ptr<Item> sibure = std::make_unique<Item>(manager.loadTexture("Assets/Imgs/ressources/sibure.png"));
        sibure->setPosition(Vector2(425, 120));
        sibure->setScale(Vector2(0.5, 0.5));

        std::unique_ptr<Item> mendiane = std::make_unique<Item>(manager.loadTexture("Assets/Imgs/ressources/mendiane.png"));
        mendiane->setPosition(Vector2(530, 122));
        mendiane->setScale(Vector2(0.5, 0.5));

        std::unique_ptr<Item> phiras = std::make_unique<Item>(manager.loadTexture("Assets/Imgs/ressources/phiras.png"));
        phiras->setPosition(Vector2(632, 124));
        phiras->setScale(Vector2(0.5, 0.5));

        std::unique_ptr<Item> thystame = std::make_unique<Item>(manager.loadTexture("Assets/Imgs/ressources/thystame.png"));
        thystame->setPosition(Vector2(735, 120));
        thystame->setScale(Vector2(0.5, 0.5));

        _items[ItemType::FOOD] = std::move(food);
        _items[ItemType::LINEMATE] = std::move(linemate);
        _items[ItemType::DERAUMERE] = std::move(deraumere);
        _items[ItemType::SIBUR] = std::move(sibure);
        _items[ItemType::MENDIANE] = std::move(mendiane);
        _items[ItemType::PHIRAS] = std::move(phiras);
        _items[ItemType::THYSTAME] = std::move(thystame);

        _background = std::move(std::make_unique<Sprite>(manager.loadTexture("Assets/Imgs/interface/inventory.png")));
        _background->setPosition(Vector2(510, 100));
        _background->setScale(Vector2(0.75, 0.75));
    }

    Inventory::~Inventory()
    {
    }

    void Inventory::setAmount(ItemType item, int amount)
    {
        _items[item]->setAmount(amount);
    }

    int Inventory::getAmount(ItemType item)
    {
        return _items[item]->getAmount();
    }

    void Inventory::addItem(ItemType item)
    {
        _items[item]->setAmount(_items[item]->getAmount() + 1);
    }

    void Inventory::removeItem(ItemType item)
    {
        if (_items[item]->getAmount() > 0)
            _items[item]->setAmount(_items[item]->getAmount() - 1);
    }

    Item &Inventory::getItem(ItemType item)
    {
        return *_items[item];
    }

    std::unordered_map<ItemType, std::unique_ptr<Item>> &Inventory::getInventory()
    {
        return _items;
    }

    void Inventory::draw()
    {
        _background->draw();
        for (auto &[_, item] : _items)
            item->draw();
    }

    void Inventory::update(double deltaTime)
    {
        updateRainbow(deltaTime);
        for (auto &[_, item] : _items)
            item->update(deltaTime);
    }

    VisualElement::Type Inventory::getType() const
    {
        return VisualElement::Type::INVENTORY;
    }

    void Inventory::applyTransform([[maybe_unused]] Transform &transform) {}

    std::string Inventory::itemToStr(const ItemType item)
    {
        static const std::unordered_map<ItemType, std::string> itemToStrTab {
            {ItemType::FOOD, "Food"},
            {ItemType::LINEMATE, "Linemate"},
            {ItemType::DERAUMERE, "Deraumere"},
            {ItemType::SIBUR, "Sibur"},
            {ItemType::MENDIANE, "Mendiane"},
            {ItemType::PHIRAS, "Phiras"},
            {ItemType::THYSTAME, "Thystame"}
        };

        return itemToStrTab.at(item);
    }
}
