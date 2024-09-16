/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Text.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TEXT_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TEXT_HPP
    #include "RayLib.hpp"
    #include "VisualElement.hpp"
    #include "Font.hpp"
    #include "Clickable.hpp"

namespace rl
{
    class Text : public VisualElement, public Clickable {
    public:
        enum class Style {
            REGULAR       = 0,
            BOLD          = 1 << 0,
            ITALIC        = 1 << 1,
            UNDERLINED    = 1 << 2,
            STRIKETHROUGH = 1 << 3
        };

        Text();
        Text(const std::string &string, const unsigned int characterSize = 15);
        Text(const std::string &string, const CustomFont &font, const unsigned int characterSize = 15);

        std::string getString() const;
        unsigned int getCharacterSize() const;
        CustomFont getFont() const;
        Vector2 getSize() const;
        float getSpacing() const;

        void setString(const std::string &string);
        void setCharacterSize(const unsigned int characterSize);
        void setFont(const CustomFont &font);
        void setSize(const Vector2 &size);
        void setSpacing(const float spacing);

        bool isEmpty() const;
        bool isCentered() const;

        void setCenterState(const bool isCentered);

        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;
        VisualElement::Type getType() const override;
        bool isHovered() override;

        void updateOrigin();

    private:
        std::string _string;
        unsigned int _characterSize;
        CustomFont _font;
        bool _hasFontLoaded;
        float _spacing;
        bool _isCentered;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TEXT_HPP*/
