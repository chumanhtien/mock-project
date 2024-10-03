#ifndef MEDIAFILEFORMATS_H
#define MEDIAFILEFORMATS_H

#include <string>
#include <vector>

typedef unsigned int uint;

// Danh sách các định dạng audio
const std::vector<std::string> AUDIO_EXTENSIONS = { ".mp3", ".wav", ".flac" };

// Danh sách các định dạng video
const std::vector<std::string> VIDEO_EXTENSIONS = { ".mp4", ".mkv", ".avi", ".mov" };

const uint ITEMS_PER_PAGE = 25;

#endif
