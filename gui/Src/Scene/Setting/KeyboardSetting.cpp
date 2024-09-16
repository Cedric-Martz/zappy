/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** KeyboardSetting
*/

#include "SceneManager.hpp"
#include "KeyboardSetting.hpp"
#include "SettingsValue.hpp"

namespace rl
{
    KeyboardSetting::KeyboardSetting() :
        _authorizedChars("0123456789")
    {
        Vector2 ws = rl::RenderWindow::getInstance().getSize();
        float wsx = ws.x;
        float wsy = ws.y;

        addText("KeyboardSetting", "Keyboard Setting", 70, YELLOW, {0.5f * wsx, 0.0555f * wsy});

        addText("upKey", "Move Up", 30, WHITE, {0.093f * wsx, 0.25f * wsy});
        addInputText("upKeyInput", {0.343f * wsx, 0.25f * wsy, 0.156f * wsx, 0.069f * wsy}, 0, 30, LIGHTGRAY);

        addText("downKey", "Move Down", 30, WHITE, {0.109f * wsx, 0.388f * wsy});
        addInputText("downKeyInput", {0.343f * wsx, 0.388f * wsy, 0.156f * wsx, 0.069f * wsy}, 0, 30, LIGHTGRAY);

        addText("leftKey", "Move Left", 30, WHITE, {0.109f * wsx, 0.527f * wsy});
        addInputText("leftKeyInput", {0.343f * wsx, 0.527f * wsy, 0.156f * wsx, 0.069f * wsy}, 0, 30, LIGHTGRAY);

        addText("rightKey", "Move Right", 30, WHITE, {0.113f * wsx, 0.667f * wsy});
        addInputText("rightKeyInput", {0.343f * wsx, 0.667f * wsy, 0.156f * wsx, 0.069f * wsy}, 0, 30, LIGHTGRAY);

        addText("leftRoll", "Camera Roll Left", 30, WHITE, {0.66f * wsx, 0.25f * wsy});
        addInputText("leftRollInput", {0.85f * wsx, 0.25f * wsy, 0.156f * wsx, 0.069f * wsy}, 0, 30, LIGHTGRAY);

        addText("rightRoll", "Camera Roll Right", 30, WHITE, {0.675f * wsx, 0.388f * wsy});
        addInputText("rightRollInput", {0.85f * wsx, 0.388f * wsy, 0.156f * wsx, 0.069f * wsy}, 0, 30, LIGHTGRAY);

        addText("resetCam", "Camera Reset", 30, WHITE, {0.675f * wsx, 0.527f * wsy});
        addInputText("resetCamInput", {0.85f * wsx, 0.527f * wsy, 0.156f * wsx, 0.069f * wsy}, 0, 30, LIGHTGRAY);

        SettingsValue &settings = SettingsValue::getInstance();
        std::unordered_map<std::string, int> keys = settings.getKeyBind();

        getElement<InputText>("upKeyInput")->setText(std::string(1, keys["upKey"]));
        getElement<InputText>("downKeyInput")->setText(std::string(1, keys["downKey"]));
        getElement<InputText>("leftKeyInput")->setText(std::string(1, keys["leftKey"]));
        getElement<InputText>("rightKeyInput")->setText(std::string(1, keys["rightKey"]));

        getElement<InputText>("leftRollInput")->setText(std::string(1, keys["leftRoll"]));
        getElement<InputText>("rightRollInput")->setText(std::string(1, keys["rightRoll"]));
        getElement<InputText>("resetCamInput")->setText(std::string(1, keys["resetCam"]));

        addButton(
            "quit button",
            Vector2{0.0234f * wsx, 0.0416f * wsy},
            Vector2{0.0468f * wsx, 0.0833f * wsy},
            YELLOW,
            [&]() {
                SceneManager::getInstance().setTransitionSpeed(0.1);
                SceneManager::getInstance().popScene();
            },
            "Assets/Imgs/buttons/buttonclose.png",
            "Assets/Imgs/buttons/hoverclose.png"
        );

        _background = std::make_unique<Sprite>(TextureManager::getInstance().loadTexture("Assets/Imgs/font/yellow_font.png"));
        _background->setTextureRect({0,
                                     0,
                                     static_cast<float>(_background->getTexture().width),
                                     static_cast<float>(_background->getTexture().height)});
        _background->setPosition(Vector2{0.5f * wsx, 0.5f * wsy});
        _background->setScale(Vector2{1.0f, 1.0f});
        _background->setColor(WHITE);
    };

    KeyboardSetting::~KeyboardSetting() {};

    std::string KeyboardSetting::getId() const
    {
        return "KeyboardSettingScene";
    }

    void KeyboardSetting::events()
    {
    }

    void KeyboardSetting::update(double deltaTime)
    {
        SettingsValue &settings = SettingsValue::getInstance();
        std::unordered_map<std::string, int> keys = settings.getKeyBind();

        std::vector<std::string> inputsName = {
            "upKey",
            "downKey",
            "leftKey",
            "rightKey",
            "leftRoll",
            "rightRoll",
            "resetCam"
        };

        for (auto elem : inputsName) {
            std::string key = getElement<InputText>(elem + "Input")->getText().getString();
            if (key.empty())
                continue;
            settings.setKeyBind(elem, toupper(key.front()));
        }
        _background->update(deltaTime);

        for (auto &[_, elem] : _elements)
            elem->update(deltaTime);

    }

    void KeyboardSetting::render()
    {
        _background->draw();
        for (auto &[_, elem] : _elements)
            elem->draw();
    }
}
