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
    // Truyền đối tượng MediaFile thay vì Metadata
    view.displayMetadata(mediaFile);
}

void MediaFileController::updateMetadata(std::shared_ptr<MediaFile> mediaFile, const std::string& key, const std::string& value) {
    repository.updateMetadata(mediaFile, key, value);
}
