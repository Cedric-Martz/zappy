/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Time.cpp
*/

#include "Time.hpp"

namespace rl
{
    Time::Time(const long long time)
        : _time(time)
    {}

    Time::~Time() {}

    void Time::restart()
    {
        _time = 0;
    }

    long long Time::getTime() const
    {
        return _time;
    }

    double Time::asSeconds() const
    {
        return static_cast<double>(_time) / 1000000.0f;
    }

    int Time::asMilliseconds() const
    {
        return static_cast<int>(static_cast<double>(_time) / 1000.0f);
    }

    long long Time::asMicroSeconds() const
    {
        return _time;
    }

    Time &Time::operator+=(const float t)
    {
        _time += t;
        return *this;
    }

    Time &Time::operator+=(const Time &t)
    {
        _time += t._time;
        return *this;
    }
};

std::ostream &operator<<(std::ostream &s, const rl::Time &time)
{
    return s << time.getTime();
}
