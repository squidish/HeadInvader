#pragma once
#include <SFML/Audio.hpp>
#include <string>

class MusicManager {
public:
    //bool load(const std::string& filename);
    bool load (const std::filesystem::path& path);
    void play(bool loop = true);
    void stop();
    void setVolume(float volume);
    bool isPlaying() const;

private:
    sf::Music music;
}; 
