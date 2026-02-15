#include "multimediaobject.h"
#include <stdexcept>

MultimediaObject::~MultimediaObject()
{
    std::cout << "Mort de l'objet " + this->getName();
}

void MultimediaObject::afficher(std::ostream& flux) const {
    flux << "Nom : " << getName() << "\n";
    flux << "Chemin : " << getPathfile() << "\n";
}

void MultimediaObject::writeData(std::ostream& out) const {
    out << getName() << '\n';
    out << getPathfile() << '\n';
}

void MultimediaObject::readData(std::istream& in) {
    std::string localName;
    std::string localPath;

    if (!std::getline(in, localName) || !std::getline(in, localPath)) {
        throw std::runtime_error("Flux invalide pendant la lecture des attributs de base multimedia");
    }

    setName(localName);
    setPathfile(localPath);
}

void MultimediaObject::serialize(std::ostream& out) const {
    out << className() << '\n';
    writeData(out);
}

void MultimediaObject::deserialize(std::istream& in) { readData(in); }

std::ostream& operator<<(std::ostream& out, const MultimediaObject& object) {
    object.serialize(out);
    return out;
}

std::istream& operator>>(std::istream& in, MultimediaObject& object) {
    object.deserialize(in);
    return in;
}
