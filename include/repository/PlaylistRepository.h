#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H
#include <memory>
#include <string>
#include <map>
#include "../model/Playlist.h"

class PlaylistRepository {
private:
    std::map<std::string, std::shared_ptr<Playlist>> listPlaylists;
public:
    void addPlaylist(std::shared_ptr<Playlist> playlist);
    void deletePlaylist(const std::string& name);
    void addMediaFileToPlaylist(const std::string& playlistName, std::shared_ptr<MediaFile> mediaFile);
    void deleteMediaFileFromPlaylist(const std::string& playlistName, uint mediaFileIndex);
    std::map<std::string, std::shared_ptr<Playlist>> getListPlaylists();
};
#endif
