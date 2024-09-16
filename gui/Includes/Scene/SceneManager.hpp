/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
    #define SCENEMANAGER_HPP_

    #include <memory>
    #include <stack>
    #include <deque>
    #include "IScene.hpp"
    #include "RayLib.hpp"

namespace rl
{
    class SceneManager {
        public:
            static SceneManager &getInstance();

            void pushScene(std::unique_ptr<IScene> scene);
            void setScene(std::unique_ptr<IScene> scene);
            void popScene();
            void handleEvents();
            void update();
            void render();

            void drawTransition();
            void setTransitionSpeed(float transitionSpeed);

        private:
            SceneManager();
            ~SceneManager() = default;

            void updateSceneStack();

            void updateTransition();
            void capturePrecedingSceneScreenshot();

            enum class stackActions {
                Push,
                Pop
            };

            std::deque<stackActions> _stackActions;
            std::deque<std::unique_ptr<IScene>> _tmpSceneStack;
            std::stack<std::unique_ptr<IScene>> _sceneStack;

            float _transitionAlpha;
            float _transitionSpeed;

            Texture2D _precedingSceneTexture;
    };
}

#endif /* !SCENEMANAGER_HPP_ */
