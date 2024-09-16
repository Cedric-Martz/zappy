/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Camera3.cpp
*/

#include "Camera3.hpp"

namespace rl
{
    Camera3::Camera3(const Vector3 position,
                   const Vector3 target,
                   const Vector3 up,
                   const float fovy,
                   const CameraProjection projection)
    {
        _camera.position = position;
        _camera.target = target;
        _camera.up = up;
        _camera.fovy = fovy;
        _camera.projection = projection;
        setRenderDistance(10000.0f);
    }

    Camera3::~Camera3() {}

    Camera3D &Camera3::getSource()
    {
        return _camera;
    }

    void Camera3::setMode(const CameraMode mode)
    {
        UpdateCamera(&_camera, mode);
        _mode3D = mode;
    }

    CameraMode Camera3::getMode() const
    {
        return _mode3D;
    }

    void Camera3::setProjection(const CameraProjection mode)
    {
        _camera.projection = mode;
    }

    CameraProjection Camera3::getProjection() const
    {
        return static_cast<CameraProjection>(_camera.projection);
    }

    Matrix Camera3::getProjectionMatrix() const
    {
        return _projectionMatrix;
    }

    void Camera3::setMatrixUtils(float near, float far, float aspect, float top, float right)
    {
        _near = near;
        _aspect = aspect;
        _top = top;
        _right = right;
        setRenderDistance(far);
    }

    void Camera3::setRenderDistance(const float renderDistance)
    {
        _far = renderDistance;
        _projectionMatrix = Matrix{
            .m0 = _near / _right,
            .m4 = 0.0f,
            .m8 = 0.0f,
            .m12 = 0.0f,

            .m1 = 0.0f,
            .m5 = _near / _top,
            .m9 = 0.0f,
            .m13 = 0.0f,

            .m2 = 0.0f,
            .m6 = 0.0f,
            .m10 = -(_far + _near) / (_far - _near),
            .m14 = -(2.0f * _far * _near) / (_far - _near),

            .m3 = 0.0f,
            .m7 = 0.0f,
            .m11 = -1.0f,
            .m15 = 0.0f
        };
    }

    float Camera3::getRenderDistance() const
    {
        return _far;
    }
};
