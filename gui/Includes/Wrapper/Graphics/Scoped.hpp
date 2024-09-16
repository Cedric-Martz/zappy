/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ScopedDraw.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SCOPEDDRAW_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SCOPEDDRAW_HPP
    #include "RayLib.hpp"
    #include "Camera2.hpp"
    #include "Camera3.hpp"

namespace rl
{
    class Scoped {
    public:
        enum class Mode {
            DRAW,
            MODE2D,
            MODE3D
        };

        Scoped();
        Scoped(Camera2 &camera);
        Scoped(std::shared_ptr<Camera3> camera);
        ~Scoped();

        Mode getMode() const;
    private:
        Mode _mode;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SCOPEDDRAW_HPP*/
