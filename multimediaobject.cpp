#include "multimediaobject.h"
#include <string>
#include <iostream>

MultimediaObject::~MultimediaObject()
{
    std::cout << "Mort de l'objet " + this->getName();
}

void MultimediaObject::afficher(std::ostream& flux) const{
    flux << "Nom : " << name << "\n";
    flux << "Chemin :" << pathfile << "\n";
}

