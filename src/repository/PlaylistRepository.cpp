#include "../../include/repository/PlaylistRepository.h"

void PlaylistRepository::addPlaylist(std::shared_ptr<Playlist> playlist) {
    std::string playlistName = playlist->getName();
    if (listPlaylists.find(playlistName) != listPlaylists.end()) {
        std::cout << "Playlist: " << playlistName << " already exists.\n";
        return;
    }
    listPlaylists[playlistName] = playlist;
    // std::cout << "Playlist '" << playlistName << "' added successfully.\n";
}

void PlaylistRepository::deletePlaylist(const std::string& name) {
    auto it = listPlaylists.find(name);
    if (it != listPlaylists.end()) {
        listPlaylists.erase(it);
        // std::cout << "Playlist '" << name << "' deleted successfully.\n";
    } else {
        std::cout << "Playlist '" << name << "' not found.\n";
    }
}

void PlaylistRepository::addMediaFileToPlaylist(const std::string& playlistName, std::shared_ptr<MediaFile> mediaFile) {
    auto it = listPlaylists.find(playlistName);
    if (it != listPlaylists.end()) {
        it->second->addMediaFile(mediaFile);
        std::cout << "Media file added to playlist '" << playlistName << "'." << std::endl;
    } else {
        std::cout << "Playlist '" << playlistName << "' not found." << std::endl;
    }
}

void PlaylistRepository::deleteMediaFileFromPlaylist(const std::string& playlistName, uint mediaFileIndex) {
    auto it = listPlaylists.find(playlistName);
    if (it != listPlaylists.end()) {
        try {
            it->second->deleteMediaFile(mediaFileIndex);
            std::cout << "Media file deleted from playlist '" << playlistName << "'." << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "Media file index out of range for playlist '" << playlistName << "'." << std::endl;
        }
    } else {
        std::cout << "Playlist '" << playlistName << "' not found." << std::endl;
    }
}

std::map<std::string, std::shared_ptr<Playlist>> PlaylistRepository::getListPlaylists() {
    return listPlaylists;
}

std::shared_ptr<Playlist> PlaylistRepository::getPlaylist(std::string playlistName) {
    auto it = listPlaylists.find(playlistName); // Tìm playlist theo tên
    if (it != listPlaylists.end()) { // Nếu tìm thấy
        return it->second; // Trả về con trỏ tới Playlist
    }
    return nullptr; // Nếu không tìm thấy, trả về nullptr
}