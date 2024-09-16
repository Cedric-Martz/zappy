/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** KeyboardSetting
*/

#ifndef KEYBOARDSETTING_HPP_
    #define KEYBOARDSETTING_HPP_
    #include "AScene.hpp"
    #include "Wrapper.hpp"
    #include "RayLib.hpp"

namespace rl
{
    class KeyboardSetting : public AScene {
        public:
            KeyboardSetting();
            ~KeyboardSetting();

            std::string getId() const override;

            void events() override;
            void update(double deltaTime) override;
            void render() override;

        private:
            std::string _authorizedChars;

            std::unique_ptr<Sprite> _background;
    };
}

#endif /* !KEYBOARDSETTING_HPP_ */
