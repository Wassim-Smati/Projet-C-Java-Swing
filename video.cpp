#include "video.h"

void Video::play() const {
    std::string cmd = "start \"\" \"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\" \"" + this->getPathfile() + "\"";
    system(cmd.c_str());
}

Video::~Video(){
    std::cout << "Destruction de la vidéo " + this->getName();
}
