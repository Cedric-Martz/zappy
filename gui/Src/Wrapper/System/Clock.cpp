/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Time.cpp
*/

#include "Clock.hpp"

namespace rl
{
    Clock::Clock()
        : _currentDeltaTime(0)
    {
        _timeBank.restart();
    }

    Clock::~Clock() {}

    int Clock::getFps() const
    {
        return GetFPS();
    }

    Clock &Clock::getInstance()
    {
        static Clock clock;
        return clock;
    }

    Time Clock::updateDeltaTime()
    {
        long long gotDeltaTime = GetFrameTime() * 1000000;

        _currentDeltaTime = Time(gotDeltaTime);
        return _currentDeltaTime;
    }

    Time Clock::getDeltaTime()
    {
        return _currentDeltaTime;
    }

    Time Clock::updateTimeBank()
    {
        _timeBank += updateDeltaTime();
        return _timeBank;
    }

    Time Clock::getTimeBank() const
    {
        return _timeBank;
    }

    void Clock::setTimeBank(const Time newTimeBank)
    {
        _timeBank = newTimeBank;
    }

    Time Clock::restart()
    {
        Time lastTimeBank = _timeBank;

        _timeBank.restart();
        return lastTimeBank;
    }
};
