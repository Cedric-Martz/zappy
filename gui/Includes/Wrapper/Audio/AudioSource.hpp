/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** AudioSource.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_AUDIOSOURCE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_AUDIOSOURCE_HPP

namespace rl
{
    class AudioSource {
    public:
        virtual ~AudioSource();

        virtual bool isReady() = 0;
        virtual void open() = 0;
        virtual void close() = 0;
        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual bool isPlaying() = 0;
        virtual void setVolume(const float volume) = 0;
        virtual void setPitch(const float pitch) = 0;
        virtual void setPan(const float pan) = 0;
    protected:
        AudioSource();
        float _volume;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_AUDIOSOURCE_HPP*/
