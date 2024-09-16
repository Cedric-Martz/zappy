/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** SplashScreen.hpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

namespace rl {
    class SplashScreenManager {
    public:
        static SplashScreenManager &getInstance();
        std::string run(const std::string &filepath);

    private:
        SplashScreenManager();
        ~SplashScreenManager();
    };
}
