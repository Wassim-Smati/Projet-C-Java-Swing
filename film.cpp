#include "film.h"
#include <stdexcept>

Film::~Film(){
    std::cout << "Destruction du film " + this->getName();
}

void Film::writeData(std::ostream& out) const {
    Video::writeData(out);
    out << chapitres.size() << '\n';
    for (const int chapitre : chapitres) {
        out << chapitre << '\n';
    }
}

void Film::readData(std::istream& in) {
    Video::readData(in);

    std::string countLine;
    if (!std::getline(in, countLine)) {
        throw std::runtime_error("Flux invalide pendant la lecture du nombre de chapitres");
    }

    const int chapterCount = std::stoi(countLine);
    if (chapterCount <= 0) {
        throw std::runtime_error("Un film doit contenir au moins un chapitre");
    }

    std::vector<int> chapters;
    chapters.reserve(static_cast<size_t>(chapterCount));

    for (int i = 0; i < chapterCount; ++i) {
        std::string chapterLine;
        if (!std::getline(in, chapterLine)) {
            throw std::runtime_error("Flux invalide pendant la lecture d'un chapitre");
        }

        const int duration = std::stoi(chapterLine);
        if (duration <= 0) {
            throw std::runtime_error("La durée d'un chapitre doit être strictement positive");
        }
        chapters.push_back(duration);
    }

    setChapitres(chapters);
}
