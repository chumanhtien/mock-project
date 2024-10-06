#ifndef MEDIAFILE_REPOSITORY_H
#define MEDIAFILE_REPOSITORY_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include "../model/MediaFile.h"
#include <algorithm>
#include <taglib/tag.h>
#include <taglib/fileref.h>
namespace fs = std::filesystem;

class MediaFileRepository {
private:
    std::vector<std::shared_ptr<MediaFile>> allFiles;

    // Check if the file has a valid audio/video extension
    bool isMediaFile(const fs::path& filePath);

public:
    // Quét thư mục và lấy các media file
    std::vector<std::shared_ptr<MediaFile>> scanFolder(const std::string& folderPath);

    // Phân trang media files
    std::vector<std::shared_ptr<MediaFile>> getMediaFilesByPage(uint page, uint pageSize = 25);

    // Tìm kiếm media files theo tên hoặc metadata
    std::vector<std::shared_ptr<MediaFile>> searchMediaFiles(const std::string& searchTerm);

    // Cập nhật metadata cho media file
    void updateMetadata(std::shared_ptr<MediaFile> mediaFile, const std::string& key, const std::string& value);

    void getAudioMetadata(std::shared_ptr<MediaFile>& mediaFile);


    std::vector<std::shared_ptr<MediaFile>> getAllFiles();

    // void getVideoMetadata(std::shared_ptr<MediaFile>& mediaFile);
};

#endif // MEDIAFILE_REPOSITORY_H
