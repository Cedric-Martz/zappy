/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Sky.cpp
*/

#include "Sky.hpp"

namespace rl
{
    Sky::Sky()
        : _rotationAcc({0, 0, 0}),
        _speed(0)
    {}

    Sky::Sky(const size_t count,
             const float radiusPosition,
             const float radiusSize,
             const Vector3 &position,
             const Vector2 &radiusInterval,
             const float speed,
             const std::shared_ptr<Camera3> &camera,
             const bool hasTrail,
             const size_t trailLength)
        : _rotationAcc({0, 0, 0}),
        _speed(speed)
    {
        loadConfig(count, radiusPosition, radiusSize, position, radiusInterval, _speed, camera, hasTrail, trailLength);
    }

    Sky::~Sky() {}

    void Sky::loadConfig(const size_t count,
                         const float radiusPosition,
                         [[maybe_unused]] const float radiusSize,
                         const Vector3 &position,
                         const Vector2 &radiusInterval,
                         const float speed,
                         const std::shared_ptr<Camera3> &camera,
                         const bool hasTrail,
                         const size_t trailLength)
    {
        float theta = 0;
        float phi = 0;
        int radius = 0;
        Color color{};

        _camera = camera;
        _speed = speed;

        for (size_t i = 0; i < count; ++i) {
            theta = GetRandomValue(0, 360) * DEG2RAD;
            phi = GetRandomValue(0, 360) * DEG2RAD;
            radius = GetRandomValue(radiusInterval.x, radiusInterval.y);

            color.r = GetRandomValue(180, 255);
            color.g = GetRandomValue(180, 255);
            color.b = GetRandomValue(180, 255);
            color.a = GetRandomValue(200, 255);

            if (GetRandomValue(1, 100) > 90) {
                color.r = GetRandomValue(10, 50);
                color.g = 0;
                color.b = GetRandomValue(1, 150);
                color.a = GetRandomValue(50, 255);
            }

            Star s;
            s.setPosition(position.x + radiusPosition * sinf(theta) * cosf(phi),
                          position.y + radiusPosition * sinf(theta) * sinf(phi),
                          position.z + radiusPosition * cosf(theta));
            s.setColor(color);
            s.setSize(static_cast<float>(radius) / 100.0f);
            s.setTrailState(hasTrail);
            if (hasTrail)
                s.setTrailLength(trailLength);
            _stars.push_back(s);
        }
    }

    void Sky::update([[maybe_unused]] double deltaTime)
    {
        _rotationAcc.x += _speed;
        _rotationAcc.y += _speed;

        for (auto &star : _stars)
            star.updateTrailPosition(
                Vector3RotateByAxisAngle(
                    Vector3RotateByAxisAngle(
                        star.getPosition3(),
                        (Vector3){1.0f, 0.0f, 0.0f},
                        _rotationAcc.x
                    ),
                    (Vector3){0.0f, 1.0f, 0.0f},
                    _rotationAcc.y
                )
            );
    }

    void Sky::draw()
    {
        rlPushMatrix();
        rlRotatef(_rotationAcc.x, 1.0f, 0.0f, 0.0f);
        rlRotatef(_rotationAcc.y, 0.0f, 1.0f, 0.0f);
        for (auto &star : _stars) {
            if (Vector3Distance(star.getPosition3(), _camera->getSource().position) > 2.0f) {
                star.draw();
                star.drawTrail();
            }
        }
        rlPopMatrix();
    }

    int Sky::getStarNumber() const
    {
        return static_cast<int>(_stars.size());
    }
};
