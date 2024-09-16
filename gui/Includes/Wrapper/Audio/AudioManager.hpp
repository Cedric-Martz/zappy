/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** AudioManager.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_AUDIOMANAGER_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_AUDIOMANAGER_HPP
    #include "AScene.hpp"
    #include "SoundSource.hpp"
    #include "MusicSource.hpp"

namespace rl
{
    typedef struct {
        Vector3 _position;
        std::shared_ptr<MusicSource> _music;
    } Speakers;

    class AudioManager {
    public:
        static AudioManager &getInstance();

        size_t getJukeboxIndex() const;
        void setJukeboxIndex(const size_t index, AScene &scene);
        std::string getJukeboxName() const;
        void setJukeboxName(const std::string &name, AScene &scene);
        size_t getJukeboxSize() const;

        void playJukebox(AScene &scene);
        void stopJukebox(AScene &scene);
        void updateJukebox(AScene &scene);

        void loadMusic(const std::string &filename, const std::string &id);
        void unloadMusic(const std::string &id);
        void loadSound(const std::string &filename, const std::string &id);
        void unloadSound(const std::string &id);
        void loadSpeaker(const std::string &filename, const std::string &id, const Vector3 &position);
        void unloadSpeaker(const std::string &id);
        void stopAllSounds();

        void playSound(const std::string &id);
        void stopSound(const std::string &id);
        void openSound(const std::string &id);

        void playMusic(const std::string &id);
        void stopMusic(const std::string &id);
        void openMusic(const std::string &id);
        void updateMusic(const std::string &id);
        void updateSpeakers(const Vector3 &position, const float maxDistance = 2000.0f);

        float getVolumeMaster();
        void setVolumeMaster(const float volume);

        float getVolumeMusic(const std::string &id);
        void setVolumeMusic(const std::string &id, const float volume);

        float getVolumeSound(const std::string &id);
        void setVolumeSound(const std::string &id, const float volume);

        void setSpeakerPosition(const std::string &id, const Vector3 &position);
        Vector3 getSpeakerPosition(const std::string &id);


        const Sound &getRawSound(const std::string &id);
        const Music &getRawMusic(const std::string &id);

    private:
        AudioManager();
        ~AudioManager();
        AudioManager(const AudioManager&) = delete;
        AudioManager& operator=(const AudioManager&) = delete;
        std::string getMusicFromJukebox(AScene &scene);
        std::unordered_map<std::string, std::shared_ptr<SoundSource>> _sounds;
        std::unordered_map<std::string, std::shared_ptr<MusicSource>> _musics;
        std::unordered_map<std::string, Speakers> _speakers;
        std::vector<std::unordered_map<std::string, std::string>> _jukebox;
        std::vector<std::string> _jukeboxEntries;
        size_t _jukeboxIndex;
        bool _isJukeboxPlaying;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_AUDIOMANAGER_HPP*/
