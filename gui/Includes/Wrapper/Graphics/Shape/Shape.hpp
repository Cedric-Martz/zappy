/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Shape.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SHAPE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SHAPE_HPP
    #include "VisualElement.hpp"

namespace rl
{
    class Shape : public VisualElement {
    public:
        virtual ~Shape();

    protected:
        Shape();
        void draw() override;
        void applyTransform(Transform &transform);
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SHAPE_HPP*/
