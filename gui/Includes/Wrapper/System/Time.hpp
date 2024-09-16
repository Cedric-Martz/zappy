/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Time.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TIME_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TIME_HPP
    #include <iostream>

namespace rl
{
    class Time {
    public:
        Time(const long long time = 0);
        ~Time();

        void restart();
        long long getTime() const;

        double asSeconds() const;
        int asMilliseconds() const;
        long long asMicroSeconds() const;

        Time &operator+=(const float t);
        Time &operator+=(const Time &t);

    private:
        long long _time;
    };
};

std::ostream &operator<<(std::ostream &s, const rl::Time &time);

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_TIME_HPP*/
