/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** MainSetting
*/

#include "MainSetting.hpp"
#include "SceneManager.hpp"
#include "MiscellaneousSetting.hpp"
#include "KeyboardSetting.hpp"
#include "ResolutionSetting.hpp"
#include "SoundSetting.hpp"
#include "RenderWindow.hpp"

namespace rl
{
    MainSetting::MainSetting()
    {
        Vector2 ws = rl::RenderWindow::getInstance().getSize();
        float wsx = ws.x;
        float wsy = ws.y;

        addText("Setting_title", "Settings", 75, RED, {0.5f * wsx, 0.0555f * wsy});

        addButton(
            "quit button",
            Vector2{0.0234f * wsx, 0.0416f * wsy},
            Vector2{0.0468f * wsx, 0.0833f * wsy},
            WHITE,
            [&]() {

                SceneManager::getInstance().setTransitionSpeed(0.01);
                SceneManager::getInstance().popScene();
            },
            "Assets/Imgs/buttons/buttonclose.png",
            "Assets/Imgs/buttons/hoverclose.png"
        );

        addButton(
            "Resolution button",
            Vector2{0.5f * wsx, 0.25f * wsy},
            Vector2{0.20f * wsx, 0.1f * wsy},
            WHITE,
            [&]() {
                SceneManager::getInstance().setTransitionSpeed(0.1);
                SceneManager::getInstance().pushScene(std::make_unique<ResolutionSetting>());
            },
            "Assets/Imgs/buttons/buttonVideosetting.png",
            "Assets/Imgs/buttons/hoverVideosetting.png"
        );

        addButton(
            "sound button",
            Vector2{0.5f * wsx, 0.40f * wsy},
            Vector2{0.20f * wsx, 0.1f * wsy},
            WHITE,
            [&]() {
                SceneManager::getInstance().setTransitionSpeed(0.1);
                SceneManager::getInstance().pushScene(std::make_unique<SoundSetting>());
            },
            "Assets/Imgs/buttons/buttonsoundsetting.png",
            "Assets/Imgs/buttons/hoversoundsetting.png"
        );

        addButton(
            "keyboard button",
            Vector2{0.5f * wsx, 0.55f * wsy},
            Vector2{0.20f * wsx, 0.1f * wsy},
            WHITE,
            [&]() {
                SceneManager::getInstance().setTransitionSpeed(0.1);
                SceneManager::getInstance().pushScene(std::make_unique<KeyboardSetting>());
            },
            "Assets/Imgs/buttons/buttoncontrolssetting.png",
            "Assets/Imgs/buttons/hovercontrolssetting.png"
        );

        addButton(
            "Miscellaneous button",
            Vector2{0.5f * wsx, 0.70f * wsy},
            Vector2{0.2f * wsx, 0.1f * wsy},
            WHITE,
            [&]() {
                SceneManager::getInstance().setTransitionSpeed(0.1);
                SceneManager::getInstance().pushScene(std::make_unique<MiscellaneousSetting>());
            },
            "Assets/Imgs/buttons/buttonMiscellaneous.png",
            "Assets/Imgs/buttons/hoverMiscellaneous.png"

        );

        _background = std::make_unique<Sprite>(TextureManager::getInstance().loadTexture("Assets/Imgs/font/red_font.png"));
        _background->setTextureRect({0,
                                     0,
                                     static_cast<float>(_background->getTexture().width),
                                     static_cast<float>(_background->getTexture().height)});
        _background->setPosition(Vector2{0.5f * wsx, 0.5f * wsy});
        _background->setScale(Vector2{1.0f, 1.0f});
        _background->setColor(WHITE);

    };

    MainSetting::~MainSetting()
    {
    }

    std::string MainSetting::getId() const
    {
        return "MainSettingScene";
    }

    void MainSetting::events()
    {
    }

    void MainSetting::update(double deltaTime)
    {
        _background->update(deltaTime);

        for (auto &[_, elem] : _elements)
            elem->update(deltaTime);
        AudioManager::getInstance().updateJukebox(*this);
    }

    void MainSetting::render()
    {
        _background->draw();

        for (auto &[_, elem] : _elements)
            elem->draw();
    }
}