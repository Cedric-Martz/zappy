/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Button.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_BUTTON_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_BUTTON_HPP
    #include "RectangleShape.hpp"

namespace rl
{
    class Button : public RectangleShape {
    public:
        Button(const Rectangle rectangle,
               const Color color,
               std::function<void()> onClick,
               const std::string &textureName = "",
               const std::string &onHoverTextureName = "");
        ~Button();

        void draw() override;
        void update(double deltaTime) override;

        std::function<void()> _onClickFunction;

    private:
        Texture _textureOnHover;
        Texture _generalTexture;
        bool _isHovered;
        bool _hasGeneralTextureLoaded;
        bool _hasOnHoverTextureLoaded;
    };
}

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_BUTTON_HPP*/
