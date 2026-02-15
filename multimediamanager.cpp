#include "multimediamanager.h"
#include <cctype>
#include <fstream>

void MultimediaManager::validateName(const std::string& name) {
    if (name.empty()) {
        throw std::runtime_error("Le nom ne peut pas être vide");
    }

    for (const char c : name) {
        if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-' || c == ' ')) {
            throw std::runtime_error("Nom invalide : caractères interdits");
        }
    }
}

MultimediaPtr MultimediaManager::createMediaByType(const std::string& typeName) const {
    if (typeName == "Photo") {
        return MultimediaPtr(new Photo());
    }
    if (typeName == "Video") {
        return MultimediaPtr(new Video());
    }
    if (typeName == "Film") {
        return MultimediaPtr(new Film());
    }

    throw std::runtime_error("Type multimédia inconnu : " + typeName);
}

PhotoPtr MultimediaManager::createPhoto(const std::string& name, const std::string& pathfile, double latitude, double longitude) {
    validateName(name);
    if (mediaMap.find(name) != mediaMap.end()) {
        throw std::runtime_error("Un objet multimédia avec ce nom existe déjà : " + name);
    }

    PhotoPtr newPhoto(new Photo(name, pathfile, latitude, longitude));
    mediaMap[name] = newPhoto;
    return newPhoto;
}

VideoPtr MultimediaManager::createVideo(const std::string& name, const std::string& pathfile, int length) {
    validateName(name);
    if (length < 0) {
        throw std::runtime_error("La durée d'une vidéo doit être positive ou nulle");
    }
    if (mediaMap.find(name) != mediaMap.end()) {
        throw std::runtime_error("Un objet multimédia avec ce nom existe déjà : " + name);
    }

    VideoPtr newVideo(new Video(name, pathfile, length));
    mediaMap[name] = newVideo;
    return newVideo;
}

FilmPtr MultimediaManager::createFilm(const std::string& name, const std::string& pathfile, int length, const std::vector<int>& chapitres) {
    validateName(name);
    if (length < 0) {
        throw std::runtime_error("La durée d'un film doit être positive ou nulle");
    }
    if (chapitres.empty()) {
        throw std::runtime_error("Un film doit contenir au moins un chapitre");
    }
    for (const int chapitre : chapitres) {
        if (chapitre <= 0) {
            throw std::runtime_error("Toutes les durées de chapitres doivent être strictement positives");
        }
    }
    if (mediaMap.find(name) != mediaMap.end()) {
        throw std::runtime_error("Un objet multimédia avec ce nom existe déjà : " + name);
    }

    FilmPtr newFilm(new Film(name, pathfile, length, chapitres));
    mediaMap[name] = newFilm;
    return newFilm;
}

GroupePtr MultimediaManager::createGroupe(const std::string& name) {
    validateName(name);
    if (groupeMap.find(name) != groupeMap.end()) {
        throw std::runtime_error("Un groupe avec ce nom existe déjà : " + name);
    }

    GroupePtr newGroupe(new Groupe(name));
    groupeMap[name] = newGroupe;
    return newGroupe;
}

void MultimediaManager::afficherMultimedia(const std::string& name, std::ostringstream& flux) {
    auto it = mediaMap.find(name);
    if (it == mediaMap.end()) {
        flux << "Erreur : média introuvable '" << name << "'\n";
        return;
    }
    it->second->afficher(flux);
}

void MultimediaManager::afficherGroupe(const std::string& name, std::ostringstream& flux) {
    auto it = groupeMap.find(name);
    if (it == groupeMap.end()) {
        flux << "Erreur : groupe introuvable '" << name << "'\n";
        return;
    }
    it->second->afficher(flux);
}

void MultimediaManager::playMultimedia(const std::string& name) {
    auto it = mediaMap.find(name);
    if (it == mediaMap.end()) {
        throw std::runtime_error("Impossible de lancer un média inexistant : " + name);
    }
    it->second->play();
}

