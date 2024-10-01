#include "../../include/model/Metadata.h"

void Metadata::updateMetadata(const std::string& key, const std::string& value) {
    data[key] = value;
}

std::string Metadata::getMetadata(const std::string &key) const {
    auto it = data.find(key);
    if(it != data.end()) {
        return it->second;
    }
    return "Not Avaiable";
}

void Metadata::displayAllMetadata() const {
    for(const auto &entry: data) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
}
