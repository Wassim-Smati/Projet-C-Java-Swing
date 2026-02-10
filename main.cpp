//
// main.cpp
// Created on 21/10/2018
//
#include <iostream>
#include <vector>
#include "video.h"
#include <memory>
#include "film.h"
#include "groupe.h"
#include "multimediamanager.h"
using namespace std;

int main(int argc, const char* argv[])
{
    std::cout << "Je suis un nouvel arbre" << std::endl;

    std::string potironPath = "C:\\Users\\Wess9\\Pictures\\potiron.jpg";
    std::string videoPath = "C:\\Users\\Wess9\\Videos\\Captures\\vinted.mp4";

    MultimediaManager manager;

    PhotoPtr media1 = manager.createPhoto("tompere",potironPath, 4, 23);
    VideoPtr media2 = manager.createVideo("tompere2",videoPath, 23);
    FilmPtr media3 = manager.createFilm("tompere3",videoPath, 12, std::vector<int> {2,3,124,45});

    GroupePtr content = manager.createGroupe("Contenu");

    content->push_back(media1);
    content->push_back(media2);
    content->push_back(media3);

    content->afficher(std::cout);
    content->play();

    std::cin.get();
    return 0;
}
