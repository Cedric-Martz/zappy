/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Transform.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TRANSFORM_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TRANSFORM_HPP
    #include "RayLib.hpp"
    #include "Transformable.hpp"

namespace rl
{
    class Transform : public Transformable {
    public:
        enum class Type {
            TRANSLATION,
            ROTATION,
            SCALE
        };

        Transform();
        ~Transform();

        void clear();
        void clearCheckers();

        Transform getInverse() const;
        Type getType() const;
        std::vector<Transform> const &getTransforms() const;

        Transform &combine(const Transform &transform);

        Transform &translate(float x, float y);
        Transform &translate(const Vector2 &vector);

        Transform &rotate(const float angle);

        Transform &scale(float radius);
        Transform &scale(float x, float y);
        Transform &scale(const Vector2 &vector);

        Vector2 transformPoint2D(float x, float y) const;
        Vector2 transformPoint2D(const Vector2 &vector) const;

        void identity();
    private:
        Matrix _matrix;
        Type _type;
        std::vector<Transform> _transforms;
        bool _hasTranslated;
        bool _hasRotated;
        bool _hasScaled;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TRANSFORM_HPP*/
