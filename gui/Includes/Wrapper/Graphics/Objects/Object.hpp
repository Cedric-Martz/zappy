/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Object.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_OBJECT_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_OBJECT_HPP
    #include "VisualElement.hpp"

namespace rl
{
    class Object : public virtual VisualElement {
    public:
        virtual ~Object();

    protected:
        Object();
        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;

        void setTexture(const Texture texture) = delete;
        void setTextureRect(const Rectangle textureRect) = delete;

        VisualElement::Dimension getDimension() const override;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_OBJECT_HPP*/
