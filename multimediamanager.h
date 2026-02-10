#ifndef MULTIMEDIAMANAGER_H
#define MULTIMEDIAMANAGER_H
#include "multimediaobject.h"
#include "groupe.h"
#include <map>
#include "photo.h"
#include "film.h"
#include "video.h"

class MultimediaManager
{
private:
    std::map<std::string, MultimediaPtr> mediaMap;
    std::map<std::string, GroupePtr> groupeMap;
public:
    MultimediaManager(){};
    ~MultimediaManager(){};

    PhotoPtr createPhoto(const std::string& name,const std::string& pathfile, double latitude, double longitude);
    VideoPtr createVideo(const std::string& name, const std::string& pathfile, const int length);
    FilmPtr createFilm(const std::string& name, const std::string& pathfile, const int length, const std::vector<int> chapitres);
    GroupePtr createGroupe(const std::string& name);
    void afficherMultimedia(const std::string& name, std::ostringstream& flux);
    void afficherGroupe(const std::string& name, std::ostringstream& flux);
    void playMultimedia(const std::string& name);
    void deleteMultimedia(const std::string& name);
    void deleteGroupe(const std::string& name);
};

#endif // MULTIMEDIAMANAGER_H
