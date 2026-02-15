#ifndef GROUPE_H
#define GROUPE_H
#include "multimediaobject.h"
#include <list>
#include <string>

class Groupe : public std::list<MultimediaPtr> {
protected:
    Groupe() = default;
    explicit Groupe(const std::string& name) : name(name) {}
    friend class MultimediaManager;

private:
    std::string name;

public:
    ~Groupe() = default;
    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    void afficher(std::ostream& flux) const {
        flux << "Affichage de tous les éléments du groupe " << name << "\n";
        for (const auto& media : *this) {
            media->afficher(flux);
        }
    }

    void play() const {
        std::cout << "Lancement des médias du groupe " << name << std::endl;
        for (const auto& media : *this) {
            media->play();
        }
    }
};

using GroupePtr = std::shared_ptr<Groupe>;

#endif // GROUPE_H
