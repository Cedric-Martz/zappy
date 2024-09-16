/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** CircleShape.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CIRCLESHAPE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CIRCLESHAPE_HPP
    #include "RayLib.hpp"
    #include "Shape.hpp"

namespace rl
{
    class CircleShape : public Shape {
    public:
        CircleShape(const Vector2 position,
                    const float radius = 10,
                    const Color color = BLACK);

        void setRadius(const float radius);

        float getRadius();
        VisualElement::Type getType() const override;

        void draw() override;
        void applyTransform(Transform &transform) override;

    private:
        float _radius;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CIRCLESHAPE_HPP*/
