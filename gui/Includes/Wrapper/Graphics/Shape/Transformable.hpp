/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Transformable.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TRANSFORMABLE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TRANSFORMABLE_HPP
    #include "RayLib.hpp"

namespace rl
{
    class Transformable {
    public:
        virtual ~Transformable();

        /* 2D */

        void setPosition(float x, float y);
        void setPosition(const Vector2 &vector);
        void setRotation(float angle);
        void setScale(float x, float y);
        void setScale(const Vector2 &vector);
        void setScale(const float scale);

        Vector2 getPosition2() const;
        float getRotation() const;
        Vector2 getScale2() const;

        /* 3D */

        void setPosition(float x, float y, float z);
        void setPosition(const Vector3 &vector);
        void setScale(float x, float y, float z);
        void setScale(const Vector3 &vector);

        Vector3 getPosition3() const;
        Vector3 getScale3() const;

    protected:
        Transformable();
        Vector3 _position;
        float _rotation;
        Vector3 _scale;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TRANSFORMABLE_HPP*/
