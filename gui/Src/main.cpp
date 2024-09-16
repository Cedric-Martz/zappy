/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** main
*/

#include "Wrapper.hpp"
#include "SceneManager.hpp"
#include "MainMenu.hpp"
#include "Game.hpp"
#include "NetworkManager.hpp"
#include "ArgumentParser.hpp"

using
    rl::RenderWindow,
    rl::SceneManager,
    rl::ArgumentParser,
    rl::MainMenu;

int main(int argc, char **argv)
{
    RenderWindow &window = RenderWindow::getInstance();
    SceneManager &manager = SceneManager::getInstance();
    ArgumentParser &parser = ArgumentParser::getInstance();

    if (!parser.setInfo(argc, argv))
        return 84;

    window.open();
    window.setTitle("Zappy");
    window.setFrameLimit(60);
    manager.pushScene(std::make_unique<MainMenu>());

    while (window.isOpen()) {
        manager.handleEvents();
        manager.update();
        manager.render();
    }
    window.close();

    return 0;
}
