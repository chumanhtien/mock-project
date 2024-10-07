#include "../../include/model/Metadata.h"

Metadata::Metadata(std::string path) {
    TagLib::FileRef filePath(path.c_str());

    if (!filePath.isNull() && filePath.tag()) {
        //get the inf of media file using TagLib
        TagLib::Tag* tag = filePath.tag();
        data["Title"] = tag->title().toCString(true);
        data["Artist"] = tag->artist().toCString(true);
        data["Year"] = std::to_string(tag->year());
        data["Comment"] = tag->comment().toCString(true);

        TagLib::AudioProperties *properties = filePath.audioProperties();
        data["Duration"] = std::to_string(properties->length());
    }
}

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
