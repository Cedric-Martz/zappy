/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Planet.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_PLANET_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_PLANET_HPP
    #include "StellarObject.hpp"
    #include "Model3.hpp"
    #include "Sphere.hpp"

namespace rl
{
    class Planet : public StellarObject {
    public:
        Planet();
        Planet(
                const std::string &id,
                const Vector3 &position,
                const float size,
                const Color color,
                const std::shared_ptr<Camera3> &camera,
                const float orbitRadius,
                const float rotationSpeed,
                const OrbitAxis orbitAxis = OrbitAxis::Y
        );
        Planet(
                const std::string &id,
                const std::string &modelFilepath,
                const Vector3 &position,
                const float size,
                const Color color,
                const std::shared_ptr<Camera3> &camera,
                const float orbitRadius,
                const float rotationSpeed,
                const OrbitAxis orbitAxis = OrbitAxis::Y
        );
        ~Planet();

        void update(double deltaTime) override;
        void draw() override;
        void applyTransform(Transform &transform) override;

        VisualElement::Dimension getDimension() const override;
        VisualElement::Type getType() const override;

        void setTextureRotating(const bool state);
        void setTextureRotationSpeed(const float speed);

    private:
        bool _textureRotating;
        float _textureRotation;
        float _textureRotationSpeed;
    };
}

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_PLANET_HPP*/
