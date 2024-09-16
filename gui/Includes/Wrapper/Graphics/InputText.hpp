/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** InputText.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_INPUTTEXT_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_INPUTTEXT_HPP
    #include "RectangleShape.hpp"
    #include "Text.hpp"

namespace rl
{
    class InputText : public RectangleShape {
    public:
        InputText(
            const Rectangle rectangle = Rectangle(0, 0, 0, 0),
            const size_t maxCharactersNumber = 20,
            const std::string &accepted = "",
            const std::string &rejected = "",
            std::function<void(Text &, size_t &)> onEnter = nullptr,
            std::function<void()> onFocus = nullptr,
            std::function<void()> onUnfocus = nullptr
        );
        ~InputText();

        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;
        VisualElement::Type getType() const override;

        size_t getMaxCharactersNumber() const;
        void setText(const std::string &text);
        Text &getText();
        bool isActive() const;

        void setMaxCharactersNumber(const size_t maxCharactersNumber);

        void handleInput(const float deltaTime);

    private:
        bool isCharValid(int c);

        Text _text;
        size_t _maxCharactersNumber;

        bool _isActive;

        bool _cursorVisible;
        float _cursorTimer;
        size_t _cursorPos;
        float _backspaceTimer;
        float _leftTimer;
        float _rightTimer;
        const float _initialDelay = 0.5f;
        const float _repeatDelay = 0.05f;

        std::string _accepted;
        std::string _rejected;

        std::function<void(Text&, size_t &)> _onEnter;
        std::function<void()> _onFocus;
        std::function<void()> _onUnfocus;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_INPUTTEXT_HPP*/
