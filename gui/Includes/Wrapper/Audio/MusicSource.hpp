/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** MusicSource.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MUSICSOURCE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MUSICSOURCE_HPP
    #include "RayLib.hpp"
    #include "AudioSource.hpp"

namespace rl
{
    class MusicSource : public AudioSource {
    public:
        MusicSource();
        MusicSource(const std::string &filepath);
        ~MusicSource();

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
        void update();
        void seek(const float position);
        float getLength() const;
        float getPlayedLength() const;
        float getRemainingLength() const;
        float getVolume() const;
        const Music &getSource() const;
    private:
        Music _music;
        bool _hasMusicOpened;
        std::string _filepath;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MUSICSOURCE_HPP*/
