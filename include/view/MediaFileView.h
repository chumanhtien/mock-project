#ifndef MEDIAFILEVIEW_H
#define MEDIAFILEVIEW_H

#include <vector>
#include <memory>
#include "../model/MediaFile.h"
#include "../const/MediaFileFormats.h"

class MediaFileView {
public:
    // Hiển thị danh sách các file media
    void displayMediaFileList(const std::vector<std::shared_ptr<MediaFile>>& mediaFiles);

    // Hiển thị metadata của một file media
    void displayMetadata(const std::shared_ptr<MediaFile>& file);

    // Thông báo khi không có metadata
    void displayNoMetadataMessage();

    void displayPage(const std::vector<std::shared_ptr<MediaFile>>& mediaFiles, uint currentPage, uint itemsPerPage);
    char getUserCommand(); // Nhận lệnh từ người dùng
    
    void printOptions();
    void printManageMetadataOptions();
};

#endif  // MEDIAFILEVIEW_H
