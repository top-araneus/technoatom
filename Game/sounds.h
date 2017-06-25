#ifndef SOUNDS_H
#define SOUNDS_H

class SoundManager {
public:
  sf::Sound bg_sound_;
  sf::Sound melee_sound_;
  sf::Sound range_sound_;
  sf::Sound restart_sound_;
  sf::Sound kill_sound_;
  SoundManager()
  {
    bg_buf_.loadFromFile("sound/background.ogg");
    melee_buf_.loadFromFile("sound/melee.ogg");
    range_buf_.loadFromFile("sound/range.ogg");
    restart_buf_.loadFromFile("sound/restart.ogg");
    kill_buf_.loadFromFile("sound/kill.ogg");
    bg_sound_.setBuffer(bg_buf_);
    melee_sound_.setBuffer(melee_buf_);
    range_sound_.setBuffer(range_buf_);
    restart_sound_.setBuffer(restart_buf_);
    kill_sound_.setBuffer(kill_buf_);
    melee_sound_.setVolume(30);
    kill_sound_.setVolume(30);
    range_sound_.setVolume(30);
    bg_sound_.setLoop(true);
  }

private:
  sf::SoundBuffer bg_buf_;
  sf::SoundBuffer melee_buf_;
  sf::SoundBuffer range_buf_;
  sf::SoundBuffer restart_buf_;
  sf::SoundBuffer kill_buf_;
};

#endif // SOUNDS_H
