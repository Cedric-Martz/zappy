/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** SoundSetting
*/

#ifndef SOUNDSETTING_HPP_
    #define SOUNDSETTING_HPP_
    #include "AScene.hpp"
    #include "Wrapper.hpp"
    #include "RayLib.hpp"

namespace rl
{
    class SoundSetting : public AScene {
        public:
            SoundSetting();
            ~SoundSetting();

            std::string getId() const override;

            void events() override;
            void update(double deltaTime) override;
            void render() override;

        private:
            std::unordered_map<std::string, int> _soundValue;

            RectangleShape _jukboxRect;
            RectangleShape _jukeboxBar;
            RectangleShape _jukeboxProgressBar;
            RectangleShape _soundBar;
            RectangleShape _soundProgressBar;
            RectangleShape _musicBar;
            RectangleShape _musicProgressBar;

            std::string _jukboxString;
            std::unique_ptr<Sprite> _background;
    };
}

#endif /* !SOUNDSETTING_HPP_ */
