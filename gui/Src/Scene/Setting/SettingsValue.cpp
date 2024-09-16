/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** SettingsValue
*/

#include "SettingsValue.hpp"
#include "RenderWindow.hpp"

namespace rl
{
    SettingsValue &SettingsValue::getInstance()
    {
        static SettingsValue instance;
        return instance;
    }


    void SettingsValue::setWindowMode(enum ScreenMode mode)
    {
        if (_mode == mode)
            return;
        RenderWindow &window = RenderWindow::getInstance();

        _mode = mode;
        window.toggleFullscreen();
    }

    enum ScreenMode SettingsValue::getWindowMode() const
    {
        return _mode;
    }

    void SettingsValue::setGraphicalPreset(enum GraphicalPreset preset)
    {
        _graphical = preset;

    }

    enum GraphicalPreset SettingsValue::getGraphicalPreset() const
    {
        return _graphical;
    }

    void SettingsValue::setFramerateLimit(enum FPSLimit limit)
    {
        _framerate = limit;
        RenderWindow::getInstance().setFrameLimit(_framerate);
    }

    enum FPSLimit SettingsValue::getFramerateLimit() const
    {
        return _framerate;
    }

    void SettingsValue::setColorimetry(enum Colorimetry color)
    {
        _colorimetry = color;
    }

    enum Colorimetry SettingsValue::getColorimetry() const
    {
        return _colorimetry;
    }

    void SettingsValue::setSoundVolume(float volume)
    {
        if (volume < 0.0) {
            _soundVolume = 0.0;
            return;
        }
        if (volume > 1.0) {
            _soundVolume = 1.0;
            return;
        }
        _soundVolume = volume;
    }

    float SettingsValue::getSoundVolume() const
    {
        return _soundVolume;
    }

    void SettingsValue::setJukeboxVolume(float volume)
    {
        if (volume < 0.0) {
            _JukeboxVolume = 0.0;
            return;
        }
        if (volume > 1.0) {
            _JukeboxVolume = 1.0;
            return;
        }
        _JukeboxVolume = volume;
    }

    float SettingsValue::getJukeboxVolume() const
    {
        return _JukeboxVolume;
    }

    void SettingsValue::setMusicVolume(float volume)
    {
        if (volume < 0.0) {
            _musicVolume = 0.0;
            return;
        }
        if (volume > 1.0) {
            _musicVolume = 1.0;
            return;
        }
        _musicVolume = volume;
    }

    float SettingsValue::getMusicVolume() const
    {
        return _musicVolume;
    }

    void SettingsValue::setKeyBind(std::string id, int value)
    {
        _keyBind[id] = value;
    }

    std::unordered_map<std::string, int> SettingsValue::getKeyBind() const
    {
        return _keyBind;
    }

    void SettingsValue::setMoveSpeed(const float moveSpeed)
    {
        _moveSpeed = moveSpeed;
    }

    float SettingsValue::getMoveSpeed() const
    {
        return _moveSpeed;
    }

    void SettingsValue::setTileRefreshInterval(const std::chrono::milliseconds interval)
    {
        _tileRefreshInterval = interval;
    }

    std::chrono::milliseconds SettingsValue::getTileRefreshInterval() const
    {
        return _tileRefreshInterval;
    }

    void SettingsValue::setLastGuiResult(std::string result)
    {
        _lastGuiResult = result;
    }

    std::string SettingsValue::getLastGuiResult() const
    {
        return _lastGuiResult;
    }

    void SettingsValue::setLastAdminResult(std::string result)
    {
        _lastAdminResult = result;
    }

    std::string SettingsValue::getLastAdminResult() const
    {
        return _lastAdminResult;
    }

    SettingsValue::SettingsValue()
    {
        // Resolution Settings
        _mode = WINDOW;
        _graphical = LOW;
        _framerate = NORMAL_FPS;
        _colorimetry = NORMAL;
        // Sounds Settings
        _soundVolume = 0.5;
        _JukeboxVolume = 0.5;
        _musicVolume = 0.5;
        // Keyboard Settings
        _keyBind = {
            {"upKey", KEY_Z},
            {"downKey", KEY_S},
            {"leftKey", KEY_Q},
            {"rightKey", KEY_D},
            {"upCam", KEY_UP},
            {"downCam", KEY_DOWN},
            {"leftCam", KEY_LEFT},
            {"rightCam", KEY_RIGHT},
            {"rightRoll", KEY_E},
            {"leftRoll", KEY_A},
            {"resetCam", KEY_R},
        };
        // Miscellaneous Settings
        _moveSpeed = 1000.0f;
        _tileRefreshInterval = std::chrono::milliseconds(300);
        // Admin Commands
        _lastGuiResult = "";
        _lastAdminResult = "";
    }
}
