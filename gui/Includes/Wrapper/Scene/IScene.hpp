/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

    #include <memory>

namespace rl
{
    class IScene {
        public:
            virtual ~IScene() = default;

            virtual void events() = 0;
            virtual void render() = 0;
            virtual void update(double deltaTime) = 0;
    };
}

#endif /* !ISCENE_HPP_ */
