#include <iostream>
#include "controller/MediaFileController.h"

int main() {
    MediaFileController mediaController;
    std::string folderPath;

    // Automatically prompt for folder path at the beginning
    std::cout << "Enter folder path to scan: ";
    getline(std::cin, folderPath);
    mediaController.scanFolder(folderPath);

    while (true) {
        std::cout << "============================" << std::endl;
        std::cout << "1. View MediaFiles by page" << std::endl;
        std::cout << "2. Search MediaFiles" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                // Xem media files theo trang
                int page;
                std::cout << "Enter page number: ";
                std::cin >> page;
                mediaController.viewMediaFilesByPage(page);
                break;
            }

            case 2: {
                // Tìm kiếm file media
                std::string searchKey;
                std::cout << "Enter search keyword: ";
                std::cin.ignore();
                std::getline(std::cin, searchKey);
                mediaController.viewMediaFilesByPage(1, searchKey);
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
