//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "multimediamanager.h"

const int PORT = 3331;


int main(int argc, char* argv[])
{
    std::cout << "Serveur lancé ! ";
    MultimediaManager manager;
    PhotoPtr photo = manager.createPhoto("franck", "franck.jpeg", 4, 23);
    VideoPtr video = manager.createVideo("video1", "video.mp4", 23);

    GroupePtr g = manager.createGroupe("Contenu");
    g->push_back(photo);
    g->push_back(video);

    // cree le TCPServer
    auto* server =
    new TCPServer( [&](std::string const& request, std::string& response) {

        std::stringstream ss(request);
        std::string cmd, type, name;

        ss >> cmd >> type >> name;

        if (cmd == "show") {
            std::ostringstream os;

            if (type == "media"){
                manager.afficherMultimedia(name, os);
                response = os.str();
            }
            else if (type == "groupe"){
                manager.afficherGroupe(name, os);
                response = os.str();
            }
            else {
                response = "type inconnu";
            }
        }
        else if (cmd == "play") {
            manager.playMultimedia(name);
            response = "Playing " + name;
        }
        else {
            response = "Commande inconnue";
        }

        // return false would close the connection with the client
        return true;
    });


    // lance la boucle infinie du serveur
    std::cout << "Starting Server on port " << PORT << std::endl;

    int status = server->run(PORT);

    // en cas d'erreur
    if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
    }

    return 0;
}

