/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ResolutionSetting
*/

#include "SceneManager.hpp"
#include "ResolutionSetting.hpp"

namespace rl
{
    ResolutionSetting::ResolutionSetting()
    {
        SettingsValue &settings = SettingsValue::getInstance();
        Vector2 ws = rl::RenderWindow::getInstance().getSize();
        float wsx = ws.x;
        float wsy = ws.y;

        AScene::addText("ResolutionSetting", "Resolution Settings", 70, BLUE, {0.5f * wsx, 0.0555f * wsy});
        AScene::addText("Windowmode", "Window Mode", 30, BLACK, {0.5f * wsx, 0.194f * wsy});
        AScene::addText("graph", "Graphical Preset", 30, BLACK, {0.5f * wsx, 0.388f * wsy});
        AScene::addText("Frame", "Limit Frame Rate", 30, BLACK, {0.5f * wsx, 0.583f * wsy});
        AScene::addText("Colorblind", "Color Blind Mode", 30, BLACK, {0.5f * wsx, 0.777f * wsy});

        addButton(
            "quit button",
            Vector2{0.0234f * wsx, 0.0416f * wsy},
            Vector2{0.0468f * wsx, 0.0833f * wsy},
            BLUE,
            [&]() {

                SceneManager::getInstance().setTransitionSpeed(0.1);
                SceneManager::getInstance().popScene();
            },
            "Assets/Imgs/buttons/buttonclose.png",
            "Assets/Imgs/buttons/hoverclose.png"
        );

        AScene::addButton(
            "Window mode UP",
            Vector2{0.656f * wsx, 0.284f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &instance  = SettingsValue::getInstance();
                ScreenMode mode = instance.getWindowMode();
                if (mode < ScreenMode::FULL)
                    instance.setWindowMode(static_cast<ScreenMode>(mode + 1));
            },
            "Assets/Imgs/buttons/next_arrow.png",
            "Assets/Imgs/buttons/next_arrow.png"
        );

        AScene::addButton(
            "Window mode DOWN",
            Vector2{0.343f * wsx, 0.284f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            WHITE,
            [&]() {
                SettingsValue &instance  = SettingsValue::getInstance();
                ScreenMode mode = instance.getWindowMode();
                if (mode > ScreenMode::WINDOW)
                    instance.setWindowMode(static_cast<ScreenMode>(mode - 1));
            },
            "Assets/Imgs/buttons/prev_arrow.png",
            "Assets/Imgs/buttons/prev_arrow.png"
        );

        AScene::addButton(
            "Graphical mode UP",
            Vector2{0.656f * wsx, 0.479f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &instance  = SettingsValue::getInstance();
                GraphicalPreset preset = instance.getGraphicalPreset();
                if (preset < GraphicalPreset::HIGH)
                    instance.setGraphicalPreset(static_cast<GraphicalPreset>(preset + 1));
            },
            "Assets/Imgs/buttons/next_arrow.png",
            "Assets/Imgs/buttons/next_arrow.png"
        );

        AScene::addButton(
            "Graphical mode DOWN",
            Vector2{0.343f * wsx, 0.479f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &instance  = SettingsValue::getInstance();
                GraphicalPreset preset = instance.getGraphicalPreset();
                if (preset > GraphicalPreset::LOW)
                    instance.setGraphicalPreset(static_cast<GraphicalPreset>(preset - 1));
            },
            "Assets/Imgs/buttons/prev_arrow.png",
            "Assets/Imgs/buttons/prev_arrow.png"
        );

        AScene::addButton(
            "FPS mode UP",
            Vector2{0.656f * wsx, 0.68f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &instance  = SettingsValue::getInstance();
                size_t limit = instance.getFramerateLimit();
                if (limit < FPSLimit::EXTREME_FPS)
                    instance.setFramerateLimit(static_cast<FPSLimit>(limit * 2));
            },
            "Assets/Imgs/buttons/next_arrow.png",
            "Assets/Imgs/buttons/next_arrow.png"
        );

        AScene::addButton(
            "FPS mode DOWN",
            Vector2{0.343f * wsx, 0.68f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &instance  = SettingsValue::getInstance();
                size_t limit = instance.getFramerateLimit();
                if (limit > FPSLimit::LOW_FPS)
                    instance.setFramerateLimit(static_cast<FPSLimit>(limit / 2));
            },
            "Assets/Imgs/buttons/prev_arrow.png",
            "Assets/Imgs/buttons/prev_arrow.png"
        );

        AScene::addButton(
            "Color blind UP",
            Vector2{0.656f * wsx, 0.881f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &instance  = SettingsValue::getInstance();
                Colorimetry color = instance.getColorimetry();
                if (color < Colorimetry::TRITANOPIE)
                    instance.setColorimetry(static_cast<Colorimetry>(color + 1));
            },
            "Assets/Imgs/buttons/next_arrow.png",
            "Assets/Imgs/buttons/next_arrow.png"
        );

        AScene::addButton(
            "Color blind DOWN",
            Vector2{0.343f * wsx, 0.881f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &instance  = SettingsValue::getInstance();
                Colorimetry color = instance.getColorimetry();
                if (color > Colorimetry::NORMAL)
                    instance.setColorimetry(static_cast<Colorimetry>(color - 1));
            },
            "Assets/Imgs/buttons/prev_arrow.png",
            "Assets/Imgs/buttons/prev_arrow.png"
        );

        _windowRect.setPosition(Vector2{0.402f * wsx, 0.25f * wsy});
        _windowRect.setSize(0.195f * wsx, 0.069 * wsy);
        _windowRect.setColor(GRAY);

        _graphicalRect.setPosition(Vector2{0.402f * wsx, 0.444f * wsy});
        _graphicalRect.setSize(0.195f * wsx, 0.069 * wsy);
        _graphicalRect.setColor(GRAY);

        _fpsRect.setPosition(Vector2{0.402f * wsx, 0.645f * wsy});
        _fpsRect.setSize(0.195f * wsx, 0.069 * wsy);
        _fpsRect.setColor(GRAY);

        _colorBlindRect.setPosition(Vector2{0.402f * wsx, 0.847f * wsy});
        _colorBlindRect.setSize(0.195f * wsx, 0.069 * wsy);
        _colorBlindRect.setColor(GRAY);

        AScene::addText("window mode value", windowModeToString(settings.getWindowMode()), 30, BLACK, {0.5f * wsx, 0.284f * wsy});
        AScene::addText("graph mode value", graphModeToString(settings.getGraphicalPreset()), 30, BLACK, {0.5f * wsx, 0.479f * wsy});
        AScene::addText("FPS mode value", fpsModeToString(settings.getFramerateLimit()), 30, BLACK, {0.5f * wsx, 0.68f * wsy});
        AScene::addText("color blind mode value", daltoModeToString(settings.getColorimetry()), 30, BLACK, {0.5f * wsx, 0.881f * wsy});

        _background = std::make_unique<Sprite>(TextureManager::getInstance().loadTexture("Assets/Imgs/font/gray_font.png"));
        _background->setTextureRect({0,
                                     0,
                                     static_cast<float>(_background->getTexture().width),
                                     static_cast<float>(_background->getTexture().height)});
        _background->setPosition(Vector2{0.5f * wsx, 0.5f * wsy});
        _background->setScale(Vector2{1.0f, 1.0f});
        _background->setColor(WHITE);
    };

    ResolutionSetting::~ResolutionSetting() {};

    std::string ResolutionSetting::getId() const
    {
        return "ResolutionSettingScene";
    }

    void ResolutionSetting::events()
    {
    }

    void ResolutionSetting::update(double deltaTime)
    {
        SettingsValue &settings  = SettingsValue::getInstance();

        _background->update(deltaTime);

        for (auto &object : _elements)
            object.second->update(deltaTime);
        std::shared_ptr<Text> _window_mode = getElement<Text>("window mode value");
        _window_mode->setString(windowModeToString(settings.getWindowMode()));
        std::shared_ptr<Text> _graph_mode = getElement<Text>("graph mode value");
        _graph_mode->setString(graphModeToString(settings.getGraphicalPreset()));
        std::shared_ptr<Text> _frame_mode = getElement<Text>("FPS mode value");
        _frame_mode->setString(fpsModeToString(settings.getFramerateLimit()));
        std::shared_ptr<Text> _blind_mode = getElement<Text>("color blind mode value");
        _blind_mode->setString(daltoModeToString(settings.getColorimetry()));
    }

    void ResolutionSetting::render()
    {
        _background->draw();
        _windowRect.draw();
        _fpsRect.draw();
        _graphicalRect.draw();
        _colorBlindRect.draw();
        for (auto &object : _elements)
            object.second->draw();

    }

    std::string ResolutionSetting::windowModeToString(ScreenMode mode) const
    {
        switch(mode) {
            case WINDOW: return "WINDOW";
            case FULL: return "FULL";
            default: return "UNKNOWN";
        }
    }

    std::string ResolutionSetting::graphModeToString(GraphicalPreset preset) const
    {
        switch(preset) {
            case LOW: return "LOW";
            case MEDIUM: return "MEDIUM";
            case HIGH: return "HIGH";
            default: return "UNKNOWN";
        }
    }

    std::string ResolutionSetting::fpsModeToString(enum FPSLimit limit) const
    {
        switch(limit) {
            case LOW_FPS: return "30";
            case NORMAL_FPS: return "60";
            case HIGH_FPS: return "120";
            case EXTREME_FPS: return "NO_LIMIT";
            default: return "UNKNOWN";
        }
    }

    std::string ResolutionSetting::daltoModeToString(Colorimetry color) const
    {
        switch(color) {
            case NORMAL: return "NORMAL";
            case PROTANOPIE: return "PROTANOPIE";
            case DEUTERANOPIE: return "DEUTERANOPIE";
            case TRITANOPIE: return "TRITANOPIE";
            default: return "UNKNOWN";
        }
    }
}
