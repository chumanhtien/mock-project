#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "./MediaFile.h"
#include <vector>
#include <memory>

class Playlist {
private:
    std::vector<std::weak_ptr<MediaFile>> mediaFiles;
    std::string name;

public:
    void addMediaFile(const std::shared_ptr<MediaFile>& mediaFile);
    uint getMediaFileCount();
    // void addMediaFile(std::shared_ptr<MediaFile> file);
    void showListMediaFiles();
    void deleteMediaFile(uint index);
    const std::vector<std::weak_ptr<MediaFile>>& getMediaFiles() const;
    const std::string& getName();
};
#endif
