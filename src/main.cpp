#include <iostream>
#include "controller/MediaFileController.h"

int main() {
    MediaFileController mediaController;
    std::string folderPath;

    while (true) {
        std::cout << "============================" << std::endl;
        std::cout << "1. Scan folder for MediaFiles" << std::endl;
        std::cout << "2. View MediaFiles by page" << std::endl;
        std::cout << "3. Search MediaFiles" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
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
                mediaController.viewMediaFilesByPage(1, searchKey);
                break;
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
