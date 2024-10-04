#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H
#include <memory>
#include "../model/Playlist.h"

class PlaylistView {
public:
    void displayPlaylist(const std::shared_ptr<Playlist>& playlist);
    void displayListPlaylists(const std::map<std::string, std::shared_ptr<Playlist>>& playlists);
};

#endif
