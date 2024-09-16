/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** MiscellaneousSetting
*/

#include "SceneManager.hpp"
#include "MiscellaneousSetting.hpp"
#include "RenderWindow.hpp"
#include "SettingsValue.hpp"
#include "InputText.hpp"

namespace rl
{
    MiscellaneousSetting::MiscellaneousSetting() :
        _authorizedChars("0123456789")
    {
        Vector2 ws = rl::RenderWindow::getInstance().getSize();
        float wsx = ws.x;
        float wsy = ws.y;

        addText("MiscellaneousSetting", "Miscellaneous Settings", 70, PURPLE, {0.5f * wsx, 0.0555f * wsy});

        addButton(
            "quit button",
            Vector2{0.0234f * wsx, 0.0416f * wsy},
            Vector2{0.0468f * wsx, 0.0833f * wsy},
            PURPLE,
            [&]() {

                SceneManager::getInstance().setTransitionSpeed(0.1);
                SceneManager::getInstance().popScene();
            },
            "Assets/Imgs/buttons/buttonclose.png",
            "Assets/Imgs/buttons/hoverclose.png"
        );

        addText("moveSpeed", "Move speed", 30, BLACK, {0.093f * wsx, 0.25f * wsy});
        addInputText(
            "moveSpeedInput",
            {0.343f * wsx, 0.25f * wsy, 0.156f * wsx, 0.069f * wsy},
            8,
            30,
            LIGHTGRAY,
            _authorizedChars,
            "",
            [&](Text &text, [[maybe_unused]] size_t &_) {
                try {
                    float speed = std::atoi(text.getString().c_str());
                    SettingsValue::getInstance().setMoveSpeed(speed);
                } catch (std::exception &e) {
                    std::cerr << "Invalid value for move speed!";
                }
            }
        );
        getElement<InputText>("moveSpeedInput")->setText(std::to_string(static_cast<int>(SettingsValue::getInstance().getMoveSpeed())));

        addText("refreshInterval", "Refresh interval", 30, BLACK, {0.109f * wsx, 0.388f * wsy});
        addInputText(
            "refreshIntervalInput",
            {0.343f * wsx, 0.388f * wsy, 0.156f * wsx, 0.069f * wsy},
            8,
            30,
            LIGHTGRAY,
            _authorizedChars,
            "",
            [&](Text &text, [[maybe_unused]] size_t &_) {
                try {
                    std::chrono::milliseconds interval(std::atoi(text.getString().c_str()));
                    SettingsValue::getInstance().setTileRefreshInterval(interval);
                } catch (std::exception &e) {
                    std::cerr << "Invalid value for refresh interval!";
                }
            }
        );
        getElement<InputText>("refreshIntervalInput")->setText(std::to_string(SettingsValue::getInstance().getTileRefreshInterval().count()));

        addSprite("font", "Assets/Imgs/font/gray_font.png", Vector2{0.5f * wsx, 0.5f * wsy}, Vector2{1.0f, 1.0f}, WHITE);
    };

    MiscellaneousSetting::~MiscellaneousSetting() {};

    std::string MiscellaneousSetting::getId() const
    {
        return "MiscellaneousSettingScene";
    }

    void MiscellaneousSetting::events()
    {
    }

    void MiscellaneousSetting::update(double deltaTime)
    {
        for (auto &[_, elem] : _elements)
            elem->update(deltaTime);
    }

    void MiscellaneousSetting::render()
    {
        for (auto &[_, elem] : _elements)
            elem->draw();
    }
}
