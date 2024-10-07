#include <iostream>
#include <unistd.h>
#include <limits.h>
#include "controller/MediaFileController.h"
#include "controller/PlaylistController.h"
#include "controller/MediaPlayerController.h"

int main() {
    MediaFileController mediaController;
    std::string folderPath;

    // Automatically prompt for folder path at the beginning
    // folderPath = "/home/tiencm/Workspace/fresher_fpt/cpp/test/playlist";
    // // folderPath = "/media/tiencm/66F2-E02C";
    // mediaController.scanFolder(folderPath);
    // Lấy thư mục hiện tại
    char currentPath[PATH_MAX];
    if (getcwd(currentPath, sizeof(currentPath)) != NULL) {
        folderPath = std::string(currentPath);
        std::cout << "Folderpath: " << folderPath;
        mediaController.scanFolder(folderPath);
    } else {
        std::cerr << "Error getting current directory." << std::endl;
        return 1;
    }

    // In ra đường dẫn thư mục hiện tại (chỉ để kiểm tra)
    // std::cout << "Current folder path: " << folderPath << std::endl;

    // set controller for playlist
    PlaylistController playlistController;
    playlistController.setMediaFileController(mediaController);

    MediaPlayerController mediaPlayerController;

    while (true) {
        std::cout << "============================" << std::endl;
        std::cout << "1. Browse media files" << std::endl;
        std::cout << "2. Manage playlist" << std::endl;
        std::cout << "3. Play media files" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                mediaController.run();
                break;
            }

            case 2: {
                // Playlist manager
                playlistController.run();
                break;
            }

            case 3: {
                mediaPlayerController.run(mediaController, playlistController);
            }

            case 4:
                std::cout << "Exiting program." << std::endl;
                return 0;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
    return 0;
}
