#ifndef MEDIA_FILE_H
#define MEDIA_FILE_H

#include <string>
#include <memory>
#include "./Metadata.h"
#include <filesystem>
#include "../const/MediaFileFormats.h"

typedef unsigned int uint;

class MediaFile {
private:
    std::string name;
    std::string path;
    uint type; // 1: AUDIO 
    
    std::shared_ptr<Metadata> metadata;

public:
    MediaFile(const std::string& name, const std::string& path, uint type);
    void printInfo();
    std::string getName() const;
    std::shared_ptr<Metadata> getMetadata();
    std::string getType() const;
    std::string getPath() const;
    void setupMetadata(uint type = 1);
};

#endif