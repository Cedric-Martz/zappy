/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Egg.cpp
*/

#include "Egg.hpp"

namespace rl
{
    Egg::Egg(const std::string &id,
             const std::string &modelFilepath,
             std::shared_ptr<Camera3> &camera)
        : Model3(modelFilepath, camera),
        _id(id)
    {}

    Egg::~Egg() {}

    void Egg::draw()
    {
        Model3::draw();
    }

    std::string Egg::getId() const
    {
        return _id;
    }

    void Egg::setId(const std::string &id)
    {
        _id = id;
    }
};
