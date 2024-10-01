#ifndef MEDIA_FILE_H
#define MEDIA_FILE_H

#include <string>
#include <memory>
#include "./Metadata.h"
typedef unsigned int uint;

class MediaFile {
private:
    std::string name;
    std::string path;
    uint type;
    
    std::shared_ptr<Metadata> metadata;

public:
    MediaFile(const std::string& name, const std::string& path, uint type);
    void printInfo();
    std::string getName() const;
    std::shared_ptr<Metadata> getMetadata();
    std::string getType() const;
    std::string getPath() const;
};

#endif