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
        if (auto mediaFile = mediaFiles[i]) {
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
        int index = 1;
        for (const auto& pair : playlists) {
            std::cout << index << " - " << pair.first << "\n";
            // displayPlaylist(pair.second);
            index++;
        }
    }

// In các tùy chọn điều khiển
void PlaylistView::printOptions() {
    std::cout << "\nOptions: \n";
    std::cout << "(n) Next Page\n";
    std::cout << "(p) Previous Page\n";
    std::cout << "(q) Quit\n";
    std::cout << "(a) Add media file to playlist\n";
    std::cout << "Enter your command: ";
}

// Nhận lệnh từ người dùng và truyền cho Controller
char PlaylistView::getUserCommand() {
    char command;
    std::cin >> command;
    return command;
}
