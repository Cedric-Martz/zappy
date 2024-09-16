/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** MainSetting
*/

#ifndef MAINSETTING_HPP_
    #define MAINSETTING_HPP_
    #include "AScene.hpp"
    #include <cmath>

namespace rl
{
    class MainSetting : public AScene {
        public:
            MainSetting();
            ~MainSetting();

            std::string getId() const override;

            void events() override;
            void update(double deltaTime) override;
            void render() override;

        private:
            std::unique_ptr<Sprite> _background;
    };
}

#endif /* !MAINSETTING_HPP_ */
