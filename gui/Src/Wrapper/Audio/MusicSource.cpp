/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** MusicSource.cpp
*/

#include "MusicSource.hpp"

namespace rl
{
    MusicSource::MusicSource()
        : _hasMusicOpened(false)
    {
        _volume = 1.0f;
    }

    MusicSource::MusicSource(const std::string &filepath)
        : _hasMusicOpened(false), _filepath(filepath)
    {
        _hasMusicOpened = true;
        _music = LoadMusicStream(filepath.c_str());
    }
    
    MusicSource::~MusicSource() {}

    bool MusicSource::isReady()
    {
        return IsMusicReady(_music);
    }

    void MusicSource::open()
    {
        if (_hasMusicOpened)
            return;
        _hasMusicOpened = true;
        _music = LoadMusicStream(_filepath.c_str());
    }

    void MusicSource::close()
    {
        if (!_hasMusicOpened)
            return;
        UnloadMusicStream(_music);
        _hasMusicOpened = false;
    }

    void MusicSource::play()
    {
        PlayMusicStream(_music);
    }

    void MusicSource::stop()
    {
        StopMusicStream(_music);
    }

    void MusicSource::pause()
    {
        PauseMusicStream(_music);
    }

    void MusicSource::resume()
    {
        ResumeMusicStream(_music);
    }

    bool MusicSource::isPlaying()
    {
        return IsMusicStreamPlaying(_music);
    }

    void MusicSource::setVolume(const float volume)
    {
        SetMusicVolume(_music, volume);
    }

    void MusicSource::setPitch(const float pitch)
    {
        SetMusicPitch(_music, pitch);
    }

    void MusicSource::setPan(const float pan)
    {
        SetMusicPan(_music, pan);
    }

    void MusicSource::update()
    {
        UpdateMusicStream(_music);
    }

    void MusicSource::seek(const float position)
    {
        SeekMusicStream(_music, position);
    }

    float MusicSource::getLength() const
    {
        return GetMusicTimeLength(_music);
    }

    float MusicSource::getPlayedLength() const
    {
        return GetMusicTimePlayed(_music);
    }

    float MusicSource::getRemainingLength() const
    {
        return getLength() - getPlayedLength();
    }

    float MusicSource::getVolume() const
    {
        return _volume;
    }

    const Music &MusicSource::getSource() const
    {
        return _music;
    }
};
