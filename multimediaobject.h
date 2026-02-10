#ifndef MULTIMEDIAOBJECT_H
#define MULTIMEDIAOBJECT_H
#include <string>
#include <iostream>
#include <memory>

class MultimediaObject
{
private:
    std::string name;
    std::string pathfile;
public:
    MultimediaObject(const std::string& name, const std::string& pathfile)
        :name(name), pathfile(pathfile){};

    MultimediaObject(){};

    virtual ~MultimediaObject();

    virtual void afficher(std::ostream& flux) const;
    virtual void play() const=0;

    const std::string& getName() const {return name; }
    const std::string& getPathfile() const {return pathfile;}
    void setName(const std::string& name) {this->name=name;}
    void setPathfile(const std::string& pathfile) {this->pathfile=pathfile;}
};

using MultimediaPtr = std::shared_ptr<MultimediaObject>;

#endif // MULTIMEDIAOBJECT_H
