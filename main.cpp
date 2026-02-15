//
// main.cpp
// Created on 21/10/2018
//
#include "multimediamanager.h"
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, const char* argv[]) {
    (void)argc;
    (void)argv;

    try {
        MultimediaManager manager;

        const std::string potironPath = "C:\\Users\\Wess9\\Pictures\\potiron.jpg";
        const std::string videoPath = "C:\\Users\\Wess9\\Videos\\Captures\\vinted.mp4";

        PhotoPtr media1 = manager.createPhoto("photo_test", potironPath, 4.0, 23.0);
        VideoPtr media2 = manager.createVideo("video_test", videoPath, 23);
        FilmPtr media3 = manager.createFilm("film_test", videoPath, 120, std::vector<int>{20, 30, 70});

        GroupePtr content = manager.createGroupe("Contenu");
        content->push_back(media1);
        content->push_back(media2);
        content->push_back(media3);

        manager.saveToFile("media_table.txt");
        manager.saveGroupsToFile("group_table.txt");

        MultimediaManager reloadedManager;
        reloadedManager.loadFromFile("media_table.txt");
        reloadedManager.loadGroupsFromFile("group_table.txt");

        std::ostringstream mediaFlux;
        reloadedManager.afficherMultimedia("film_test", mediaFlux);
        std::cout << "Média rechargé :\n" << mediaFlux.str() << std::endl;

        std::ostringstream groupFlux;
        reloadedManager.afficherGroupe("Contenu", groupFlux);
        std::cout << "Groupe rechargé :\n" << groupFlux.str() << std::endl;

        try {
            manager.createFilm("film_invalide", videoPath, 10, std::vector<int>{});
        } catch (const std::exception& e) {
            std::cout << "Erreur chapitres invalides : " << e.what() << std::endl;
        }

        try {
            manager.createPhoto("photo_test", potironPath, 0, 0);
        } catch (const std::exception& e) {
            std::cout << "Erreur doublon de nom : " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erreur fatale : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
