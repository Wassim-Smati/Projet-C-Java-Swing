#ifndef FILM_H
#define FILM_H
#include "video.h"
#include <vector>
#include <iostream>

class Film : public Video
{
protected:
    Film(){};
    Film(const std::string& name, const std::string& pathfile, const int length, const std::vector<int> chapitres)
        : Video(name, pathfile, length), chapitres(chapitres){}
    friend class MultimediaManager;
private:
    std::vector<int> chapitres{};
public:
    virtual ~Film();
    std::vector<int> getChapitres()const {return chapitres;}
    void setChapitres(std::vector<int> chapitres){this->chapitres=chapitres;}

    void afficher(std::ostream& flux) const override{
        Video::afficher(flux);
        flux << "Durée des chapitres : ";
        for(size_t i=0; i<chapitres.size();i++){
            flux << "Chapitre n°" << i;
            flux << "Durée du chapitre : " << chapitres[i];
        }
    }

};

using FilmPtr = std::shared_ptr<Film>;

#endif // FILM_H
//
