/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
    #define MAINMENU_HPP_

    #include <functional>
    #include "AScene.hpp"
    #include "InputText.hpp"
    #include "Text.hpp"
    #include "Wrapper.hpp"
    #include "Camera3.hpp"
    #include "Grid.hpp"
    #include "RenderWindow.hpp"
    #include "Cube.hpp"
    #include "Model3.hpp"
    #include "Sky.hpp"

namespace rl
{
    class MainMenu : public AScene {
        public:
            MainMenu();
            ~MainMenu();

            std::string getId() const override;

            void events() override;
            void update(double deltaTime) override;
            void render() override;
        private:
            void updateAlphaElements(const float alpha);
            void updateTitleByWindow(double deltaTime);
            void detectBoomShortcut();

            std::shared_ptr<Camera3> _camera;
            bool zoom;

            bool _canDisplayMenu;
            float _alpha;
            float _starsTimebank;
            float _cameraMoveSpeed;
            Sky _sky;

            int _titleCharOffset;
            std::unordered_map<std::string, Transform> _transforms;
            Vector2 _firstWindowPosition;
            Vector2 _windowOffset;

            bool _onduloscopeMode;

            std::array<int, 4> _boomKeys;
            size_t _boomIndex;
            bool _boomEnabled;
    };
};

#endif /* !MAINMENU_HPP_ */
