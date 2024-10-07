#ifndef MEDIAFILECONTROLLER_H
#define MEDIAFILECONTROLLER_H

#include <string>
#include "../repository/MediaFileRepository.h"
#include "../view/MediaFileView.h"

class MediaFileController {
private:
    MediaFileRepository repository;  // Chỉ sử dụng repository để truy xuất dữ liệu
    MediaFileView view;

public:
    // Quét thư mục để lấy danh sách các file media
    void scanFolder(const std::string& folderPath);

    // Xem danh sách các file media theo trang, có hỗ trợ tìm kiếm
    void viewMediaFilesByPage(int page, const std::string& searchKey = "");

    // Xem metadata của file đã chọn
    void viewMetadata(std::shared_ptr<MediaFile> mediaFile);

    // Cập nhật metadata của file đã chọn
    void updateMetadata(std::shared_ptr<MediaFile> mediaFile, const std::string& key, const std::string& value);

    void displayPage(uint currentPage, uint pageSize);

    void manageMetadata(std::shared_ptr<MediaFile> mediaFile);
    
    void run();

    //getters
    MediaFileRepository& getRepository();
    MediaFileView& getMediaFileView();
};

#endif // MEDIAFILECONTROLLER_H
