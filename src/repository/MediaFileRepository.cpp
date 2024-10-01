#include "../../include/const/MediaFileFormats.h"
#include "../../include/repository/MediaFileRepository.h"
#include <algorithm>

namespace fs = std::filesystem;

bool MediaFileRepository::isMediaFile(const fs::path& filePath) {
    std::string extension = filePath.extension().string();

    // Kiểm tra phần mở rộng xem có nằm trong danh sách AUDIO_EXTENSIONS hoặc VIDEO_EXTENSIONS hay không
    return (std::find(AUDIO_EXTENSIONS.begin(), AUDIO_EXTENSIONS.end(), extension) != AUDIO_EXTENSIONS.end()) ||
           (std::find(VIDEO_EXTENSIONS.begin(), VIDEO_EXTENSIONS.end(), extension) != VIDEO_EXTENSIONS.end());
}

std::vector<std::shared_ptr<MediaFile>> MediaFileRepository::scanFolder(const std::string& folderPath) {
    try {
        // Duyệt đệ quy qua thư mục và các thư mục con
        // std::cout << "folder: " << folderPath << "\n";
        for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
            // std::cout << "file: " << entry.path() << ": " << fs::is_regular_file(entry.path()) << " - " << isMediaFile(entry.path()) << "\n";

            if (fs::is_regular_file(entry.path()) && isMediaFile(entry.path())) {
                std::string fileName = entry.path().filename().string();
                std::string filePath = entry.path().string();
                std::string fileType = entry.path().extension().string();

                // Xác định loại tệp dựa trên phần mở rộng
                uint type = (std::find(AUDIO_EXTENSIONS.begin(), AUDIO_EXTENSIONS.end(), fileType) != AUDIO_EXTENSIONS.end()) ? 1 : 0;

                // Thêm tệp media vào danh sách
                allFiles.push_back(std::make_shared<MediaFile>(fileName, filePath, type));
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Lỗi khi truy cập thư mục: " << e.what() << std::endl;
    }

    return allFiles;
}

std::vector<std::shared_ptr<MediaFile>> MediaFileRepository::getMediaFilesByPage(uint page, uint pageSize) {
    uint start = (page - 1) * pageSize;
    uint end = std::min(start + pageSize, (uint) allFiles.size());

    if (start >= allFiles.size()) {
        return {};  // Trả về danh sách rỗng nếu không có trang hợp lệ
    }

    return std::vector<std::shared_ptr<MediaFile>>(allFiles.begin() + start, allFiles.begin() + end);
}

std::vector<std::shared_ptr<MediaFile>> MediaFileRepository::searchMediaFiles(const std::string& searchTerm) {
    std::vector<std::shared_ptr<MediaFile>> result;
    for (const auto& file : allFiles) {
        if (file->getName().find(searchTerm) != std::string::npos) {
            result.push_back(file);
        }
    }
    return result;
}

void MediaFileRepository::updateMetadata(std::shared_ptr<MediaFile> mediaFile, const std::string& key, const std::string& value) {
    mediaFile->getMetadata()->updateMetadata(key, value);
}
