/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** AudioManager.cpp
*/

#include "AudioManager.hpp"
#include "SettingsValue.hpp"

namespace rl
{
    AudioManager::AudioManager()
        : _jukebox({
            {
                    {"MainMenuScene", "Assets/Musics/Minecraft/Beginning_2.mp3"},
                    {"GameScene", "Assets/Musics/Minecraft/Aria_Math.mp3"},
                    {"MainSettingScene", "Assets/Musics/Minecraft/Beginning_2.mp3"},
                    {"SoundSettingScene", "Assets/Musics/Minecraft/Beginning_2.mp3"}
            },
            {
                    {"MainMenuScene", "Assets/Musics/OuterWilds/Main_Title.mp3"},
                    {"GameScene", "Assets/Musics/OuterWilds/Main_Title.mp3"},
                    {"MainSettingScene", "Assets/Musics/OuterWilds/Main_Title.mp3"},
                    {"SoundSettingScene", "Assets/Musics/OuterWilds/Main_Title.mp3"}
            },
            {
                    {"MainMenuScene", "Assets/Musics/Portal/9999999.mp3"},
                    {"GameScene", "Assets/Musics/Portal/TEST.mp3"},
                    {"MainSettingScene", "Assets/Musics/Portal/9999999.mp3"},
                    {"SoundSettingScene", "Assets/Musics/Portal/9999999.mp3"}
            }
        }),
        _jukeboxEntries({
            "minecraft",
            "outer wilds",
            "portal"
        }),
        _jukeboxIndex(0),
        _isJukeboxPlaying(false)
    {
        InitAudioDevice();
        for (auto &game : _jukebox) {
            for (auto &[_, musicFilepath] : game) {
                loadMusic(musicFilepath, musicFilepath);
            }
        }
    }

    AudioManager::~AudioManager()
    {
        CloseAudioDevice();
    }

    AudioManager &AudioManager::getInstance()
    {
        static AudioManager manager;
        return manager;
    }

    size_t AudioManager::getJukeboxIndex() const
    {
        return _jukeboxIndex;
    }

    void AudioManager::setJukeboxIndex(const size_t index, AScene &scene)
    {
        if (index >= _jukebox.size())
            return;
        bool wasPlaying = _isJukeboxPlaying;
        stopJukebox(scene);
        _jukeboxIndex = index;
        if (wasPlaying)
            playJukebox(scene);
    }

    std::string AudioManager::getJukeboxName() const
    {
        return _jukeboxEntries[_jukeboxIndex];
    }

    void AudioManager::setJukeboxName(const std::string &name, AScene &scene)
    {
        auto it = find(_jukeboxEntries.begin(), _jukeboxEntries.end(), name);
        if (it != _jukeboxEntries.end())
            setJukeboxIndex(it - _jukeboxEntries.begin(), scene);
    }

    size_t AudioManager::getJukeboxSize() const
    {
        return _jukeboxEntries.size();
    }

    void AudioManager::playJukebox(AScene &scene)
    {
        if (_isJukeboxPlaying)
            return;
        playMusic(getMusicFromJukebox(scene));
        _isJukeboxPlaying = true;
    }

    void AudioManager::stopJukebox(AScene &scene)
    {
        if (!_isJukeboxPlaying)
            return;
        stopMusic(getMusicFromJukebox(scene));
        _isJukeboxPlaying = false;
    }

    void AudioManager::updateJukebox(AScene &scene)
    {
        SettingsValue &settings = SettingsValue::getInstance();
        std::string id = getMusicFromJukebox(scene);
        if (!_musics.contains(id))
            return;
        setVolumeMusic(id, settings.getJukeboxVolume());
        _musics[id]->update();
    }

    std::string AudioManager::getMusicFromJukebox(AScene &scene)
    {
        const std::string sceneId = scene.getId();
        if (!_jukebox[_jukeboxIndex].contains(sceneId))
            return "";
        const std::string gotId = _jukebox[_jukeboxIndex][sceneId];
        if (!_musics.contains(gotId))
            return "";
        return gotId;
    }

    void AudioManager::loadMusic(const std::string &filename, const std::string &id)
    {
        if (_musics.contains(id))
            return;
        _musics[id] = std::make_shared<MusicSource>(filename);
    }

    void AudioManager::unloadMusic(const std::string &id)
    {
        if (!_musics.contains(id))
            return;
        _musics[id]->close();
        _musics.erase(id);
    }

    void AudioManager::loadSound(const std::string &filename, const std::string &id)
    {
        if (_sounds.contains(id))
            return;
        _sounds[id] = std::make_shared<SoundSource>(filename);
    }

