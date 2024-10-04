#include "../../include/controller/PlaylistController.h"
// void run();
// void addPlaylist(std::shared_ptr<Playlist> playlist);
// void deletePlaylist(const std::string& playlistName);
// void addMediaFileToPlaylist(const std::string& playlistName, std::shared_ptr<MediaFile> mediaFile);
// void deleteMediaFileFromPlaylist(const std::string& playlistName, uint mediaFileIndex);
// void viewPlaylist();

void PlaylistController::addPlaylist(std::shared_ptr<Playlist> playlist) {
    repository.addPlaylist(playlist);
}

void PlaylistController::deletePlaylist(const std::string& playlistName) {
    repository.deletePlaylist(playlistName);
}

void PlaylistController::addMediaFileToPlaylist(const std::string& playlistName, std::shared_ptr<MediaFile> mediaFile) {
    repository.addMediaFileToPlaylist(playlistName, mediaFile);
}

void PlaylistController::deleteMediaFileFromPlaylist(const std::string& playlistName, uint mediaFileIndex) {
    repository.deleteMediaFileFromPlaylist(playlistName, mediaFileIndex);
}

void PlaylistController::viewPlaylist() {
    std::map<std::string, std::shared_ptr<Playlist>> playlists = repository.getListPlaylists();
    if (playlists.empty()) {
        std::cout << "No playlists to display." << std::endl;
    } else {
        view.displayListPlaylists(playlists);
        
        // Optionally display specific playlist
        std::string playlistName;
        std::cout << "Enter the name of the playlist to view details: ";
        std::cin >> playlistName;
        auto it = playlists.find(playlistName);
        if (it != playlists.end()) {
            view.displayPlaylist(it->second);
        } else {
            std::cout << "Playlist '" << playlistName << "' not found." << std::endl;
        }
    }
}
// PlaylistController::PlaylistController(std::shared_ptr<MediaFileController> mediaController, PlaylistView customView, PlaylistRepository customRepository) :
//     mediaController(mediaController), view(customView), repository(customRepository) {}
void PlaylistController::setMediaFileController(const MediaFileController& mediaFileController) {
    mediaController = mediaFileController;
}

// void getMediaController 

void PlaylistController::run() {
    uint option;
    while (true) {
        std::cout << "============================Browse media files======================" << std::endl;
        std::cout << "1. Show list playlist" << std::endl;
        std::cout << "2. Create a playlist" << std::endl;
        std::cout << "3. Update a playlist" << std::endl;
        std::cout << "4. Delete a playlist" << std::endl;
        std::cout << "5. Play a playlist" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option) {
            case 1: {
                viewPlaylist();
                break;
            }
    
            case 2: {
                std::string playlistName;
                std::cout << "Enter the name of the new playlist: ";
                std::cin.ignore();
                getline(std::cin, playlistName);
                std::cout << "List media files to add:\n";
                std::shared_ptr<Playlist> newPlaylist = std::make_shared<Playlist>(playlistName);

                // mediaController->displayPage()
                auto allFiles = mediaController.getRepository().getAllFiles();
                uint currentPage = 0;
                uint totalFiles = allFiles.size();
                uint totalPages = (totalFiles + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
                auto mediaFileView = mediaController.getMediaFileView();

                while (true) {
                    mediaFileView.displayPage(allFiles, currentPage, ITEMS_PER_PAGE);
                    view.printOptions();

                    char command = view.getUserCommand();
                    if (command == 'n' && currentPage < totalPages - 1) {
                        currentPage++;
                    } else if (command == 'p' && currentPage > 0) {
                        currentPage--;
                    } else if (command == 'q') {
                        addPlaylist(newPlaylist);
                        break;
                    } else if (command == 'a') {
                        std::cout << "Choose index of media files to add to your playlist: ";
                        uint index;
                        std::cin >> index;
                        if (index < 0 || index >= totalFiles) {
                            std::cout << "Invalid index. Please try again. \n";
                        } else {
                            newPlaylist->addMediaFile(allFiles[index]);
                            std::cout << "Added media file to play list successfully. \n";
                        }
                    } else {
                        std::cout << "Invalid command. Please try again.\n";
                    }
                }
                break;
            }

        }
    }
}