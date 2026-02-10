#include "multimediamanager.h"
#include <sstream>

PhotoPtr MultimediaManager::createPhoto(const std::string& name,const std::string& pathfile, double latitude, double longitude){
    PhotoPtr newPhoto(new Photo(name, pathfile, latitude, longitude));
    mediaMap[name]=newPhoto;
    return newPhoto;
}

VideoPtr MultimediaManager::createVideo(const std::string& name, const std::string& pathfile, const int length){
    VideoPtr newVideo(new Video(name, pathfile, length));
    mediaMap[name]=newVideo;
    return newVideo;
}

FilmPtr MultimediaManager::createFilm(const std::string& name, const std::string& pathfile, const int length, const std::vector<int> chapitres){
    FilmPtr newFilm(new Film(name, pathfile, length, chapitres));
    mediaMap[name]=newFilm;
    return newFilm;
}

GroupePtr MultimediaManager::createGroupe(const std::string& name){
    GroupePtr newGroupe(new Groupe(name));
    groupeMap[name]=newGroupe;
    return newGroupe;
}

void MultimediaManager::afficherMultimedia(const std::string& name,std::ostringstream& flux){
    if (mediaMap.find(name) != mediaMap.end()){
        mediaMap[name]->afficher(flux);
    }
    else{
        return;
    }
}

void MultimediaManager::afficherGroupe(const std::string& name,std::ostringstream& flux){
    if (groupeMap.find(name) != groupeMap.end()){
       groupeMap[name]->afficher(flux);
    }
    else{
        return;
    }
}

void MultimediaManager::playMultimedia(const std::string& name){
    if (mediaMap.find(name) != mediaMap.end()){
        mediaMap[name]->play();
    }
    else{
        return;
    }
}

void MultimediaManager::deleteMultimedia(const std::string& name){
    auto it = mediaMap.find(name);
    if (it == mediaMap.end()) return;
    MultimediaPtr media = it->second;

    for (auto& pair : groupeMap){
        pair.second->remove(media);
    }

    mediaMap.erase(it);
}

void MultimediaManager::deleteGroupe(const std::string& name){
    auto it = groupeMap.find(name);
    if (it == groupeMap.end()) return;

    groupeMap.erase(it);
}
