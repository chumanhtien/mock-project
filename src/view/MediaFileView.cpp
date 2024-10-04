#include "../../include/view/MediaFileView.h"
#include <iostream>

void MediaFileView::displayMediaFileList(const std::vector<std::shared_ptr<MediaFile>>& mediaFiles) {
    for (const auto& file : mediaFiles) {
        std::cout << "File: " << file->getName() << " (" << file->getType() << ")" << std::endl;
    }
}

void MediaFileView::displayMetadata(const std::shared_ptr<MediaFile>& file) {
    std::cout << "Metadata for file: " << file->getName() << std::endl;
    file->getMetadata()->displayAllMetadata();
}

void MediaFileView::displayNoMetadataMessage() {
    std::cout << "No metadata available for this file.\n";
}

// Hiển thị danh sách media files theo trang

void MediaFileView::displayPage(const std::vector<std::shared_ptr<MediaFile>>& mediaFiles, uint currentPage, uint itemsPerPage) {
    // Tính toán chỉ số bắt đầu và kết thúc
    uint start = currentPage * itemsPerPage;
    uint end = std::min(start + itemsPerPage, (uint) mediaFiles.size());

    // Kiểm tra nếu không có file nào để hiển thị
    if (mediaFiles.empty()) {
        std::cout << "No media files available." << std::endl;
        return;
    }

    std::cout << "\nDisplaying Page " << (currentPage + 1) << " of " << ((mediaFiles.size() + itemsPerPage - 1) / itemsPerPage) << std::endl;

    // In thông tin của các tệp media trong trang hiện tại
    for (size_t i = start; i < end; ++i) {
        std::cout << i + 1 << ". Name: " << mediaFiles[i]->getName() 
                  << " | Path: " << mediaFiles[i]->getPath()
                  << " | Type: " << mediaFiles[i]->getType() 
                  << std::endl;
    }

    // In thông tin phân trang
    std::cout << "Page " << (currentPage + 1) << " of " << ((mediaFiles.size() + itemsPerPage - 1) / itemsPerPage) << std::endl;

    // In các tùy chọn điều khiển
    printOptions();
}

// In các tùy chọn điều khiển
void MediaFileView::printOptions() {
    std::cout << "\nOptions:" << std::endl;
    std::cout << "(n) Next Page" << std::endl;
    std::cout << "(p) Previous Page" << std::endl;
    std::cout << "(q) Quit" << std::endl;
    std::cout << "Enter your command: ";
}

// Nhận lệnh từ người dùng và truyền cho Controller
char MediaFileView::getUserCommand() {
    char command;
    std::cin >> command;
    return command;
}
