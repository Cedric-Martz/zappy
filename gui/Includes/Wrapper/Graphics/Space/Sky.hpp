/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Sky.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SKY_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SKY_HPP
    #include "Star.hpp"
    #include "Camera3.hpp"

namespace rl
{
    class Sky : StellarObject {
    public:
        Sky();
        Sky(const size_t count,
            const float radiusPosition,
            const float radiusSize,
            const Vector3 &position,
            const Vector2 &radiusInterval,
            const float speed,
            const std::shared_ptr<Camera3> &camera,
            const bool hasTrail = false,
            const size_t trailLength = 10);
        ~Sky();

        void loadConfig(
            const std::size_t count,
            const float radiusPosition,
            const float radiusSize,
            const Vector3 &position,
            const Vector2 &radiusInterval,
            const float speed,
            const std::shared_ptr<Camera3> &camera,
            const bool hasTrail = false,
            const size_t trailLength = 10
        );
        void draw() override;
        void update(double deltaTime) override;
        int getStarNumber() const;

    private:
        std::vector<Star> _stars;
        float radiusPosition;
        float radiusSize;
        Vector2 _radiusInterval;
        Vector3 _rotationAcc;
        float _speed;
        std::shared_ptr<Camera3> _camera;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SKY_HP*/
