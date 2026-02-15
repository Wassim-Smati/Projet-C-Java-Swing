#include "video.h"
#include <stdexcept>

void Video::play() const {
    std::string cmd = "start \"\" \"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\" \"" + this->getPathfile() + "\"";
    system(cmd.c_str());
}

Video::~Video(){
    std::cout << "Destruction de la vidéo " + this->getName();
}

void Video::writeData(std::ostream& out) const {
    MultimediaObject::writeData(out);
    out << length << '\n';
}

void Video::readData(std::istream& in) {
    MultimediaObject::readData(in);

    std::string line;
    if (!std::getline(in, line)) {
        throw std::runtime_error("Flux invalide pendant la lecture de la durée d'une vidéo");
    }

    const int parsedLength = std::stoi(line);
    if (parsedLength < 0) {
        throw std::runtime_error("La durée d'une vidéo doit être positive ou nulle");
    }
    setLength(parsedLength);
}
