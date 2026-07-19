#ifndef MULTIMEDIAMANAGER_H
#define MULTIMEDIAMANAGER_H
#include "film.h"
#include "groupe.h"
#include "photo.h"
#include "video.h"
#include <map>
#include <sstream>
#include <stdexcept>

class MultimediaManager {
private:
    std::map<std::string, MultimediaPtr> mediaMap;
    std::map<std::string, GroupePtr> groupeMap;

    static void validateName(const std::string& name);
    MultimediaPtr createMediaByType(const std::string& typeName) const;

public:
    MultimediaManager() = default;
    ~MultimediaManager() = default;

    PhotoPtr createPhoto(const std::string& name, const std::string& pathfile, double latitude, double longitude);
    VideoPtr createVideo(const std::string& name, const std::string& pathfile, int length);
    FilmPtr createFilm(const std::string& name, const std::string& pathfile, int length, const std::vector<int>& chapitres);
    GroupePtr createGroupe(const std::string& name);

    void afficherMultimedia(const std::string& name, std::ostringstream& flux);
    void afficherGroupe(const std::string& name, std::ostringstream& flux);
    void playMultimedia(const std::string& name);
    void deleteMultimedia(const std::string& name);
    void deleteGroupe(const std::string& name);

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    void saveGroupsToFile(const std::string& filename) const;
    void loadGroupsFromFile(const std::string& filename);
};

#endif // MULTIMEDIAMANAGER_H
