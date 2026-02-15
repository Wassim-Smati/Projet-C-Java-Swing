#ifndef VIDEO_H
#define VIDEO_H
#include "multimediaobject.h"
#include <iostream>
#include <string>

class Video : public MultimediaObject {
protected:
    Video() = default;
    Video(const std::string& name, const std::string& pathfile, int length)
        : MultimediaObject(name, pathfile), length(length) {}
    friend class MultimediaManager;

    void writeData(std::ostream& out) const override;
    void readData(std::istream& in) override;

private:
    int length{};

public:
    virtual ~Video();
    int getLength() const { return length; }
    void setLength(int newLength) { length = newLength; }

    void afficher(std::ostream& flux) const override {
        MultimediaObject::afficher(flux);
        flux << "Durée : " << length << "\n";
    }

    std::string className() const override { return "Video"; }

    void play() const override;
};

using VideoPtr = std::shared_ptr<Video>;

#endif // VIDEO_H
