/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Torus.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TORUS_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TORUS_HPP
    #include "Object.hpp"

namespace rl
{
    class Torus : public Object {
    public:
        Torus(const float radius,
              const float size,
              const int radSeg,
              const int sides);
        Torus(const float radius,
              const float size,
              const int radSeg,
              const int sides,
              const std::string &filepath);
        ~Torus();

        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;
        VisualElement::Type getType() const override;

        void loadTextureFromFile(const std::string &filepath);

    private:
        bool _hasTextureLoaded;
        Model _model;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TORUS_HPP*/
