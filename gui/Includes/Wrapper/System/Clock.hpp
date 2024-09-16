/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Time.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CLOCK_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CLOCK_HPP
    #include "RayLib.hpp"
    #include "Time.hpp"

namespace rl
{
    class Clock {
    public:
        static Clock &getInstance();

        int getFps() const;
        Time updateDeltaTime();
        Time getDeltaTime();
        Time updateTimeBank();
        Time getTimeBank() const;
        void setTimeBank(const Time newTimeBank);

        Time restart();
    private:
        Clock();
        ~Clock();
        Clock(const Clock&) = delete;
        Clock& operator=(const Clock&) = delete;

        Time _timeBank;
        Time _currentDeltaTime;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CLOCK_HPP*/
