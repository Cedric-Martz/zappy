/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Object.cpp
*/

#include "Object.hpp"

namespace rl
{
    Object::Object()
        : VisualElement()
    {}

    Object::~Object() {}

    void Object::draw() {}

    void Object::applyTransform([[maybe_unused]] Transform &transform) {}

    void Object::update(double deltaTime)
    {
        updateRainbow(deltaTime);
    }

    VisualElement::Dimension Object::getDimension() const
    {
        return VisualElement::Dimension::DIMENSION3;
    }
};
