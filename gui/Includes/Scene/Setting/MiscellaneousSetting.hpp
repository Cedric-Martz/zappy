/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** MiscellaneousSetting
*/

#ifndef MISCELLANEOUSSETTING_HPP_
    #define MISCELLANEOUSSETTING_HPP_
    #include "AScene.hpp"

namespace rl
{
    class MiscellaneousSetting : public AScene {
        public:
            MiscellaneousSetting();
            ~MiscellaneousSetting();

            std::string getId() const override;

            void events() override;
            void update(double deltaTime) override;
            void render() override;

        private:
            std::string _authorizedChars;
    };
}


#endif /* !MISCELLANEOUSSETTING_HPP_ */
