#ifndef VIDEO_H
#define VIDEO_H
#include "multimediaobject.h"
#include <iostream>


#include <string>
class Video : public MultimediaObject
{
protected:
    Video(){};
    Video(const std::string& name, const std::string& pathfile, const int length)
        : MultimediaObject(name, pathfile), length(length) {}
    friend class MultimediaManager;
private:
    int length{};
public:
    virtual ~Video();
    int getLength() const {return length;}
    void setLength(int length) {this->length = length;}

    void afficher(std::ostream& flux) const override{
        MultimediaObject::afficher(flux);
        flux << "Durée : " << length;
    }

    void play() const override;
};

using VideoPtr = std::shared_ptr<Video>;

#endif // VIDEO_H