void MultimediaManager::deleteMultimedia(const std::string& name) {
    auto it = mediaMap.find(name);
    if (it == mediaMap.end()) {
        return;
    }
    MultimediaPtr media = it->second;

    for (auto& pair : groupeMap) {
        pair.second->remove(media);
    }

    mediaMap.erase(it);
}

void MultimediaManager::deleteGroupe(const std::string& name) {
    auto it = groupeMap.find(name);
    if (it == groupeMap.end()) {
        return;
    }

    groupeMap.erase(it);
}

void MultimediaManager::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier en écriture : " + filename);
    }

    out << mediaMap.size() << '\n';
    for (const auto& pair : mediaMap) {
        out << *pair.second;
    }

    out.close();
}

void MultimediaManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier en lecture : " + filename);
    }

    std::string countLine;
    if (!std::getline(in, countLine)) {
        throw std::runtime_error("Fichier de médias invalide : compteur absent");
    }
    const int mediaCount = std::stoi(countLine);
    if (mediaCount < 0) {
        throw std::runtime_error("Fichier de médias invalide : compteur négatif");
    }

    mediaMap.clear();

    for (int i = 0; i < mediaCount; ++i) {
        std::string typeName;
        if (!std::getline(in, typeName)) {
            throw std::runtime_error("Fichier de médias tronqué : type manquant");
        }

        MultimediaPtr media = createMediaByType(typeName);
        in >> *media;

        const std::string key = media->getName();
        if (mediaMap.find(key) != mediaMap.end()) {
            throw std::runtime_error("Doublon détecté pendant le chargement des médias : " + key);
        }
        mediaMap[key] = media;
    }

    in.close();
}

void MultimediaManager::saveGroupsToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier des groupes en écriture : " + filename);
    }

    out << groupeMap.size() << '\n';
    for (const auto& pair : groupeMap) {
        out << pair.first << '\n';
        out << pair.second->size() << '\n';
        for (const auto& media : *pair.second) {
            out << media->getName() << '\n';
        }
    }

    out.close();
}

void MultimediaManager::loadGroupsFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier des groupes en lecture : " + filename);
    }

    std::string countLine;
    if (!std::getline(in, countLine)) {
        throw std::runtime_error("Fichier des groupes invalide : compteur absent");
    }

    const int groupCount = std::stoi(countLine);
    if (groupCount < 0) {
        throw std::runtime_error("Fichier des groupes invalide : compteur négatif");
    }

    groupeMap.clear();

    for (int i = 0; i < groupCount; ++i) {
        std::string groupName;
        if (!std::getline(in, groupName)) {
            throw std::runtime_error("Fichier des groupes tronqué : nom de groupe manquant");
        }
        validateName(groupName);

        std::string memberCountLine;
        if (!std::getline(in, memberCountLine)) {
            throw std::runtime_error("Fichier des groupes tronqué : taille de groupe manquante");
        }

        const int memberCount = std::stoi(memberCountLine);
        if (memberCount < 0) {
            throw std::runtime_error("Fichier des groupes invalide : taille négative");
        }

        GroupePtr group(new Groupe(groupName));
        for (int j = 0; j < memberCount; ++j) {
            std::string mediaName;
            if (!std::getline(in, mediaName)) {
                throw std::runtime_error("Fichier des groupes tronqué : média manquant");
            }

            auto mediaIt = mediaMap.find(mediaName);
            if (mediaIt == mediaMap.end()) {
                throw std::runtime_error("Média référencé par un groupe mais absent : " + mediaName);
            }
            group->push_back(mediaIt->second);
        }

        if (groupeMap.find(groupName) != groupeMap.end()) {
            throw std::runtime_error("Doublon de groupe pendant le chargement : " + groupName);
        }
        groupeMap[groupName] = group;
    }

    in.close();
}
