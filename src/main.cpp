#include <iostream>
#include "controller/MediaFileController.h"

int main() {
    MediaFileController mediaController;
    std::string folderPath;

<<<<<<< HEAD
    // Automatically prompt for folder path at the beginning
    // std::cout << "Enter folder path to scan: ";
    // getline(std::cin, folderPath);
    folderPath = "/home/tiencm/Workspace/fresher_fpt/cpp/test/playlist";
    mediaController.scanFolder(folderPath);

    while (true) {
        std::cout << "============================" << std::endl;
        std::cout << "1. Browse media files" << std::endl;
        std::cout << "2. Manage playlist" << std::endl;
        std::cout << "3. Exit" << std::endl;
=======
    while (true) {
        std::cout << "============================" << std::endl;
        std::cout << "1. Scan folder for MediaFiles" << std::endl;
        std::cout << "2. View MediaFiles by page" << std::endl;
        std::cout << "3. Search MediaFiles" << std::endl;
        std::cout << "4. Exit" << std::endl;
>>>>>>> main
        std::cout << "============================" << std::endl;
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
<<<<<<< HEAD
            case 1: {
                // Xem media files theo trang
                // int page;
                // std::cout << "Enter page number: ";
                // std::cin >> page;
                mediaController.run();
                break;
            }

            case 2: {
                // Tìm kiếm file media
                std::string searchKey;
                std::cout << "Enter search keyword: ";
                std::cin.ignore();
                std::getline(std::cin, searchKey);
=======
            case 1:
                // Chức năng quét thư mục
                std::cout << "Enter folder path to scan: ";
                getline(std::cin, folderPath);

                mediaController.scanFolder(folderPath);
                break;

            case 2: {
                // Xem media files theo trang
                int page;
                std::cout << "Enter page number: ";
                std::cin >> page;
                mediaController.viewMediaFilesByPage(page);
                break;
            }

            case 3: {
                // Tìm kiếm file media
                std::string searchKey;
                std::cout << "Enter search keyword: ";
                std::cin >> searchKey;
>>>>>>> main
                mediaController.viewMediaFilesByPage(1, searchKey);
                break;
            }

<<<<<<< HEAD
            case 3:
=======
            case 4:
>>>>>>> main
                std::cout << "Exiting program." << std::endl;
                return 0;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
<<<<<<< HEAD

=======
>>>>>>> main
    return 0;
}
