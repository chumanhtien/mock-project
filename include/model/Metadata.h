#ifndef METADATA_H
#define METADATA_H
#include <map>
#include <string>
#include <iostream>

class Metadata {
private:
    std::map<std::string, std::string> data;

public:
    Metadata() = default;

    void updateMetadata(const std::string& key, const std::string& value);
    std::string getMetadata(const std::string& key) const;
    void displayAllMetadata() const;
};

#endif
