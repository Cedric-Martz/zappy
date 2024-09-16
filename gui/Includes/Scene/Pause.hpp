/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** Pause
*/

#ifndef PAUSE_HPP_
    #define PAUSE_HPP_

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
    #include "Button.hpp"
    #include "SceneManager.hpp"

namespace rl
{
    class Pause : public AScene {
        public:
            Pause();
            ~Pause();

            std::string getId() const override;

            void events() override;
            void update(double deltaTime) override;
            void render() override;
        private:
            std::shared_ptr<Camera3> _camera;
    };
};

#endif /* !PAUSE_HPP_ */
