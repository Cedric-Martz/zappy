/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** SoundSetting
*/

#include "SceneManager.hpp"
#include "SoundSetting.hpp"
#include "SettingsValue.hpp"

namespace rl
{
    SoundSetting::SoundSetting()
    {
        Vector2 ws = rl::RenderWindow::getInstance().getSize();
        AudioManager &audio = AudioManager::getInstance();
        float wsx = ws.x;
        float wsy = ws.y;

        addText("SoundSetting", "Sound Settings", 70, GREEN, {0.5f * wsx, 0.0555f * wsy});

        addText("MainVolume", "Main Volume", 30, BLACK, {0.5f * wsx, 0.2f * wsy});

        addText("NotifVolume", "Jukebox Volume", 30, BLACK, {0.5f * wsx, 0.35f * wsy});

        addText("JukeboxSetting", "Sound Volume", 30, BLACK, {0.5f * wsx, 0.5f * wsy});

        addText("MusicVolume", "Music Volume", 30, BLACK, {0.5f * wsx, 0.67f * wsy});

        addButton(
            "quit button",
            Vector2{0.0234f * wsx, 0.0416f * wsy},
            Vector2{0.0468f * wsx, 0.0833f * wsy},
            GREEN,
            [&]() {
                SceneManager::getInstance().setTransitionSpeed(0.1);
                SceneManager::getInstance().popScene();
            },
            "Assets/Imgs/buttons/buttonclose.png",
            "Assets/Imgs/buttons/hoverclose.png"
        );

        addButton(
            "Juke Left",
            Vector2{0.382f * wsx, 0.26f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            WHITE,
            [&]() {
                size_t idx = audio.getJukeboxIndex();
                if (idx == 0)
                    audio.setJukeboxIndex(audio.getJukeboxSize() - 1, *this);
                else
                    audio.setJukeboxIndex(idx - 1, *this);
            },
            "Assets/Imgs/buttons/prev_arrow.png",
            "Assets/Imgs/buttons/prev_arrow.png"
        );

        addButton(
            "Juke Right",
            Vector2{0.617f * wsx, 0.26f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            WHITE,
            [&]() {
                size_t idx = audio.getJukeboxIndex();
                if (idx + 1 == audio.getJukeboxSize())
                    audio.setJukeboxIndex(0, *this);
                else
                    audio.setJukeboxIndex(idx + 1, *this);
            },
            "Assets/Imgs/buttons/next_arrow.png",
            "Assets/Imgs/buttons/next_arrow.png"
        );

        addButton(
            "Jukebox volume UP",
            Vector2{0.617f * wsx, 0.41f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &settings = SettingsValue::getInstance();
                float volume = settings.getJukeboxVolume();
                settings.setJukeboxVolume(volume + 0.1);
            },
            "Assets/Imgs/buttons/up_vol.png",
            "Assets/Imgs/buttons/up_vol.png"
        );

        addButton(
            "Jukebox volume DOWN",
            Vector2{0.382f * wsx, 0.41f * wsy},
            Vector2{0.0321f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &settings = SettingsValue::getInstance();
                float volume = settings.getJukeboxVolume();
                settings.setJukeboxVolume(volume - 0.1);
            },
            "Assets/Imgs/buttons/down_vol.png",
            "Assets/Imgs/buttons/down_vol.png"
        );

        addButton(
            "Sound UP",
            Vector2{0.617f * wsx, 0.56f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &settings = SettingsValue::getInstance();
                float volume = settings.getSoundVolume();
                settings.setSoundVolume(volume + 0.1);
            },
            "Assets/Imgs/buttons/up_vol.png",
            "Assets/Imgs/buttons/up_vol.png"
        );

        addButton(
            "Sound DOWN",
            Vector2{0.382f * wsx, 0.56f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &settings = SettingsValue::getInstance();
                float volume = settings.getSoundVolume();
                settings.setSoundVolume(volume - 0.1);
            },
            "Assets/Imgs/buttons/down_vol.png",
            "Assets/Imgs/buttons/down_vol.png"
        );

        addButton(
            "Music Volume UP",
            Vector2{0.617f * wsx, 0.73f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &settings = SettingsValue::getInstance();
                float volume = settings.getMusicVolume();
                settings.setMusicVolume(volume + 0.1);
            },
            "Assets/Imgs/buttons/up_vol.png",
            "Assets/Imgs/buttons/up_vol.png"
        );

        addButton(
            "Music Volume DOWN",
            Vector2{0.382f * wsx, 0.73f * wsy},
            Vector2{0.0312f * wsx, 0.055f * wsy},
            GRAY,
            [&]() {
                SettingsValue &settings = SettingsValue::getInstance();
                float volume = settings.getMusicVolume();
                settings.setMusicVolume(volume - 0.1);
            },
            "Assets/Imgs/buttons/down_vol.png",
            "Assets/Imgs/buttons/down_vol.png"
        );

        _jukboxRect.setPosition(Vector2{0.421f * wsx, 0.23f * wsy});
        _jukboxRect.setSize(0.156f * wsx, 0.069f * wsy);
        _jukboxRect.setColor(GRAY);

        _jukeboxBar.setPosition(Vector2{0.421f * wsx, 0.38f * wsy});
        _jukeboxBar.setSize(0.156f * wsx, 0.069f * wsy);
        _jukeboxBar.setColor(GRAY);
        _jukeboxProgressBar.setOrigin(Vector2{0, 0});
        _jukeboxProgressBar.setPosition(Vector2{0.421f * wsx, 0.38f * wsy});
        _jukeboxProgressBar.setColor(GREEN);

        _soundBar.setPosition(Vector2{0.421f * wsx, 0.53f * wsy});
        _soundBar.setSize(0.156f * wsx, 0.069f * wsy);
        _soundBar.setColor(GRAY);
        _soundProgressBar.setOrigin(Vector2{0, 0});
        _soundProgressBar.setPosition(Vector2{0.421f * wsx, 0.53f * wsy});
        _soundProgressBar.setColor(GREEN);

        _musicBar.setPosition(Vector2{0.421f * wsx, 0.70f * wsy});
        _musicBar.setSize(0.156f * wsx, 0.069f * wsy);
        _musicBar.setColor(GRAY);
        _musicProgressBar.setOrigin(Vector2{0, 0});
        _musicProgressBar.setPosition(Vector2{0.421f * wsx, 0.70f * wsy});
        _musicProgressBar.setColor(GREEN);

        SettingsValue &settings = SettingsValue::getInstance();
        addText("JukeString", _jukboxString, 30, BLACK, {0.5f * wsx, 0.26f * wsy});
        addText("MainPrint", std::to_string(settings.getJukeboxVolume()), 30, BLACK, {0.5f * wsx, 0.41f * wsy});
        addText("NotifPrint", std::to_string(settings.getSoundVolume()), 30, BLACK, {0.5f * wsx, 0.56f * wsy});
        addText("MusicPrint", std::to_string(settings.getMusicVolume()), 30, BLACK, {0.5f * wsx, 0.73f * wsy});

        _background = std::make_unique<Sprite>(TextureManager::getInstance().loadTexture("Assets/Imgs/font/green_font.png"));
        _background->setTextureRect({0,
                                     0,
                                     static_cast<float>(_background->getTexture().width),
                                     static_cast<float>(_background->getTexture().height)});
        _background->setPosition(Vector2{0.5f * wsx, 0.5f * wsy});
        _background->setScale(Vector2{1.0f, 1.0f});
        _background->setColor(WHITE);
    };

    SoundSetting::~SoundSetting() {};

    std::string SoundSetting::getId() const
    {
        return "SoundSettingScene";
    }

    void SoundSetting::events()
    {
    }

    void SoundSetting::update(double deltaTime)
    {
        Vector2 ws = rl::RenderWindow::getInstance().getSize();
        SettingsValue &settings = SettingsValue::getInstance();
        float wsx = ws.x;
        float wsy = ws.y;

        float jukeboxVolume = settings.getJukeboxVolume();
        float notifVolume = settings.getSoundVolume();
        float musicVolume = settings.getMusicVolume();

        _background->update(deltaTime);

        _jukboxString = AudioManager::getInstance().getJukeboxName();
        _jukeboxProgressBar.setSize((0.156f * wsx) * jukeboxVolume, 0.069f * wsy);
        _soundProgressBar.setSize((0.156f * wsx) * notifVolume, 0.069f * wsy);
        _musicProgressBar.setSize((0.156f * wsx) * musicVolume, 0.069f * wsy);
        std::shared_ptr<Text> _jukbox_val = getElement<Text>("JukeString");
        _jukbox_val->setString(_jukboxString);
        std::shared_ptr<Text> _main_vol = getElement<Text>("MainPrint");
        _main_vol->setString(std::to_string(static_cast<int>(jukeboxVolume * 100)));
        std::shared_ptr<Text> _notif_vol = getElement<Text>("NotifPrint");
        _notif_vol->setString(std::to_string(static_cast<int>(notifVolume * 100)));
        std::shared_ptr<Text> _music_vol = getElement<Text>("MusicPrint");
        _music_vol->setString(std::to_string(static_cast<int>(musicVolume * 100)));
        for (auto &object : _elements)
            object.second->update(deltaTime);
        AudioManager::getInstance().updateJukebox(*this);
    }

    void SoundSetting::render()
    {
        _background->draw();
        _jukboxRect.draw();
        _jukeboxBar.draw();
        _soundBar.draw();
        _musicBar.draw();
        _jukeboxProgressBar.draw();
        _soundProgressBar.draw();
        _musicProgressBar.draw();
        for (auto &object : _elements)
            object.second->draw();
    }
}
