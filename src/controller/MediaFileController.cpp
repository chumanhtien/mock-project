#include "../../include/controller/MediaFileController.h"

void MediaFileController::scanFolder(const std::string& folderPath) {
    repository.scanFolder(folderPath);
}

void MediaFileController::viewMediaFilesByPage(int page, const std::string& searchKey) {
    std::vector<std::shared_ptr<MediaFile>> files;
    if (searchKey.empty()) {
        files = repository.getMediaFilesByPage(page);
    } else {
        files = repository.searchMediaFiles(searchKey);
    }
    // Sử dụng đúng phương thức để hiển thị danh sách
    view.displayMediaFileList(files);
}

void MediaFileController::viewMetadata(std::shared_ptr<MediaFile> mediaFile) {
    // Truyền đối tượshowEditViewMetadatang MediaFile thay vì Metadata
    view.displayMetadata(mediaFile);
}

void MediaFileController::updateMetadata(std::shared_ptr<MediaFile> mediaFile, const std::string& key, const std::string& value) {
    repository.updateMetadata(mediaFile, key, value);
}

void MediaFileController::displayPage(uint currentPage, uint pageSize) {
    // Lấy danh sách media files theo trang
    std::vector<std::shared_ptr<MediaFile>> mediaFiles = repository.getMediaFilesByPage(currentPage, pageSize);
    
    // Tính tổng số trang
    uint totalFiles = repository.getAllFiles().size();
    uint totalPage = (totalFiles + pageSize - 1) / pageSize; // Tính số trang dựa trên tổng số tệp và kích thước trang

    // Hiển thị trang bằng View
    view.displayPage(mediaFiles, currentPage, totalPage);
}

void MediaFileController::run() {
    while (true)
    {
        uint option;
        std::cout << "============================Browse media files======================" << std::endl;
        std::cout << "1. Show list media files" << std::endl;
        std::cout << "2. Search media files" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option)
        {
            case 1:
            {
                /* code */
                std::cout << "LIST MEDIA FILES\n";
                auto allFiles = repository.getAllFiles();
                std::cout << allFiles.size() << "\n";

                uint currentPage = 0;
                uint totalFiles = allFiles.size();
                uint totalPages = (totalFiles + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;

                while (true) {
                    view.displayPage(allFiles, currentPage, ITEMS_PER_PAGE);
                    view.printOptions();

                    char command = view.getUserCommand();
                    if (command == 'n' && currentPage < totalPages - 1) {
                        currentPage++;
                    } else if (command == 'p' && currentPage > 0) {
                        currentPage--;
                    } else if (command == 'q') {
                        break;
                    } else {
                        std::cout << "Invalid command. Please try again.\n";
                    }
                }
                break;
            }
            case 2:
            {
                std::cout << "LIST FOUNDED MEDIA FILES\n";
                std::cout << "Please enter the keyword to search: ";
                std::cin.ignore();
                std::string keySearch;
                getline(std::cin, keySearch);
                auto foundFiles = repository.searchMediaFiles(keySearch);
                uint totalFoundFiles = foundFiles.size();
                uint currentPage = 0;
                uint totalPages = (totalFoundFiles + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;

                if (totalFoundFiles == 0) {
                    std::cout << "No media files found matching the keyword: " << keySearch << std::endl;
                } else {
                    while (true) {
                        view.displayPage(foundFiles, currentPage, ITEMS_PER_PAGE); // Gọi hàm displayPage
                        view.printOptions();

                        char command = view.getUserCommand();
                        if (command == 'n' && currentPage < totalPages - 1) {
                            currentPage++; // Chuyển đến trang tiếp theo
                        } else if (command == 'p' && currentPage > 0) {
                            currentPage--; // Quay lại trang trước
                        } else if (command == 'q') {
                            break; // Thoát khỏi vòng lặp
                        } else {
                            std::cout << "Invalid command. Please try again.\n";
                        }
                    }
                }
                break;
            }
            case 3: 
            {
                std::cout << "case 3 \n";
                // break;
                return;
            }
            default:
                break;
        }
    }
    
}

// getters
MediaFileRepository& MediaFileController::getRepository() {
    return repository;
}

MediaFileView& MediaFileController::getMediaFileView() {
    return view;
}
