/*
** EPITECH PROJECT, 2024
** survivor
** File description:
** SceneManager
*/

#include "SceneManager.hpp"
#include "Wrapper.hpp"
#include "Clock.hpp"

namespace rl
{
    SceneManager &SceneManager::getInstance()
    {
        static SceneManager instance;
        return instance;
    }

    SceneManager::SceneManager()
        : _transitionAlpha(0.0f), _transitionSpeed(0.001f), _precedingSceneTexture{}
    {
    }

    void SceneManager::pushScene(std::unique_ptr<IScene> scene)
    {
        _stackActions.push_back(stackActions::Push);
        _tmpSceneStack.push_back(std::move(scene));
    }

    void SceneManager::setScene(std::unique_ptr<IScene> scene)
    {
        popScene();
        pushScene(std::move(scene));
    }

    void SceneManager::popScene()
    {
        if (!_sceneStack.empty())
            _stackActions.push_back(stackActions::Pop);
    }

    void SceneManager::updateSceneStack()
    {
        while (!_stackActions.empty()) {
            capturePrecedingSceneScreenshot();
            _transitionAlpha = 0.0f;
            if (_stackActions.front() == stackActions::Pop && !_sceneStack.empty()) {
                _sceneStack.pop();
            } else {
                std::unique_ptr<IScene> newScene = std::move(_tmpSceneStack.front());
                _sceneStack.push(std::move(newScene));
                _tmpSceneStack.pop_front();
            }
            _stackActions.pop_front();
        }
    }

    void SceneManager::handleEvents()
    {
        updateSceneStack();

        if (!_sceneStack.empty())
            _sceneStack.top()->events();
    }

    void SceneManager::update()
    {
        if (_sceneStack.empty())
            return;

        double deltaTime = Clock::getInstance().updateDeltaTime().asSeconds();

        _sceneStack.top()->update(deltaTime);
        updateTransition();
    }

    void SceneManager::render()
    {
        Scoped draw;
        RenderWindow::getInstance().clear(WHITE);

        if (!_sceneStack.empty())
            _sceneStack.top()->render();

        drawTransition();
    }

    void SceneManager::updateTransition()
    {
        if (_transitionAlpha < 255.0f) {
            _transitionAlpha += _transitionSpeed * 255.0f;
            if (_transitionAlpha > 255.0f)
                _transitionAlpha = 255.0f;
        }
    }

    void SceneManager::drawTransition()
    {
        if (_transitionAlpha > 0.0 && _transitionAlpha < 255.0f && _precedingSceneTexture.id > 0) {
            Rectangle rec(0.0f, 0.0f, static_cast<float>(_precedingSceneTexture.width), static_cast<float>(_precedingSceneTexture.height));
            RectangleShape shape(
                rec,
                Color{255, 255, 255, static_cast<unsigned char>(255.0f - _transitionAlpha)}
            );
            shape.setOrigin({0.0f, 0.0f});
            shape.setTexture(_precedingSceneTexture);
            shape.setTextureRect(rec);
            shape.draw();
        }
    }

    void SceneManager::setTransitionSpeed(float transitionSpeed)
    {
        _transitionSpeed = transitionSpeed;
    }

    void SceneManager::capturePrecedingSceneScreenshot()
    {
        if (!_sceneStack.empty()) {
            TakeScreenshot("currentScene.png");
            if (_precedingSceneTexture.id > 0)
                UnloadTexture(_precedingSceneTexture);
            _precedingSceneTexture = LoadTexture("currentScene.png");
        }
    }
}
