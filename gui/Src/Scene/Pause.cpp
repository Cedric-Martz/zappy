/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** Pause
*/

#include <iostream>
#include <random>
#include "Factory.hpp"
#include "MainSetting.hpp"
#include "Game.hpp"
#include "Star.hpp"
#include "ArgumentParser.hpp"
#include "Pause.hpp"
#include "NetworkManager.hpp"

namespace rl
{
    Pause::Pause()
        : _camera(std::make_shared<Camera3>(Vector3{0.0f, 0.0f, 5.0f},
                                            Vector3{0.0f, 0.0f, 0.0f},
                                            Vector3{0.0f, 1.0f, 0.0f},
                                            60.0f,
                                            CAMERA_PERSPECTIVE))
    {
        NetworkManager::getInstance() << "/pause\n";

        RenderWindow &window = RenderWindow::getInstance();

        float wsx = window.getSize().x;
        float wsy = window.getSize().y;

        addText("Pause", "Pause", 40, WHITE, Vector2{wsx / 2, wsy / 2 - 400});

        addButton(
                "Back to Game",
                Vector2{wsx / 2, wsy / 2 - 200},
                Vector2{350, 100},
                WHITE,
                [&]() {
                    SceneManager::getInstance().setTransitionSpeed(1.0f);
                    SceneManager::getInstance().popScene();
                },
                "Assets/Imgs/buttons/pauseMenu/buttonBackToGame.png",
                "Assets/Imgs/buttons/pauseMenu/hoverBackToGame.png"
        );

        addButton(
                "Options",
                Vector2{wsx / 2, wsy / 2},
                Vector2{350, 100},
                WHITE,
                [&]() {
                    SceneManager::getInstance().setTransitionSpeed(1.0f);
                    SceneManager::getInstance().pushScene(std::make_unique<MainSetting>());
                },
                "Assets/Imgs/buttons/pauseMenu/buttonOptions.png",
                "Assets/Imgs/buttons/pauseMenu/hoverOptions.png"
        );

        addButton(
                "Quit to Title",
                Vector2{wsx / 2, wsy / 2 + 200},
                Vector2{350, 100},
                WHITE,
                [&]() {
                    SceneManager::getInstance().setTransitionSpeed(1.0f);
                    SceneManager::getInstance().popScene();
                    SceneManager::getInstance().popScene();
                },
                "Assets/Imgs/buttons/pauseMenu/buttonQuitToTitle.png",
                "Assets/Imgs/buttons/pauseMenu/hoverQuitToTitle.png"
        );

        addSprite("backgroundBlack", "./Assets/Imgs/interface/black.png", Vector2{0, 0}, Vector2{8.0f, 8.0f},
                  ColorAlpha(WHITE, 0.6f));
        addSprite("background", "./MenuBackground.png", Vector2{wsx / 2, wsy / 2}, Vector2{1.0f, 1.0f}, WHITE);
    }

    Pause::~Pause()
    {
        TextureManager::getInstance().removeTexture("./MenuBackground.png");
        NetworkManager::getInstance() << "/play\n";
    }

    std::string Pause::getId() const
    {
        return "PauseScene";
    }

    void Pause::events()
    {
        if (Keyboard::getInstance().isKeyPressed(KeyboardKey::KEY_ESCAPE)) {
            SceneManager::getInstance().popScene();
            return;
        }
    }

    void Pause::update(double deltaTime)
    {
        for (auto &[_, element] : _elements)
            element->update(deltaTime);
    }

    void Pause::render()
    {
        {
            Scoped scoped(_camera);
            for (auto &[_, element] : _elements) {
                if (!element->getDisplayed())
                    continue;
                if (element->getDimension() == VisualElement::Dimension::DIMENSION3)
                    element->draw();
            }
        }
        for (auto &[_, element] : _elements) {
            if (!element->getDisplayed())
                continue;
            if (element->getDimension() == VisualElement::Dimension::DIMENSION2)
                element->draw();
        }
    }
}
