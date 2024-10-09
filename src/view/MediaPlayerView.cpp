#include "../../include/view/MediaPlayerView.h"

    //********************* PLAY MUSIC MENU ***********************/
void MediaPlayerView::showPlayMusic(){
    std::cout<<"\n=================== PLAY MUSIC ===================\n";
    std::cout<<"1. Play all current media files\n";
    std::cout<<"2. Play music from a playlist\n";
    std::cout<<"3. Back\n";
    std::cout<<"====================================================\n";
    std::cout<<"Choose option: ";
}

void MediaPlayerView::showOptionPlayMusic(){
    std::cout<<"\n====================================================\n";
    std::cout<<"1. Start playing music\n";
    std::cout<<"2. Pause\n";
    std::cout<<"3. Resume\n";
    std::cout<<"4. Next Track\n";
    std::cout<<"5. Previous Track\n";
    std::cout<<"6. Change volume\n";
    std::cout<<"7. Stop and exit\n";
    std::cout<<"====================================================\n";
    std::cout<<"Play time: 00:00 / 00:00   ||   Choose option: ";
}

/************************************** OTHER FEATURES *****************************************/
void MediaPlayerView::showErrorInput(){
    std::cout<<"**ERROR: invalid input, check again!!!\n";
}
void MediaPlayerView::clearScreen() {
    std::cout << "\033[2J\033[1;1H";  // escape ANSI to clear screen and point the pointer to initial
}