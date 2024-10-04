#include <iostream>
#include "controller/MediaFileController.h"
#include "controller/PlaylistController.h"

int main() {
    MediaFileController mediaController;
    std::string folderPath;

    // Automatically prompt for folder path at the beginning
    // std::cout << "Enter folder path to scan: ";
    // getline(std::cin, folderPath);
    folderPath = "/home/tiencm/Workspace/fresher_fpt/cpp/test/playlist";
    mediaController.scanFolder(folderPath);

    // set controller for playlist
    PlaylistController playlistController;
    playlistController.setMediaFileController(mediaController);


    while (true) {
        std::cout << "============================" << std::endl;
        std::cout << "1. Browse media files" << std::endl;
        std::cout << "2. Manage playlist" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                // Xem media files theo trang
                // int page;
                // std::cout << "Enter page number: ";
                // std::cin >> page;
                mediaController.run();
                break;
            }

            case 2: {
                // Playlist manager
                playlistController.run();
                break;
            }

            case 3:
                std::cout << "Exiting program." << std::endl;
                return 0;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
    return 0;
}
