#ifndef FILM_H
#define FILM_H
#include "video.h"
#include <iostream>
#include <vector>

class Film : public Video {
protected:
    Film() = default;
    Film(const std::string& name, const std::string& pathfile, int length, const std::vector<int>& chapitres)
        : Video(name, pathfile, length), chapitres(chapitres) {}
    friend class MultimediaManager;

    void writeData(std::ostream& out) const override;
    void readData(std::istream& in) override;

private:
    std::vector<int> chapitres{};

public:
    virtual ~Film();
    std::vector<int> getChapitres() const { return chapitres; }
    void setChapitres(const std::vector<int>& newChapitres) { chapitres = newChapitres; }

    void afficher(std::ostream& flux) const override {
        Video::afficher(flux);
        flux << "Durée des chapitres : ";
        for (size_t i = 0; i < chapitres.size(); i++) {
            flux << "[Chapitre " << i << " : " << chapitres[i] << "] ";
        }
        flux << "\n";
    }

    std::string className() const override { return "Film"; }
};

using FilmPtr = std::shared_ptr<Film>;

#endif // FILM_H
