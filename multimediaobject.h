#ifndef MULTIMEDIAOBJECT_H
#define MULTIMEDIAOBJECT_H
#include <iostream>
#include <memory>
#include <string>

class MultimediaObject {
private:
    std::string name;
    std::string pathfile;

protected:
    virtual void writeData(std::ostream& out) const;
    virtual void readData(std::istream& in);

public:
    MultimediaObject(const std::string& name, const std::string& pathfile)
        : name(name), pathfile(pathfile) {}

    MultimediaObject() = default;

    virtual ~MultimediaObject();

    virtual void afficher(std::ostream& flux) const;
    virtual void play() const = 0;
    virtual std::string className() const = 0;

    const std::string& getName() const { return name; }
    const std::string& getPathfile() const { return pathfile; }
    void setName(const std::string& newName) { name = newName; }
    void setPathfile(const std::string& newPathfile) { pathfile = newPathfile; }

    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

    friend std::ostream& operator<<(std::ostream& out, const MultimediaObject& object);
    friend std::istream& operator>>(std::istream& in, MultimediaObject& object);
};

using MultimediaPtr = std::shared_ptr<MultimediaObject>;

#endif // MULTIMEDIAOBJECT_H
