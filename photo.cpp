#include "photo.h"

void Photo::play() const{

    if (this==nullptr) return;
    std::string path = this->getPathfile();
    std::string cmd = "mspaint \"" + path + "\"";

    std::cout << "Lancement de : " << cmd << std::endl;
    system(cmd.c_str());
}

Photo::~Photo(){
    std::cout << "Destruction de la photo " + this->getName();
}


