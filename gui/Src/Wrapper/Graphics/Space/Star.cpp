/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Star.cpp
*/

#include "Star.hpp"

namespace rl
{
    Star::Star()
        : Sphere()
    {}

    Star::Star(const Vector3 &position, const Color &color, const float size, const bool hasTrail, const size_t trailLength)
        : Sphere(), _hasTrail(hasTrail), _trailLength(trailLength)
    {
        _position = position;
        _color = color;
        _size.x = size;
    }

    Star::~Star() {}

    void Star::draw()
    {
        Sphere::draw();
    }

    void Star::update([[maybe_unused]] double deltaTime) {}

    VisualElement::Dimension Star::getDimension() const
    {
        return VisualElement::Dimension::DIMENSION3;
    }

    void Star::applyTransform([[maybe_unused]] Transform &transform) {}

    VisualElement::Type Star::getType() const
    {
        return VisualElement::Type::STAR;
    }

    void Star::setTrailState(const bool state)
    {
        _hasTrail = state;
    }

    void Star::setTrailLength(const size_t length)
    {
        _trailLength = length;
    }

    void Star::updateTrailPosition(const Vector3 &position)
    {
        if (!_hasTrail)
            return;

        _history.push_back(position);
        if (_history.size() > _trailLength)
            _history.erase(_history.begin());
    }

    void Star::drawTrail() const
    {
        if (!_hasTrail)
            return;
        if (_history.size() < 2)
            return;

        for (size_t i = 0; i < _history.size() - 1; ++i)
            DrawLine3D(_history[i], _history[i + 1], _color);
    }
};
