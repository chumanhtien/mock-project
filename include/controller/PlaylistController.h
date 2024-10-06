#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H
#include "../model/Playlist.h"
#include "./MediaFileController.h"
#include "../view/PlaylistView.h"
#include "../repository/PlaylistRepository.h"

class PlaylistController {
private:
    MediaFileController mediaController;
    PlaylistView view;
    PlaylistRepository repository;

public:
    // PlaylistController(std::shared_ptr<MediaFileController> mediaController, PlaylistView view, PlaylistRepository repository);

    void run();
    void addPlaylist(std::shared_ptr<Playlist> playlist);
    void deletePlaylist(const std::string& playlistName);
    void addMediaFileToPlaylist(const std::string& playlistName, std::shared_ptr<MediaFile> mediaFile);
    void deleteMediaFileFromPlaylist(const std::string& playlistName, uint mediaFileIndex);
    void viewPlaylist();
    void setMediaFileController(const MediaFileController& mediaFileController);
    std::shared_ptr<Playlist> getPlaylist(std::string playlistName);
};
#endif
