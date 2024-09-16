/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ResolutionSetting
*/

#ifndef RESOLUTION_SETTING_HPP_
    #define RESOLUTION_SETTING_HPP_
    #include "AScene.hpp"
    #include "Wrapper.hpp"
    #include "RayLib.hpp"
    #include "SettingsValue.hpp"

namespace rl
{
    class ResolutionSetting : public AScene {
        public:
            ResolutionSetting();
            ~ResolutionSetting();

            std::string getId() const override;

            void events() override;
            void update(double deltaTime) override;
            void render() override;

        private:
            RectangleShape _windowRect;
            RectangleShape _fpsRect;
            RectangleShape _graphicalRect;
            RectangleShape _colorBlindRect;

            std::string windowModeToString(ScreenMode mode) const;
            std::string graphModeToString(GraphicalPreset preset) const;
            std::string fpsModeToString(enum FPSLimit limit) const;
            std::string daltoModeToString(Colorimetry color) const;

            std::unique_ptr<Sprite> _background;
    };

}

#endif /* !RESOLUTIONSETTING_HPP_ */
