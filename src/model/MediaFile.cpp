
#include "../../include/model/MediaFile.h"
namespace fs = std::filesystem;

MediaFile::MediaFile(const std::string& name, const std::string& path, uint type)
        : name(name), path(path), type(type), metadata(std::make_shared<Metadata>(path)) {
            setupMetadata(type);
        }

void MediaFile::printInfo() {
    std::cout << "Media Name: " << name << std::endl;
    std::cout << "Path: " << path << std::endl;
    std::cout << "Type: " << (type == AUDIO_TYPE ? "Audio" : "Video") << std::endl;
    std::cout << "Metadata: " << std::endl;
    metadata->displayAllMetadata();  
}

std::shared_ptr<Metadata> MediaFile::getMetadata() {
    return metadata;
}

std::string MediaFile::getName() const {
    return name;
}

std::string MediaFile::getType() const {
    return type == 1 ? "audio" : "video";
}

std::string MediaFile::getPath() const {
    return path;
}

void MediaFile::setupMetadata(uint type) {
    if (type == AUDIO_TYPE) {
        TagLib::FileRef f(path.c_str());
    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();

        metadata->updateMetadata("Name", tag->title().to8Bit(true));
        metadata->updateMetadata("Size", std::to_string(fs::file_size(path)));
        metadata->updateMetadata("Duration", std::to_string(f.audioProperties()->length()));
        metadata->updateMetadata("Bitrate", std::to_string(f.audioProperties()->bitrate()));
        metadata->updateMetadata("Codec", "MP3"); // Điều này có thể phụ thuộc vào file
    }
    } else {
        // do for VIDEO
    }
}