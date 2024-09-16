/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Star.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_STAR_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_STAR_HPP
    #include "StellarObject.hpp"
    #include "Sphere.hpp"

namespace rl
{
    class Star : public StellarObject {
    public:
        Star();
        Star(const Vector3 &position,
             const Color &color,
             const float size,
             const bool hasTrail = false,
             const size_t trailLength = 10);
        ~Star();

        void draw() override;
        void update(double deltaTime) override;
        VisualElement::Dimension getDimension() const override;
        VisualElement::Type getType() const override;
        void applyTransform(Transform &transform) override;

        void setTrailState(const bool state);
        void setTrailLength(const size_t length);
        void updateTrailPosition(const Vector3 &position);
        void drawTrail() const;

    private:
        bool _hasTrail;
        size_t _trailLength;
        std::vector<Vector3> _history;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_STAR_HPP*/
