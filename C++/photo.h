#ifndef PHOTO_H
#define PHOTO_H
#include "multimediaobject.h"
#include <iostream>

class Photo : public MultimediaObject {
protected:
    Photo() = default;
    Photo(const std::string& name, const std::string& pathfile, double latitude, double longitude)
        : MultimediaObject(name, pathfile), latitude(latitude), longitude(longitude) {}
    friend class MultimediaManager;

    void writeData(std::ostream& out) const override;
    void readData(std::istream& in) override;

private:
    double latitude{};
    double longitude{};

public:
    virtual ~Photo();
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    void setLatitude(double newLatitude) { latitude = newLatitude; }
    void setLongitude(double newLongitude) { longitude = newLongitude; }

    void afficher(std::ostream& flux) const override {
        MultimediaObject::afficher(flux);
        flux << "Latitude : " << latitude << "\n";
        flux << "Longitude : " << longitude << "\n";
    }

    std::string className() const override { return "Photo"; }

    void play() const override;
};

using PhotoPtr = std::shared_ptr<Photo>;

#endif // PHOTO_H
