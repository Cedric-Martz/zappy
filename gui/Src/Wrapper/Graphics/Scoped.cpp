/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ScopedDraw.cpp
*/

#include "Scoped.hpp"
#include "Camera2.hpp"
#include "Camera3.hpp"

namespace rl
{
    Scoped::Scoped()
    {
        BeginDrawing();
        _mode = Mode::DRAW;
    }

    Scoped::Scoped(Camera2 &camera)
    {
        BeginMode2D(camera.getSource());
        _mode = Mode::MODE2D;
    }

    Scoped::Scoped(std::shared_ptr<Camera3> camera)
    {
        BeginMode3D(camera->getSource());
        rlSetMatrixProjection(camera->getProjectionMatrix());
        _mode = Mode::MODE3D;
    }

    Scoped::~Scoped()
    {
        switch (_mode) {
            case (Mode::DRAW):
                EndDrawing();
                break;
            case (Mode::MODE2D):
                EndMode2D();
                break;
            case (Mode::MODE3D):
                EndMode3D();
                break;
        }
    }

    Scoped::Mode Scoped::getMode() const
    {
        return _mode;
    }
};
