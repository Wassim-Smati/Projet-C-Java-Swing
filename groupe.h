#ifndef GROUPE_H
#define GROUPE_H
#include <string>
#include "multimediaobject.h"
#include <list>
class Groupe : public std::list<MultimediaPtr>
{
protected:
    Groupe(){};
    Groupe(const std::string& name) : name(name){}
    friend class MultimediaManager;
private:
    std::string name;
public:
    ~Groupe(){};
    std::string getName() const {return this->name;}
    void setName(std::string name){this->name=name;}

    void afficher(std::ostream& flux) const {
        std::cout << "Affichage de tous les éléments du groupe " + this->name << std::endl;
        for(const auto& media : *this){
            media->afficher(flux);
        }
    }

    void play() const {
        std::cout << "Lancement des médias du groupe " + this->name << std::endl;
        for(const auto& media : *this){
            media->play();
        }
    }

};

using GroupePtr = std::shared_ptr<Groupe>;

#endif // GROUPE_H
