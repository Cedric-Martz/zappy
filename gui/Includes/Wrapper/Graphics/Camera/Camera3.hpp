/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Camera.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_Camera3_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_Camera3_HPP
    #include "RayLib.hpp"

namespace rl
{
    class Camera3 {
    public:
        Camera3(const Vector3 position,
               const Vector3 target,
               const Vector3 up,
               const float fovy,
               const CameraProjection projection);
        ~Camera3();

        Camera3D &getSource();

        void setMode(const CameraMode mode);
        CameraMode getMode() const;

        void setProjection(const CameraProjection mode);
        CameraProjection getProjection() const;

        void setProjectionMatrix(const Matrix &matrix);
        Matrix getProjectionMatrix() const;

        void setMatrixUtils(float near, float far, float aspect, float top, float right);

        void setRenderDistance(const float renderDistance);
        float getRenderDistance() const;

    private:
        Camera3D _camera;
        CameraMode _mode3D = CAMERA_FIRST_PERSON;
        Matrix _projectionMatrix{};
        float _near;
        float _far;
        float _aspect;
        float _top;
        float _right;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_Camera3_HPP*/
