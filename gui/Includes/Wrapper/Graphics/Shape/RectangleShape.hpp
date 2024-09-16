/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** RectangleShape.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RECTANGLESHAPE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RECTANGLESHAPE_HPP
    #include "RayLib.hpp"
    #include "Shape.hpp"
    #include "Clickable.hpp"

namespace rl
{
    class RectangleShape : public Shape, public Clickable {
    public:
        RectangleShape(const Rectangle rectangle = Rectangle(0, 0, 0, 0),
                       const Color color = WHITE);

        Rectangle getBounds() const;
        Vector2 getSize() const;
        VisualElement::Type getType() const override;

        void setBounds(const Rectangle rectangle);
        void setSize(const Vector2 &size);
        void setSize(const float x, const float y);

        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;

        bool isHovered() override;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RECTANGLESHAPE_HPP*/
