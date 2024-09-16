/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** RenderWindow.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RENDERWINDOW_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RENDERWINDOW_HPP
    #include "RayLib.hpp"

namespace rl
{
    class RenderWindow {
    public:
        static RenderWindow &getInstance();

        Vector2 getSize();

        void open();

        void applyFlag(const ConfigFlags flag);
        void setFrameLimit(size_t fps);
        void setTitle(const std::string &filepath);
        void updateSize(const Vector2 &newSize);
        bool isOpen();
        void clear(const Color color = BLACK);
        void close();
        Vector2 getPosition() const;
        void toggleFullscreen();

    private:
        RenderWindow();
        ~RenderWindow();
        bool _hasOpened;
        size_t _width;
        size_t _height;
        const std::string _name;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_RENDERWINDOW_HPP*/
