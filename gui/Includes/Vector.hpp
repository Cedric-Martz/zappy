/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Vector.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_VECTOR_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_VECTOR_HPP
    #include "RayLib.hpp"

bool operator==(const Vector2 &a, const Vector2 &b);
bool operator!=(const Vector2 &a, const Vector2 &b);
Vector2 operator+(const Vector2 &a, const Vector2 &b);
Vector2 operator-(const Vector2 &a, const Vector2 &b);
Vector2 operator*(const Vector2 &a, const Vector2 &b);
Vector2 operator/(const Vector2 &a, const Vector2 &b);
Vector2 operator*(const Vector2 &a, const float scale);
Vector2 operator/(const Vector2 &a, const float scale);
bool operator<(const Vector2 &a, const Vector2 &b);
bool operator>(const Vector2 &a, const Vector2 &b);
bool operator==(const Vector3 &a, const Vector3 &b);
bool operator!=(const Vector3 &a, const Vector3 &b);
Vector3 operator+(const Vector3 &a, const Vector3 &b);
Vector3 operator-(const Vector3 &a, const Vector3 &b);
Vector3 operator*(const Vector3 &a, const float scale);
bool operator<(const Vector3 &a, const Vector3 &b);
bool operator>(const Vector3 &a, const Vector3 &b);

std::ostream &operator<<(std::ostream &s, const Vector2 &vec);
std::ostream &operator<<(std::ostream &s, const Vector3 &vec);
Vector3 operator*(const Vector3 &vec, const Matrix &matrix);

class Vec3Wrapper {
public:
    static float distanceSquared(const Vector3 &a, const Vector3 &b);
    static Vector3 normalize(const Vector3 &vec);
    static Vector3 crossProduct(const Vector3 &a, const Vector3 &b);
    static float length(const Vector3 &vec);
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_VECTOR_HPP*/
