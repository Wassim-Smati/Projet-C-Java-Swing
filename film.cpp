#include "film.h"

Film::~Film(){
    std::cout << "Destruction du film " + this->getName();
}
