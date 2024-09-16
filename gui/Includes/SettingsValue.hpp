/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** SettingsValue
*/

#ifndef SETTINGSVALUE_HPP_
    #define SETTINGSVALUE_HPP_
    #include <iostream>
    #include <unordered_map>
    #include <chrono>

namespace rl
{
    enum ScreenMode {
        WINDOW = 0,
        FULL
    };

    enum GraphicalPreset {
        LOW = 0,
        MEDIUM = 1,
        HIGH = 2
    };

    enum FPSLimit {
        LOW_FPS = 30,
        NORMAL_FPS = 60,
        HIGH_FPS = 120,
        EXTREME_FPS = 240
    };

    enum Colorimetry {
        NORMAL = 0,
        PROTANOPIE = 1,
        DEUTERANOPIE = 2,
        TRITANOPIE = 3
    };

    class SettingsValue {
        public:
            static SettingsValue &getInstance();

            // Resolution Settings
            void setWindowMode(enum ScreenMode mode);
            enum ScreenMode getWindowMode() const;
            void setGraphicalPreset(enum GraphicalPreset preset);
            enum GraphicalPreset getGraphicalPreset() const;
            void setFramerateLimit(enum FPSLimit limit);
            enum FPSLimit getFramerateLimit() const;
            void setColorimetry(enum Colorimetry color);
            enum Colorimetry getColorimetry() const;
            // Sounds Settings
            void setSoundVolume(float volume);
            float getSoundVolume() const;
            void setJukeboxVolume(float volume);
            float getJukeboxVolume() const;
            void setMusicVolume(float volume);
            float getMusicVolume() const;
            // Keyboard Settings
            void setKeyBind(std::string id, int value);
            std::unordered_map<std::string, int> getKeyBind() const;
            // Miscallenaous Settings
            void setMoveSpeed(const float moveSpeed);
            float getMoveSpeed() const;
            void setTileRefreshInterval(const std::chrono::milliseconds interval);
            std::chrono::milliseconds getTileRefreshInterval() const;;
            // GUI debug commands
            void setLastGuiResult(std::string result);
            std::string getLastGuiResult() const;
            // Admin Commands
            void setLastAdminResult(std::string result);
            std::string getLastAdminResult() const;

        private:
            SettingsValue();
            ~SettingsValue() = default;

            // Resolution Settings
            enum ScreenMode _mode;
            enum GraphicalPreset _graphical;
            enum FPSLimit _framerate;
            enum Colorimetry _colorimetry;
            // Sounds Settings
            float _soundVolume;
            float _JukeboxVolume;
            float _musicVolume;
            // Keyboard Settings
            std::unordered_map<std::string, int> _keyBind;
            // Miscellaneous Settings
            float _moveSpeed;
            std::chrono::milliseconds _tileRefreshInterval;
            // Admin Commands
            std::string _lastGuiResult;
            std::string _lastAdminResult;
    };
}
#endif /* !SETTINGSVALUE_HPP_ */
