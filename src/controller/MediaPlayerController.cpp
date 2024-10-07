#include "../../include/controller/MediaPlayerController.h"

MediaPlayerController* MediaPlayerController::sControllerInstance = nullptr;

MediaPlayerController::MediaPlayerController() 
    : mIsPlaying(false), mTimePaused(0), mVolume(0), mMusic(nullptr) {
    sControllerInstance = this;
}

MediaPlayerController::~MediaPlayerController() {
    if (mMusic) {
        Mix_FreeMusic(mMusic);
        mMusic = nullptr;
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void MediaPlayerController::init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_Mixer initialization error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}

void MediaPlayerController::play(std::shared_ptr<MediaFile> mediaFile) {
    mMusic = Mix_LoadMUS(mediaFile->getPath().c_str());
    if (!mMusic) {
        std::cout << "Music load error: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    if (Mix_PlayMusic(mMusic, 1) == -1) {
        std::cout << "Music play error: " << Mix_GetError() << std::endl;
    } else {
        mStartTime = std::chrono::steady_clock::now();
        mIsPlaying = true;
        mTimePaused = 0;

        // std::shared_ptr<MediaFile> mediaFile = std::make_shared<MediaFile>(filePath);
        mDuration = std::stoi(mediaFile->getMetadata()->getMetadata("Duration"));
        std::cout << "Playing: " << mediaFile->getPath() << std::endl;
    }
}

void MediaPlayerController::pause() {
    if (mIsPlaying) {
        Mix_PauseMusic();
        mIsPlaying = false;
        mTimePaused += std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - mStartTime).count();
        std::cout << "Music paused.\n";
    } else {
        std::cout << "Music is already paused.\n";
    }
}

void MediaPlayerController::resume() {
    if (!mIsPlaying) {
        Mix_ResumeMusic();
        mIsPlaying = true;
        mStartTime = std::chrono::steady_clock::now();
        std::cout << "Music resumed.\n";
    } else {
        std::cout << "Music is already playing.\n";
    }
}

void MediaPlayerController::end() {
    Mix_HookMusicFinished(nullptr);
    mIsPlaying = false;
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
    if (mMusic != nullptr) {
        Mix_FreeMusic(mMusic);
        mMusic = nullptr;
    }
}

void MediaPlayerController::nextTrack() {
    ++mCurrentTrack;
    if (mCurrentTrack == mListToPlay.end()) {
        mCurrentTrack = mListToPlay.begin();
    }
    play(*mCurrentTrack);
}

void MediaPlayerController::previousTrack() {
    if (mCurrentTrack == mListToPlay.begin()) {
        mCurrentTrack = mListToPlay.end();
    }
    --mCurrentTrack;
    play(*mCurrentTrack);
}

void MediaPlayerController::setNonCanonicalMode(bool enable) {
    tcgetattr(STDIN_FILENO, &mTty);

    if (enable) {
        mTty.c_lflag &= ~(ICANON | ECHO);
    } else {
        mTty.c_lflag |= (ICANON | ECHO);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &mTty);
}

void MediaPlayerController::increaseVolume() {
    mVolume += 10;
    // if (mVolume > 128) mVolume = 128;
    Mix_VolumeMusic(mVolume);
}

void MediaPlayerController::decreaseVolume() {
    mVolume -= 10;
    if (mVolume < 0) mVolume = 0;
    Mix_VolumeMusic(mVolume);
}

void MediaPlayerController::musicEndedStatic() {
    if (sControllerInstance) {
        sControllerInstance->musicEnded();
    }
}

void MediaPlayerController::musicEnded() {
    std::cout << "Track finished playing.\n";
    ++mCurrentTrack;
    if (mCurrentTrack == mListToPlay.end()) {
        mCurrentTrack = mListToPlay.begin();
    }
    play(*mCurrentTrack);
}

int MediaPlayerController::getCurrentPlayTime() {
    if (mIsPlaying) {
        auto currentTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - mStartTime);
        return static_cast<int>(duration.count()) + mTimePaused;
    }
    return mTimePaused;
}

std::string MediaPlayerController::formatTime(int seconds) {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, secs);
    return std::string(buffer);
}

void MediaPlayerController::showTimeInRealTime() {
    while (mIsPlaying) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (mIsPlaying) {
            int playTime = getCurrentPlayTime();
            std::cout << "\rCurrent play time: " << formatTime(playTime) << " / " << formatTime(mDuration) << "   ||   Enter your option: " << std::flush;
        }
    }
}

