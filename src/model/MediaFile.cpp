
#include "../../include/model/MediaFile.h"

MediaFile::MediaFile(const std::string& name, const std::string& path, uint type)
        : name(name), path(path), type(type), metadata(std::make_shared<Metadata>()) {}

void MediaFile::printInfo() {
    std::cout << "Media Name: " << name << std::endl;
    std::cout << "Path: " << path << std::endl;
    std::cout << "Type: " << (type == 1 ? "Audio" : "Video") << std::endl;
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