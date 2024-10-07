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
    }
}
// PlaylistController::PlaylistController(std::shared_ptr<MediaFileController> mediaController, PlaylistView customView, PlaylistRepository customRepository) :
//     mediaController(mediaController), view(customView), repository(customRepository) {}
void PlaylistController::setMediaFileController(const MediaFileController& mediaFileController) {
    mediaController = mediaFileController;
}

// void getMediaController 
std::shared_ptr<Playlist> PlaylistController::getPlaylist(std::string playlistName) {
    return repository.getPlaylist(playlistName);
}

void PlaylistController::run() {
    uint option;
    while (true) {
        std::cout << "============================ Manage playlist ======================" << std::endl;
        std::cout << "1. Show list playlist" << std::endl;
        std::cout << "2. Show detail playlist" << std::endl;
        std::cout << "3. Create a playlist" << std::endl;
        std::cout << "4. Update a playlist" << std::endl;
        std::cout << "5. Delete a playlist" << std::endl;
        std::cout << "6. Exit" << std::endl;
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
                std::cout << "Enter the name of the playlist: ";
                std::cin.ignore();
                getline(std::cin, playlistName);
                auto playlistFind = getPlaylist(playlistName);
                if (playlistFind) {
                    view.displayPlaylist(playlistFind);
                } else {
                    std::cout << "Playlist '" << playlistName << "' not found.\n";
                }
                break;
            }

            case 3: {
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
                            newPlaylist->addMediaFile(allFiles[index - 1]);
                            std::cout << "Added media file to play list successfully. \n";
                        }
                    } else {
                        std::cout << "Invalid command. Please try again.\n";
                    }
                }
                break;
            }

            case 4: {
                // update a playlist
                std::string playlistName;
                std::cout << "Enter the name of the playlist to update: ";
                std::cin.ignore(); // Để bỏ qua ký tự newline từ lần nhập trước
                getline(std::cin, playlistName);

                auto playlists = repository.getListPlaylists();
                auto it = playlists.find(playlistName);
                
                if (it == playlists.end()) {
                    std::cout << "Playlist '" << playlistName << "' not found." << std::endl;
                    break;
                }

                std::shared_ptr<Playlist> playlistToUpdate = it->second;
                
                while (true) {
                    std::cout << "============================Update Playlist======================" << std::endl;
                    std::cout << "1. Add media file" << std::endl;
                    std::cout << "2. Delete media file" << std::endl;
                    std::cout << "3. Update playlist name" << std::endl;
                    std::cout << "4. Finish updating" << std::endl;
                    std::cout << "Choose an option: ";
                    uint updateOption;
                    std::cin >> updateOption;
                
                    switch (updateOption) {
                        case 1: {
                            // Thêm media file
                            auto allFiles = mediaController.getRepository().getAllFiles();
                            std::cout << "Available media files:\n";
                            for (size_t i = 0; i < allFiles.size(); ++i) {
                                std::cout << i << ": " << allFiles[i]->getName() << std::endl; // Giả sử có phương thức getName()
                            }
                            
                            std::cout << "Choose the index of the media file to add: ";
                            uint index;
                            std::cin >> index;
                            
                            if (index < 0 || index >= allFiles.size()) {
                                std::cout << "Invalid index. Please try again.\n";
                            } else {
                                playlistToUpdate->addMediaFile(allFiles[index - 1]);
                                std::cout << "Media file added successfully.\n";
                            }
                            break;
                        }

                        case 2: {
                            // Xóa media file
                            std::cout << "Current media files in the playlist:\n";
                            playlistToUpdate->showListMediaFiles(); // Giả sử có phương thức này để hiển thị media files

                            std::cout << "Enter the index of the media file to delete: ";
                            uint deleteIndex;
                            std::cin >> deleteIndex;

                            playlistToUpdate->deleteMediaFile(deleteIndex); // Giả sử có phương thức này
                            std::cout << "Media file deleted successfully.\n";
                            break;
                        }
                        case 3: {
                            // update playlist name
                            std::string updateName;
                            std::cout << "Input the new playlist name: "; 
                            std::cin.ignore();
                            std::getline(std::cin, updateName);
                            repository.deletePlaylist(playlistToUpdate->getName());
                            playlistToUpdate->setName(updateName);
                            repository.addPlaylist(playlistToUpdate);
                            std::cout << "Playlist update successfully!\n"; 
                            break;
                        }
                        case 4: {
                            break;
                        }                        
                    }
                    if (updateOption == 3) {
                        break;
                    }
                }
                break;
            }

            case 5: {
                // Delete a playlist
                std::string playlistName;
                std::cout << "Enter the name of the playlist to delete: ";
                std::cin.ignore(); // Bỏ qua ký tự newline còn lại từ lần nhập trước
                getline(std::cin, playlistName);

                // Lấy danh sách playlist hiện tại
                auto playlists = repository.getListPlaylists();
                auto it = playlists.find(playlistName);

                if (it == playlists.end()) {
                    std::cout << "Playlist '" << playlistName << "' not found." << std::endl;
                } else {
                    // Xác nhận trước khi xóa
                    char confirmation;
                    std::cout << "Are you sure you want to delete the playlist '" << playlistName << "'? (y/n): ";
                    std::cin >> confirmation;

                    if (confirmation == 'y' || confirmation == 'Y') {
                        // Xóa playlist
                        deletePlaylist(playlistName);
                        std::cout << "Playlist '" << playlistName << "' has been deleted successfully." << std::endl;
                    } else {
                        std::cout << "Deletion canceled." << std::endl;
                    }
                }
                break;
            }

            case 6: {
                return;
            }
        }
    }
}
