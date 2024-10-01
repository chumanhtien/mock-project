#include "../../include/const/MediaFileFormats.h"
#include "../../include/repository/MediaFileRepository.h"
#include <algorithm>
#include <taglib/tag.h>
#include <taglib/fileref.h>

// #include <libavformat/avformat.h>
// #include <libavcodec/avcodec.h>
// #include <libavutil/avutil.h>
// #include <libavutil/dict.h>

namespace fs = std::filesystem;

bool MediaFileRepository::isMediaFile(const fs::path& filePath) {
    std::string extension = filePath.extension().string();

    // Kiểm tra phần mở rộng xem có nằm trong danh sách AUDIO_EXTENSIONS hoặc VIDEO_EXTENSIONS hay không
    return (std::find(AUDIO_EXTENSIONS.begin(), AUDIO_EXTENSIONS.end(), extension) != AUDIO_EXTENSIONS.end()) ||
           (std::find(VIDEO_EXTENSIONS.begin(), VIDEO_EXTENSIONS.end(), extension) != VIDEO_EXTENSIONS.end());
}

void MediaFileRepository::getAudioMetadata(std::shared_ptr<MediaFile>& mediaFile) {
    TagLib::FileRef f(mediaFile->getPath().c_str());
    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();

        mediaFile->getMetadata()->updateMetadata("Name", tag->title().to8Bit(true));
        mediaFile->getMetadata()->updateMetadata("Size", std::to_string(fs::file_size(mediaFile->getPath())));
        mediaFile->getMetadata()->updateMetadata("Duration", std::to_string(f.audioProperties()->length()));
        mediaFile->getMetadata()->updateMetadata("Bitrate", std::to_string(f.audioProperties()->bitrate()));
        mediaFile->getMetadata()->updateMetadata("Codec", "MP3"); // Điều này có thể phụ thuộc vào file
    }
}

// TODO
// void MediaFileRepository::getVideoMetadata(std::shared_ptr<MediaFile>& mediaFile) {
//     AVFormatContext *formatContext = avformat_alloc_context();
//     if (avformat_open_input(&formatContext, mediaFile->getPath().c_str(), nullptr, nullptr) == 0) {
//         AVDictionary *metadata = formatContext->metadata;
//         AVDictionaryEntry *tag = nullptr;

//         // Lấy các thông tin cần thiết từ metadata
//         while ((tag = av_dict_get(metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
//             std::string key(tag->key);
//             std::string value(tag->value);
//             mediaFile->getMetadata()->updateMetadata(key, value);
//         }

//         avformat_close_input(&formatContext);
//         avformat_free_context(formatContext);
//     }
// }


std::vector<std::shared_ptr<MediaFile>> MediaFileRepository::scanFolder(const std::string& folderPath) {
    try {
        // Duyệt đệ quy qua thư mục và các thư mục con
        for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {

            if (fs::is_regular_file(entry.path()) && isMediaFile(entry.path())) {
                std::string fileName = entry.path().filename().string();
                std::string filePath = entry.path().string();
                std::string fileType = entry.path().extension().string();

                // Xác định loại tệp dựa trên phần mở rộng
                uint type = (std::find(AUDIO_EXTENSIONS.begin(), AUDIO_EXTENSIONS.end(), fileType) != AUDIO_EXTENSIONS.end()) ? 1 : 0;

                // Tạo 1 obj mediafile
                std::shared_ptr<MediaFile> mediaFile = std::make_shared<MediaFile>(fileName, filePath, type);


                if (type == 1) {
                    // get metadata of audio
                    getAudioMetadata(mediaFile);
                } else {
                    // get metadata of video
                    getAudioMetadata(mediaFile);
                    // getVideoMetadata(mediaFile);
                }

                // Thêm tệp media vào danh sách
                allFiles.push_back(mediaFile);
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
