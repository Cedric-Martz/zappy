/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** RenderWindow.cpp
*/

#include "RenderWindow.hpp"

namespace rl
{
    RenderWindow &RenderWindow::getInstance()
    {
        static RenderWindow instance;
        return instance;
    }

    RenderWindow::RenderWindow()
    {
        _width = 1920;
        _height = 1080;
    }

    RenderWindow::~RenderWindow() {}

    void RenderWindow::open()
    {
        if (_hasOpened)
            return;
        _hasOpened = true;

        SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);

        InitWindow(
                static_cast<int>(_width),
                static_cast<int>(_height),
                _name.c_str()
        );
        SetTraceLogLevel(LOG_ERROR);
    }

    Vector2 RenderWindow::getSize()
    {
        return Vector2(_width, _height);
    }

    void RenderWindow::applyFlag(const ConfigFlags flag)
    {
        SetWindowState(flag);
    }

    void RenderWindow::setFrameLimit(size_t fps)
    {
        SetTargetFPS(static_cast<int>(fps));
    }

    void RenderWindow::setTitle(const std::string &filepath)
    {
        SetWindowTitle(filepath.c_str());
    }

    void RenderWindow::updateSize(const Vector2 &newSize)
    {
        SetWindowSize(newSize.x, newSize.y);
    }

    bool RenderWindow::isOpen()
    {
        return !WindowShouldClose();
    }

    void RenderWindow::clear(const Color color)
    {
        ClearBackground(color);
    }

    void RenderWindow::close()
    {
        CloseWindow();
    }

    Vector2 RenderWindow::getPosition() const
    {
        return GetWindowPosition();
    }

    void RenderWindow::toggleFullscreen()
    {
        ToggleFullscreen();
    }

};
