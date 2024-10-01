#include "../../include/view/MediaFileView.h"
#include <iostream>

void MediaFileView::displayMediaFileList(const std::vector<std::shared_ptr<MediaFile>>& mediaFiles) {
    for (const auto& file : mediaFiles) {
        std::cout << "File: " << file->getName() << " (" << file->getType() << ")" << std::endl;
    }
}

void MediaFileView::displayMetadata(const std::shared_ptr<MediaFile>& file) {
    std::cout << "Metadata for file: " << file->getName() << std::endl;
    file->getMetadata()->displayAllMetadata();
}

void MediaFileView::displayNoMetadataMessage() {
    std::cout << "No metadata available for this file.\n";
}
