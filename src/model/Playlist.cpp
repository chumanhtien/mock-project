#include "../../include/model/Playlist.h"

Playlist::Playlist(const std::string& playlistName, const std::vector<std::shared_ptr<MediaFile>>& mediaFiles) : 
    name(playlistName), mediaFiles(mediaFiles) {}

void Playlist::addMediaFile(const std::shared_ptr<MediaFile>& mediaFile) {
    mediaFiles.push_back(mediaFile);
}

uint Playlist::getMediaFileCount() {
    return (uint) mediaFiles.size();
}

void Playlist::showListMediaFiles() {
    for (uint i = 0; i < mediaFiles.size(); i++) {
        if (auto mediaFile = mediaFiles[i]) {
            // check xem có thể lấy được shared_ptr không
            std::cout << i << ": " << mediaFile->getName() << "\n";
        } else {
            std::cout << i << ": [Expired]" << "\n";
        }
    }
}

void Playlist::deleteMediaFile(uint index) {
    if (index < mediaFiles.size()) {
        mediaFiles.erase(mediaFiles.begin() + index); // xóa media file
    } else {
        std::cerr << "Invalid index: " << index << "\n";
    }
}

const std::vector<std::shared_ptr<MediaFile>>& Playlist::getMediaFiles() const {
    return mediaFiles; // Trả về danh sách media files
}

const std::string& Playlist::getName() {
    return name;
}

std::vector<std::string> Playlist::getPathAllFiles() {
    std::vector<std::string> pathAllFiles;
    pathAllFiles.reserve(mediaFiles.size()); // Dự trữ trước bộ nhớ để tránh cấp phát lại nhiều lần
    for (auto& it : mediaFiles) {
        if (auto media = it) { // Kiểm tra nếu con trỏ yếu vẫn còn giá trị
            pathAllFiles.push_back(media->getPath());
        }
    }
    return pathAllFiles;
}

void Playlist::setName(const std::string& updateName) {
    name = updateName;
}