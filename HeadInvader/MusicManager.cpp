#include "MusicManager.h"
#include <iostream>

bool MusicManager::load(const std::filesystem::path& path) {
    if (!music.openFromFile(path)) {
        std::cerr << "[MusicManager] Failed to load: " << path << "\n";
        return false;
    }
    return true;
}


void MusicManager::play(bool loop) {
     music.setLooping(loop);
     music.play();
}

void MusicManager::stop() {
    music.stop();
}

void MusicManager::setVolume(float volume) {
    music.setVolume(volume);
}

bool MusicManager::isPlaying() const {
    return music.getStatus() == sf::SoundSource::Status::Playing;
}