void MediaPlayerController::runPlaylist(std::shared_ptr<Playlist> playlist) {
    init();
    mIsPlaying = false;
    Mix_HookMusicFinished(musicEndedStatic);
    
    mListToPlay = playlist->getMediaFiles();
    mCurrentTrack = mListToPlay.begin();
    
    while (true) {
        setNonCanonicalMode(false);
        uint option;
        view.showOptionPlayMusic();
        std::cin >> option;
        switch (option) {
            case 1: {
                view.clearScreen();
                if (!mIsPlaying) {
                    play(*mCurrentTrack);
                    std::thread playMusic(&MediaPlayerController::showTimeInRealTime, this);
                    playMusic.detach();
                } else {
                    std::cout << "Music is already playing.\n";
                }
                break;
            }
            case 2: {
                view.clearScreen();
                if (mIsPlaying) {
                    pause();
                } else {
                    std::cout << "Music is not playing.\n";
                }
                break;
            }
            case 3: {
                view.clearScreen();
                if (!mIsPlaying) {
                    resume();
                    std::thread playMusic(&MediaPlayerController::showTimeInRealTime, this);
                    playMusic.detach();
                } else {
                    std::cout << "Music is already playing.\n";
                }
                break;
            }
            case 4: {
                view.clearScreen();
                nextTrack();
                std::thread playMusic(&MediaPlayerController::showTimeInRealTime, this);
                playMusic.detach();
                break;
            }
            case 5: {
                view.clearScreen();
                previousTrack();
                std::thread playMusic(&MediaPlayerController::showTimeInRealTime, this);
                playMusic.detach();
                break;
            }
            case 6: {
                view.clearScreen();
                setNonCanonicalMode(true);
                std::cout << "1. Increase volume\n2. Decrease volume\n3. Back\n";
                char volumeOption;
                while(true) {
                    // std::cin.ignore();
                    std::cin >> volumeOption;
                    if (volumeOption == '1') {
                        increaseVolume();
                        // continue;
                    } else if (volumeOption == '2') {
                        decreaseVolume();
                        // continue;
                    }
                    break;
                }
            }
            case 7: {
                end();
                std::cout << "Stopping music...\n";
                return;
            }
            default:
                view.showErrorInput();
                break;
        }
    }
}

void MediaPlayerController::runListMediaFiles(std::vector<std::shared_ptr<MediaFile>> listMediaFiles) {
    mIsPlaying = false;
    init();
    Mix_HookMusicFinished(musicEndedStatic);
    
    for (const auto& file : listMediaFiles) {
        mListToPlay.push_back(file);
    }
    mCurrentTrack = mListToPlay.begin();

    // Run the playlist logic (similar to runPlaylist)
    while (true) {
        setNonCanonicalMode(false);
        uint option;
        view.showOptionPlayMusic();
        std::cin >> option;
        switch (option) {
            case 1: {
                view.clearScreen();
                if (!mIsPlaying) {
                    play(*mCurrentTrack);
                    std::thread playMusic(&MediaPlayerController::showTimeInRealTime, this);
                    playMusic.detach();
                } else {
                    std::cout << "Music is already playing.\n";
                }
                break;
            }
            case 2: {
                view.clearScreen();
                if (mIsPlaying) {
                    pause();
                } else {
                    std::cout << "Music is not playing.\n";
                }
                break;
            }
            case 3: {
                view.clearScreen();
                if (!mIsPlaying) {
                    resume();
                    std::thread playMusic(&MediaPlayerController::showTimeInRealTime, this);
                    playMusic.detach();
                } else {
                    std::cout << "Music is already playing.\n";
                }
                break;
            }
            case 4: {
                view.clearScreen();
                nextTrack();
                std::thread playMusic(&MediaPlayerController::showTimeInRealTime, this);
                playMusic.detach();
                break;
            }
            case 5: {
                view.clearScreen();
                previousTrack();
                std::thread playMusic(&MediaPlayerController::showTimeInRealTime, this);
                playMusic.detach();
                break;
            }
            case 6: {
                view.clearScreen();
                setNonCanonicalMode(true);
                std::cout << "1. Increase volume\n2. Decrease volume\n3. Back\n";
                char volumeOption;
                std::cin >> volumeOption;
                // std::cout << "volumeOption: " << volumeOption << "\n"; 
                if (volumeOption == '1') {
                    increaseVolume();
                } else if (volumeOption == '2') {
                    decreaseVolume();
                }
                break;
            }
            case 7: {
                end();
                std::cout << "Stopping music...\n";
                return;
            }
            default:
                view.showErrorInput();
                break;
        }
    }
}

void MediaPlayerController::run(MediaFileController mediaFileController, PlaylistController playlistController) {
    while(true) {
        view.showPlayMusic();
        uint inputPlayOption;
        std::cin >> inputPlayOption;
        std::cin.ignore();

        switch (inputPlayOption) {
        //case '1': play all current media files
            case 1: {
                view.clearScreen();
                runListMediaFiles(mediaFileController.getRepository().getAllFiles());
                break;
            }
        //case '2': play a specific playlist by its name
            case 2:
            {
                view.clearScreen();
                playlistController.viewPlaylist();
                std::cout<<"Enter EXACTLY the name of playlist that you want to play (or press b to back): ";
                std::string namePlaylist;
                std::getline(std::cin, namePlaylist);
                if (namePlaylist == "b") {
                    view.clearScreen();
                    break;
                }
                if (playlistController.getPlaylist(namePlaylist)) {
                    runPlaylist(playlistController.getPlaylist(namePlaylist));
                } else {
                    std::cout<<"NOT found any playlist name "<<namePlaylist<<std::endl;
                }
                view.clearScreen();
                break;
            }
            case 3:{
                view.clearScreen();
                break;
            }
            default:{
                view.showErrorInput();
                break;
            }
        }
        if (inputPlayOption == 3) {
            break;
        }
    }
}
