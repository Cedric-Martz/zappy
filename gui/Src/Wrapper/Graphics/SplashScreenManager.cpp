/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** SplashScreenManager.cpp
*/

#include "SplashScreenManager.hpp"

namespace rl {
    SplashScreenManager &SplashScreenManager::getInstance()
    {
        static SplashScreenManager instance;
        return instance;
    }

    SplashScreenManager::SplashScreenManager() {}

    SplashScreenManager::~SplashScreenManager() {}

    std::string SplashScreenManager::run(const std::string &filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Unable to open file\n";
            return "";
        }

        int lineCount = 0;
        std::string line;
        while (std::getline(file, line)) {
            ++lineCount;
        }

        if (lineCount == 0) {
            std::cerr << "The file is empty\n";
            return "";
        }

        std::srand(std::time(nullptr));
        int randomLineNumber = std::rand() % lineCount;

        file.clear();
        file.seekg(0);

        for (int i = 0; i < randomLineNumber; ++i) {
            std::getline(file, line);
        }
        std::getline(file, line);

        file.close();
        return line;
    }
}
