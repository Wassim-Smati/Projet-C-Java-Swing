#include "photo.h"
#include <stdexcept>

void Photo::play() const{

    std::string path = this->getPathfile();
    std::string cmd = "mspaint \"" + path + "\"";

    std::cout << "Lancement de : " << cmd << std::endl;
    system(cmd.c_str());
}

Photo::~Photo(){
    std::cout << "Destruction de la photo " + this->getName();
}

void Photo::writeData(std::ostream& out) const {
    MultimediaObject::writeData(out);
    out << latitude << '\n';
    out << longitude << '\n';
}

void Photo::readData(std::istream& in) {
    MultimediaObject::readData(in);

    std::string latLine;
    std::string lonLine;
    if (!std::getline(in, latLine) || !std::getline(in, lonLine)) {
        throw std::runtime_error("Flux invalide pendant la lecture des coordonnées photo");
    }

    setLatitude(std::stod(latLine));
    setLongitude(std::stod(lonLine));
}
