/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Vector.cpp
*/

#include "Vector.hpp"

bool operator==(const Vector2 &a, const Vector2 &b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator==(const Vector3 &a, const Vector3 &b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator!=(const Vector2 &a, const Vector2 &b)
{
    return !(a == b);
}

bool operator!=(const Vector3 &a, const Vector3 &b)
{
    return !(a == b);
}

Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
    return Vector3Add(a, b);
}

Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
    return Vector3Subtract(a, b);
}

Vector3 operator*(const Vector3 &vector, const float scale)
{
    return Vector3Scale(vector, scale);
}

bool operator<(const Vector2 &a, const Vector2 &b)
{
    return a.x < b.x && a.y < b.y;
}

bool operator>(const Vector2 &a, const Vector2 &b)
{
    return a.x > b.x && a.y > b.y;
}

Vector2 operator+(const Vector2 &a, const Vector2 &b)
{
    return Vector2Add(a, b);
}

Vector2 operator-(const Vector2 &a, const Vector2 &b)
{
    return Vector2Subtract(a, b);
}

Vector2 operator*(const Vector2 &a, const Vector2 &b)
{
    return Vector2Multiply(a, b);
}

Vector2 operator/(const Vector2 &a, const Vector2 &b)
{
    return Vector2Divide(a, b);
}

Vector2 operator*(const Vector2 &vector, const float scale)
{
    return Vector2Scale(vector, scale);
}

Vector2 operator/(const Vector2 &vector, const float scale)
{
    return Vector2Divide(vector, {scale, scale});
}

std::ostream &operator<<(std::ostream &s, const Vector2 &vec)
{
    return s << "(" << vec.x << ", " << vec.y << ")";
}

std::ostream &operator<<(std::ostream &s, const Vector3 &vec)
{
    return s << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

Vector3 operator*(const Vector3 &point, const Matrix &matrix)
{
    return Vector3(
            matrix.m0 * point.x + matrix.m4 * point.y + matrix.m8 * point.z + matrix.m12,
            matrix.m1 * point.x + matrix.m5 * point.y + matrix.m9 * point.z + matrix.m13,
            matrix.m2 * point.x + matrix.m6 * point.y + matrix.m10 * point.z + matrix.m14
    );
}

bool operator<(const Vector3 &a, const Vector3 &b)
{
    return a.x < b.x && b.y < b.y && a.z < b.z;
}

bool operator>(const Vector3 &a, const Vector3 &b)
{
    return a.x > b.x && b.y > b.y && a.z > b.z;
}

float Vec3Wrapper::distanceSquared(const Vector3 &a, const Vector3 &b)
{
    return Vector3DistanceSqr(a, b);
}

Vector3 Vec3Wrapper::normalize(const Vector3 &vec)
{
    return Vector3Normalize(vec);
}

Vector3 Vec3Wrapper::crossProduct(const Vector3 &a, const Vector3 &b)
{
    return Vector3CrossProduct(a, b);
}

float Vec3Wrapper::length(const Vector3 &vec)
{
    return Vector3Length(vec);
}
