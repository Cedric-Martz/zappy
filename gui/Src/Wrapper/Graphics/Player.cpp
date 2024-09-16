/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Player.cpp
*/

#include "Player.hpp"

namespace rl {
    Player::Player()
        : Model3(),
        _hasBeenClicked(false),
        _isBroadcasting(false),
        _waitingForServerResponse(false),
        _walkTimebank(0.0f)
    {
        setLevel(0);
        _levelText.setPosition(90, 160);
        _levelText.setColor(WHITE);
        _levelText.setCharacterSize(30);
        _broadcastSphere.setSize(0);
        _broadcastSphere.setColor(ColorAlpha(BLUE, 0.1f));
        _position = Vector3(-1, -1, -1);
    }

    Player::Player(const std::string &modelFilepath, std::shared_ptr<Camera3> camera)
        : Model3(modelFilepath, camera),
        _hasBeenClicked(false),
        _isBroadcasting(false),
        _waitingForServerResponse(false),
        _walkTimebank(0.0f)
    {
        setLevel(0);
        _levelText.setPosition(90, 160);
        _levelText.setColor(WHITE);
        _levelText.setCharacterSize(30);
        _broadcastSphere.setSize(0);
        _broadcastSphere.setColor(ColorAlpha(BLUE, 0.1f));
    }

    Player::~Player() {}

    void Player::update(double deltaTime)
    {
        Model3::update(deltaTime);

        if (_hasBeenClicked && !Model3::isHovered() && Mouse::getInstance().isButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
            _hasBeenClicked = false;
        if (!_hasBeenClicked && Model3::isClicked())
            _hasBeenClicked = true;
        _inventory.update(deltaTime);
        if (_isBroadcasting) {
            _broadcastSphere.setPosition(getPosition3());
            _broadcastSphere.setSize(_broadcastSphere.getSize() + 1.0f);
        }
        if (_isBroadcasting && _broadcastSphere.getSize() > 25.0f) {
            _isBroadcasting = false;
            _broadcastSphere.setSize(0);
        }

        if (_walkQueue.empty())
            return;
        _walkTimebank += deltaTime;
        if (_walkTimebank < 0.001f)
            return;
        _walkTimebank = 0.0f;
        const Vector2 &destination = _walkQueue.front();
        if (std::abs(destination.x - _position.x) > 5.0f || std::abs(destination.y - _position.z) > 5.0f) {
            _position.x = destination.x;
            _position.z = destination.y;
            _walkQueue.pop();
        } else {
            if (std::abs(destination.x - _position.x) > 1.0f)
                _position.x -= destination.x > _position.x ? -1.0f : 1.0f;
            if (std::abs(destination.y - _position.z) > 1.0f)
                _position.z -= destination.y > _position.z ? -1.0f : 1.0f;
            if (std::abs(destination.x - _position.x) <= 1.0f &&
                std::abs(destination.y - _position.z) <= 1.0f) {
                _position.x = destination.x;
                _position.z = destination.y;
                _walkQueue.pop();
            }
        }

        if (_walkQueue.empty())
            _walkTimebank = 0.0f;
    }

    void Player::draw()
    {
        Model3::draw();
        if (_isBroadcasting)
            _broadcastSphere.draw();
    }

    bool Player::isClicked()
    {
        return _hasBeenClicked;
    }

    void Player::drawInventory()
    {
        _inventory.draw();
        _levelText.draw();
    }

    int Player::getLevel() const
    {
        return _lvl;
    }

    void Player::setLevel(const int level)
    {
        _lvl = level;
        _levelText.setString("(" + _id + ") Level: " + std::to_string(_lvl));
    }

    std::string Player::getId() const
    {
        return _id;
    }

    void Player::setId(const std::string &id)
    {
        _id = id;
    }

    void Player::setOrientation(const int orientation)
    {
        float angle = getRotation();

        if (orientation >= 1 && orientation <= 4)
            angle = 180 - ((orientation - 1) * 90);
        setRotation(angle);
    }

    std::string Player::getTeamName() const
    {
        return _teamName;
    }

    void Player::setTeamName(const std::string &name)
    {
        _teamName = name;
    }

    void Player::setResourceAmount(ItemType type, int amount)
    {
        _inventory.setAmount(type, amount);
    }

    void Player::collectResource(const ItemType type)
    {
        _inventory.addItem(type);
    }

    void Player::dropResource(const ItemType type)
    {
        _inventory.removeItem(type);
    }

    void Player::setTalkStatus(const bool status)
    {
        _isBroadcasting = status;
    }

    bool Player::isTalking() const
    {
        return _isBroadcasting;
    }

    Sphere &Player::getBroadcastSphere()
    {
        return _broadcastSphere;
    }

    void Player::setServerResponseFlag(bool value)
    {
        _waitingForServerResponse = value;
    }

    bool Player::getServerResponseFlag() const
    {
        return _waitingForServerResponse;
    }

    void Player::addWalkGoal(const Vector2 &goal)
    {
        _walkQueue.push(goal);
    }

    Vector2 Player::getCurrentWalkGoal() const
    {
        return _walkQueue.front();
    }

    void Player::clearWalkGoal()
    {
        while (_walkQueue.size() > 0)
            removeCurrentWalkGoal();
    }

    void Player::removeCurrentWalkGoal()
    {
        if (_walkQueue.size() > 0)
            _walkQueue.pop();
    }

    void Player::setTilePosition(const Vector2 &position)
    {
        _tilePosition = position;
    }

    Vector2 Player::getTilePosition() const
    {
        return _tilePosition;
    }
}
