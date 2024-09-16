/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Sound.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SOUND_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SOUND_HPP
    #include <raylib.h>
    #include <raymath.h>
    #include <rlgl.h>
    #include <iostream>
    #include <vector>
    #include <memory>
    #include <unordered_map>
    #include <functional>
    #include "Vector.hpp"
    #include "AudioSource.hpp"

namespace rl
{
    class SoundSource : public AudioSource {
    public:
        SoundSource();
        SoundSource(const std::string &filepath);
        ~SoundSource();

        bool isReady() override;
        void open() override;
        void close() override;
        void play() override;
        void stop() override;
        void pause() override;
        void resume() override;
        bool isPlaying() override;
        void setVolume(const float volume) override;
        void setPitch(const float pitch) override;
        void setPan(const float pan) override;
        float getVolume() const;
        const Sound &getSource() const;
    private:
        Sound _sound;
        bool _hasSoundOpened;
        std::string _filepath;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SOUND_HPP*/
