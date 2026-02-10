#ifndef PHOTO_H
#define PHOTO_H
#include "multimediaobject.h"
#include <iostream>

class Photo : public MultimediaObject
{
protected:
    Photo(){};
    Photo(const std::string& name,const std::string& pathfile, double latitude, double longitude)
        :MultimediaObject(name, pathfile), latitude(latitude), longitude(longitude){}
    friend class MultimediaManager;

private:
    double latitude{};
    double longitude{};
public:

    virtual ~Photo();
    double getLatitude() const {return latitude;}
    double getLongitude() const {return longitude;}

    void setLatitude(double latitude) {this->latitude=latitude;}
    void setLongitude(double longitude) {this->longitude=longitude;}

    void afficher(std::ostream& flux) const override{
        MultimediaObject::afficher(flux);
        flux << "latitude : " << latitude;
        flux << "longitude : " << longitude;
    }

    void play() const override;
};

using PhotoPtr = std::shared_ptr<Photo>;

#endif // PHOTO_H
