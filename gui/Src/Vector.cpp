/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Vector.cpp
*/

#include "Vector.hpp"

bool operator<(const Vector2 &a, const Vector2 &b)
{
    return a.x < b.x && a.y < b.y;
}

bool operator>(const Vector2 &a, const Vector2 &b)
{
    return a.x > b.x && a.y > b.y;
}

std::ostream &operator<<(std::ostream &s, const Vector2 &vec)
{
    return s << "(" << vec.x << ", " << vec.y << ")";
}

std::ostream &operator<<(std::ostream &s, const Vector3 &vec)
{
    return s << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

bool operator<(const Vector3 &a, const Vector3 &b)
{
    return a.x < b.x && a.y < b.y && a.z < b.z;
}

bool operator>(const Vector3 &a, const Vector3 &b)
{
    return a.x > b.x && a.y > b.y && a.z > b.z;
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
