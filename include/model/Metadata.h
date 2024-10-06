#ifndef METADATA_H
#define METADATA_H
#include <map>
#include <string>
#include <iostream>
#include <taglib/tag.h>
#include <taglib/fileref.h>

class Metadata {
private:
    std::map<std::string, std::string> data;

public:
    Metadata(std::string path);

    void updateMetadata(const std::string& key, const std::string& value);
    std::string getMetadata(const std::string& key) const;
    void displayAllMetadata() const;
};

#endif
