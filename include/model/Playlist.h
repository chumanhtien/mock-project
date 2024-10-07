#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "./MediaFile.h"
#include <vector>
#include <memory>

class Playlist {
private:
    std::string name;
    std::vector<std::shared_ptr<MediaFile>> mediaFiles;

public:
    Playlist(const std::string& playlistName, const std::vector<std::shared_ptr<MediaFile>>& mediaFiles = {});

    void addMediaFile(const std::shared_ptr<MediaFile>& mediaFile);
    uint getMediaFileCount();
    // void addMediaFile(std::shared_ptr<MediaFile> file);
    void showListMediaFiles();
    void deleteMediaFile(uint index);
    const std::vector<std::shared_ptr<MediaFile>>& getMediaFiles() const;
    const std::string& getName();
    void setName(const std::string& updateName);
    
    std::vector<std::string> getPathAllFiles();
};
#endif
