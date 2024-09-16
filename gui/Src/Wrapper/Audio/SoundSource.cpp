/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** SoundSource.cpp
*/

#include "SoundSource.hpp"

namespace rl
{
    SoundSource::SoundSource()
        : _hasSoundOpened(false)
    {
        _volume = 1.0f;
    }

    SoundSource::SoundSource(const std::string &filepath)
        : _hasSoundOpened(false), _filepath(filepath)
    {
        _hasSoundOpened = true;
        _sound = LoadSound(_filepath.c_str());
    }
    
    SoundSource::~SoundSource()
    {
        UnloadSound(_sound);
    }

    bool SoundSource::isReady()
    {
        return IsSoundReady(_sound);
    }

    void SoundSource::open()
    {
        _hasSoundOpened = true;
        _sound = LoadSound(_filepath.c_str());
    }

    void SoundSource::close()
    {
        if (!_hasSoundOpened)
            return;
        UnloadSound(_sound);
        _hasSoundOpened = false;
    }

    void SoundSource::play()
    {
        PlaySound(_sound);
    }

    void SoundSource::stop()
    {
        StopSound(_sound);
    }

    void SoundSource::pause()
    {
        PauseSound(_sound);
    }

    void SoundSource::resume()
    {
        ResumeSound(_sound);
    }

    bool SoundSource::isPlaying()
    {
        return IsSoundPlaying(_sound);
    }

    void SoundSource::setVolume(const float volume)
    {
        SetSoundVolume(_sound, volume);
    }

    void SoundSource::setPitch(const float pitch)
    {
        SetSoundPitch(_sound, pitch);
    }

    void SoundSource::setPan(const float pan)
    {
        SetSoundPan(_sound, pan);
    }

    float SoundSource::getVolume() const
    {
        return _volume;
    }

    const Sound &SoundSource::getSource() const
    {
        return _sound;
    }
};
