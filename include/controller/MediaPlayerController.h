#ifndef MEDIAPLAYER_CONTROLLER_H
#define MEDIAPLAYER_CONTROLLER_H

#include <vector> // Thay vì list
#include <iostream>
#include <string>
#include <filesystem>
#include <memory>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../model/MediaFile.h"
#include "../model/Playlist.h"
#include "../view/MediaPlayerView.h"
#include "./MediaFileController.h"
#include "./PlaylistController.h"

class MediaPlayerController {

    static MediaPlayerController* sControllerInstance;  

private:
    MediaPlayerView view;
    bool mIsPlaying;        // check whether music is playing or not
    Mix_Music* mMusic;
    // handling playing Playlist
    std::vector<std::shared_ptr<MediaFile>>::iterator mCurrentTrack;
    std::vector<std::shared_ptr<MediaFile>> mListToPlay;
    // handling display current time when playing music
    int mTimePaused;
    int mDuration;
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;
    // handling change volume
    int mVolume;
    struct termios mTty;

public:
    MediaPlayerController();
    ~MediaPlayerController();

    // play music
    void init();
    void play(std::shared_ptr<MediaFile> mediaFile);
    void pause();
    void resume();
    void nextTrack();
    void previousTrack();
    void end();

    static void musicEndedStatic();  // used to call non-static function: musicEndedPlaylist()
    void musicEnded();               // handle the event music play finished

    // run playlist or run all media files in current folder
    void runPlaylist(std::shared_ptr<Playlist>);
    void runListMediaFiles(std::vector<std::shared_ptr<MediaFile>>); // Thay đổi từ std::list thành std::vector

    // manage display current time when playing music
    int getCurrentPlayTime();
    std::string formatTime(int);  // format time in mm:ss format
    void showTimeInRealTime();    // show current time playing over total duration of that media file

    // manage change volume
    void setNonCanonicalMode(bool = true);  // turn on/off canonical, echo
    void increaseVolume();
    void decreaseVolume();

    void run(MediaFileController mediaFileController, PlaylistController playlistController);
};

#endif
