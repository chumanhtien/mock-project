#include "../../include/view/PlaylistView.h"

void PlaylistView::displayPlaylist(const std::shared_ptr<Playlist>& playlist) {
    if (playlist == nullptr) {
        std::cout << "Playlist is null.\n";
        return;
    }

    std::cout << "Playlist: " << playlist->getName() << "\n";
    std::cout << "Media files:" << std::endl;

    const auto& mediaFiles = playlist->getMediaFiles();
    if (mediaFiles.empty()) {
        std::cout << "No media files in this playlist.\n";
        return;
    }

    for (size_t i = 0; i < mediaFiles.size(); ++i) {
        if (auto mediaFile = mediaFiles[i].lock()) {
            std::cout << i + 1 << ". " << mediaFile->getName() << " - " << mediaFile->getPath() << "\n";
        } else {
            std::cout << i + 1 << ". [Media file not available]\n";
        }
    }
}

void PlaylistView::displayListPlaylists(const std::map<std::string, std::shared_ptr<Playlist>> & playlists) {
    if (playlists.empty()) {
        std::cout << "No playlists available.\n";
        return;
    }

    std::cout << "Available Playlists:\n";
    for (const auto& pair : playlists) {
        std::cout << "- " << pair.first << "\n";
        displayPlaylist(pair.second);
    }
}
