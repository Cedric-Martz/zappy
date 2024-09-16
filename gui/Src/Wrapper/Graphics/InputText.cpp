/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** InputText.cpp
*/

#include "Keyboard.hpp"
#include "InputText.hpp"

namespace rl
{
    InputText::InputText(
        const Rectangle rectangle,
        const size_t maxCharactersNumber,
        const std::string &accepted,
        const std::string &rejected,
        std::function<void(Text&, size_t &)> onEnter,
        std::function<void()> onFocus,
        std::function<void()> onUnfocus
    )
        : RectangleShape(rectangle, BLACK),
        _maxCharactersNumber(maxCharactersNumber),
        _isActive(false),
        _cursorVisible(false),
        _cursorTimer(0.0f),
        _cursorPos(0),
        _backspaceTimer(0.0f),
        _leftTimer(0.0f),
        _rightTimer(0.0f),
        _accepted(accepted),
        _rejected(rejected),
        _onEnter(onEnter),
        _onFocus(onFocus),
        _onUnfocus(onUnfocus)
    {
        _position.x = rectangle.x;
        _position.y = rectangle.y;
        _size.x = rectangle.width;
        _size.y = rectangle.height;
        _origin.x = _size.x / 2.0f;
        _origin.y = _size.y / 2.0f;
        _text.setColor(BLACK);
        _text.setPosition(_position.x, _position.y);
    }

    InputText::~InputText() {}

    void InputText::draw()
    {
        RectangleShape::draw();

        _text.draw();

        if (_isActive && _cursorVisible) {
            Vector2 trueTextPos = _text.getPosition2() - (_text.getSize() / 2.0f);
            unsigned int fontSize = _text.getCharacterSize();
            float cursorX = trueTextPos.x + MeasureText(_text.getString().substr(0, _cursorPos).c_str(), fontSize);
            DrawLine(cursorX, trueTextPos.y, cursorX, trueTextPos.y + fontSize + 8, BLACK);
        }
    }

    void InputText::applyTransform([[maybe_unused]] Transform &transform) {}

    void InputText::update(double deltaTime)
    {
        if (isClicked()) {
            _isActive = true;
            if (_onFocus)
                _onFocus();
        } else if (!isHovered() && Mouse::getInstance().isButtonPressed()) {
            _isActive = false;
            _backspaceTimer = false;
            _leftTimer = false;
            _rightTimer = false;
            if (_onUnfocus)
                _onUnfocus();
        }

        updateRainbow(deltaTime);

        _cursorTimer += deltaTime;
        if (_cursorTimer >= 0.5f) {
            _cursorTimer = 0.0f;
            _cursorVisible = !_cursorVisible;
        }

        if (_isActive)
            handleInput(deltaTime);
    }

    VisualElement::Type InputText::getType() const
    {
        return VisualElement::Type::INPUT_TEXT;
    }

    size_t InputText::getMaxCharactersNumber() const
    {
        return _maxCharactersNumber;
    }

    void InputText::setText(const std::string &text)
    {
        _text.setString(text);
        _cursorPos = text.size();
    }

    Text &InputText::getText()
    {
        return _text;
    }

    bool InputText::isActive() const
    {
        return _isActive;
    }

    void InputText::setMaxCharactersNumber(const size_t maxCharactersNumber)
    {
        _maxCharactersNumber = maxCharactersNumber;
    }

    void InputText::handleInput(const float deltaTime)
    {
        Keyboard &k = Keyboard::getInstance();

        for (auto &c : k.getCharPressedList())
            if (isCharValid(c) && _text.getString().size() <= _maxCharactersNumber)
                _text.setString(_text.getString().insert(_cursorPos++, 1, c));

        if (_cursorPos > 0) {
            if (k.isKeyPressed(KEY_BACKSPACE)) {
                _text.setString(_text.getString().erase(_cursorPos-- - 1, 1));
                _backspaceTimer = 0.0f;
            } else if (k.isKeyDown(KEY_BACKSPACE)) {
                _backspaceTimer += deltaTime;
                if (_backspaceTimer >= _initialDelay) {
                    _text.setString(_text.getString().erase(_cursorPos-- - 1, 1));
                    _backspaceTimer = _initialDelay - _repeatDelay;
                }
            } else
                _backspaceTimer = 0.0f;
        }

        if (_cursorPos > 0) {
            if (k.isKeyPressed(KEY_LEFT)) {
                --_cursorPos;
                _leftTimer = 0.0f;
            } else if (k.isKeyDown(KEY_LEFT)) {
                _leftTimer += deltaTime;
                if (_leftTimer >= _initialDelay) {
                    --_cursorPos;
                    _leftTimer = _initialDelay - _repeatDelay;
                }
            } else
                _leftTimer = 0.0f;
        }

        if (_cursorPos < _text.getString().size()) {
            if (k.isKeyPressed(KEY_RIGHT)) {
                ++_cursorPos;
                _rightTimer = 0.0f;
            } else if (k.isKeyDown(KEY_RIGHT)) {
                _rightTimer += deltaTime;
                if (_rightTimer >= _initialDelay) {
                    ++_cursorPos;
                    _rightTimer = _initialDelay - _repeatDelay;
                }
            } else
                _rightTimer = 0.0f;
        }

        if (k.isKeyPressed(KEY_ENTER)) {
            if (_onEnter)
                _onEnter(_text, _cursorPos);
        }
    }

    bool InputText::isCharValid(int c)
    {
        bool isAccepted = false;
        bool isRejected = false;

        if (!_accepted.empty())
            isAccepted = std::find(_accepted.begin(), _accepted.end(), c) != _accepted.end();
        else if (c >= 32 && c <= 125)
            isAccepted = true;

        if (!_rejected.empty())
            isRejected = std::find(_rejected.begin(), _rejected.end(), c) != _rejected.end();

        return isAccepted && !isRejected;
    }
};