    void AudioManager::unloadSound(const std::string &id)
    {
        if (!_sounds.contains(id))
            return;
        _sounds[id]->close();
        _sounds.erase(id);
    }

    void AudioManager::loadSpeaker(const std::string &filename, const std::string &id, const Vector3 &position)
    {
        if (_speakers.contains(id))
            return;
        _speakers[id] = Speakers{position, std::make_shared<MusicSource>(filename)};
        _speakers[id]._music->setVolume(0.0f);
        _speakers[id]._music->setPan(0.0f);
        _speakers[id]._music->play();
    }

    void AudioManager::unloadSpeaker(const std::string &id)
    {
        if (!_speakers.contains(id))
            return;
        _speakers[id]._music->close();
        _speakers.erase(id);
    }


    void AudioManager::stopAllSounds()
    {
        for (auto &[_, music] : _sounds)
            music->stop();
    }

    void AudioManager::playSound(const std::string &id)
    {
        SettingsValue &settings = SettingsValue::getInstance();
        if (!_sounds.contains(id))
            return;
        setVolumeSound(id, settings.getSoundVolume());
        _sounds[id]->play();
    }

    void AudioManager::stopSound(const std::string &id)
    {
        if (!_sounds.contains(id))
            return;
        _sounds[id]->stop();
    }

    void AudioManager::openSound(const std::string &id)
    {
        if (!_sounds.contains(id))
            return;
        _sounds[id]->open();
    }

    void AudioManager::playMusic(const std::string &id)
    {
        if (!_musics.contains(id))
            return;
        _musics[id]->play();
    }

    void AudioManager::stopMusic(const std::string &id)
    {
        if (!_musics.contains(id))
            return;
        _musics[id]->stop();
    }

    void AudioManager::openMusic(const std::string &id)
    {
        if (!_musics.contains(id))
            return;
        _musics[id]->open();
    }

    void AudioManager::updateMusic(const std::string &id)
    {
        SettingsValue &settings = SettingsValue::getInstance();
        if (!_musics.contains(id))
            return;
        setVolumeMusic(id, settings.getMusicVolume());
        _musics[id]->update();
    }

    void AudioManager::updateSpeakers(const Vector3 &position, const float maxDistance)
    {
        float distance;
        float volume;
        float pan;
        for (auto &[_, speaker] : _speakers) {
            distance = Vector3Distance(position, speaker._position);
            volume = 1.0f - (distance / maxDistance);
            pan = (speaker._position.x - position.x) / maxDistance;
            if (volume < 0.0f)
                volume = 0.0f;
            if (pan > 1.0f)
                pan = 1.0f;
            if (pan < -1.0f)
                pan = -1.0f;
            speaker._music->setVolume(volume);
            speaker._music->setPan(pan);
            speaker._music->update();
        }
    }

    float AudioManager::getVolumeMaster()
    {
        return GetMasterVolume();
    }

    void AudioManager::setVolumeMaster(const float volume)
    {
        SetMasterVolume(volume);
    }

    float AudioManager::getVolumeMusic(const std::string &id)
    {
        if (!_musics.contains(id))
            return -1.0f;
        return _musics[id]->getVolume();
    }

    void AudioManager::setVolumeMusic(const std::string &id, const float volume)
    {
        if (!_musics.contains(id))
            return;
        _musics[id]->setVolume(volume);
    }

    float AudioManager::getVolumeSound(const std::string &id)
    {
        if (!_sounds.contains(id))
            return -1.0f;
        return _sounds[id]->getVolume();
    }

    void AudioManager::setVolumeSound(const std::string &id, const float volume)
    {
        if (!_sounds.contains(id))
            return;
        _sounds[id]->setVolume(volume);
    }

    void AudioManager::setSpeakerPosition(const std::string &id, const Vector3 &position)
    {
        if (!_speakers.contains(id))
            return;
        _speakers[id]._position = position;
    }

    Vector3 AudioManager::getSpeakerPosition(const std::string &id)
    {
        if (!_speakers.contains(id))
            return {};
        return _speakers[id]._position;
    }


    const Sound &AudioManager::getRawSound(const std::string &id)
    {
        if (!_sounds.contains(id)) {
            std::cerr << "RaylibWrapper: AudioManager: couldn't get rawSound [" << id << "]: id not found" << std::endl;
        }
        return _sounds[id]->getSource();
    }

    const Music &AudioManager::getRawMusic(const std::string &id)
    {
        if (!_musics.contains(id)) {
            std::cerr << "RaylibWrapper: AudioManager: couldn't get rawMusic [" << id << "]: id not found" << std::endl;
        }
        return _musics[id]->getSource();
    }
};
