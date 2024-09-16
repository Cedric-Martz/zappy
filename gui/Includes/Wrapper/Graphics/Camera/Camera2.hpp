/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Camera2.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_Camera2_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_Camera2_HPP
    #include "RayLib.hpp"

namespace rl
{
    class Camera2 {
    public:
        Camera2();
        ~Camera2();

        Camera2D &getSource();

    private:
        Camera2D _camera;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_Camera2_HPP*/
