# Distributed Multimedia Center

> Serveur multimédia C++ et interface télécommande Java Swing communicant par Sockets TCP.

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Java](https://img.shields.io/badge/Java-Swing-ED8B00?logo=openjdk&logoColor=white)](https://www.oracle.com/java/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

Projet développé dans le cadre du cours **INF224 (Paradigmes de Programmation)** à **Télécom Paris**.

---

## Sommaire

- [Description & Fonctionnalités](#description--fonctionnalités)
- [Architecture Système](#architecture-système)
- [Concepts POO & Design Patterns](#concepts-poo--design-patterns)
- [Structure du Projet](#structure-du-projet)
- [Compilation et Exécution](#compilation-et-exécution)
- [Protocole de Communication](#protocole-de-communication)
- [Auteur](#auteur)

---

## Description & Fonctionnalités

Ce projet est un système distribué composé d'un moteur de gestion multimédia en **C++** et d'une application cliente graphique en **Java Swing**. Les deux parties communiquent à travers un protocole réseau sur Sockets TCP.

### Backend C++
- **Hiérarchie multimédia** : Modélisation des objets `Photo` (avec coordonnées GPS), `Video` (avec durée) et `Film` (avec tableau de chapitres).
- **Gestion de collections** : Regroupement de médias dans la classe `Groupe` sous forme de listes de pointeurs partagés (`std::shared_ptr`), évitant toute duplication de données en mémoire.
- **Gestion mémoire sûre** : Utilisation des pointeurs intelligents pour prévenir les fuites de mémoire.
- **Serveur TCP multithread** : Traitement des commandes à distance (`show`, `play`).
- **Persistance** : Sérialisation et désérialisation du catalogue sur disque avec instanciation dynamique des classes.

### Client Java Swing
- **Interface graphique** : Fenêtre principale avec console d'affichage, zone de saisie, barre d'outils et menus.
- **Télécommande TCP** : Envoi synchrone de requêtes au serveur C++ et affichage des réponses en temps réel.

---

## Architecture Système

```mermaid
graph TD
    subgraph Client ["Client GUI (Java Swing)"]
        UI[MainFrame / Swing UI]
        NetClient[Client Socket TCP]
        UI -->|Commandes| NetClient
    end

    subgraph Network ["Réseau Local"]
        Socket[Socket TCP / Port 3331]
        NetClient <-->|Requêtes / Réponses| Socket
    end

    subgraph Server ["Serveur Backend (C++)"]
        TCPServer[TCPServer / Socket POSIX]
        Manager[MultimediaManager]
        Factory[Factory & Serializer]
        
        Socket <--> TCPServer
        TCPServer -->|Parsing| Manager
        Manager --> Factory
        
        subgraph MediaCore ["Hiérarchie Multimédia"]
            Base[MultimediaObject]
            Photo[Photo]
            Video[Video]
            Film[Film]
            Groupe[Groupe]
            
            Base <|-- Photo
            Base <|-- Video
            Video <|-- Film
            Groupe -->|shared_ptr| Base
        end
        
        Manager --> MediaCore
    end
```

---

## Concepts POO & Design Patterns

| Concept | Application dans le projet |
| :--- | :--- |
| **Encapsulation & Abstraction** | Classe de base abstraite `MultimediaObject` imposant l'interface (`play()`, `className()`). |
| **Pointeurs intelligents** | `std::shared_ptr` pour le partage d'objets entre plusieurs groupes sans duplication. |
| **Pattern Factory** | Instanciation dynamique d'objets à partir du nom de leur classe lors du chargement des fichiers. |
| **Sérialisation polymorphe** | Utilisation de méthodes virtuelles `writeData()` / `readData()` pour la persistance. |
| **Sockets & Client-Serveur** | Découplage complet entre l'IHM et la logique métier backend via Sockets TCP POSIX. |

---

## Structure du Projet

```text
Projet-C-Java-Swing/
├── C++/                          # Moteur multimédia C++
│   ├── main.cpp                  # Scénario de test local
│   ├── server.cpp                # Serveur TCP
│   ├── tcpserver.cpp / .h        # Wrapper de socket serveur TCP multithread
│   ├── ccsocket.cpp / .h         # Wrapper des sockets POSIX/BSD
│   ├── multimediamanager.cpp /.h # Gestionnaire du catalogue et des groupes
│   ├── multimediaobject.cpp /.h  # Classe abstraite de base
│   ├── photo.cpp / .h            # Gestion des photos
│   ├── video.cpp / .h            # Gestion des vidéos
│   ├── film.cpp / .h             # Gestion des films et chapitres
│   ├── groupe.h                  # Classe de regroupement de médias
│   └── Makefile                  # Script de compilation C++
│
└── Java-Swing/                   # Client Télécommande Java
    └── src/
        ├── Main.java             # Point d'entrée de l'application
        ├── MainFrame.java        # Fenêtre principale et interface Swing
        ├── Client.java           # Client Socket TCP Java
        └── Makefile              # Script de compilation et d'exécution
```

---

## Compilation et Exécution

### 1. Démarrer le serveur C++

```bash
cd C++
make clean && make
./server
```

> Le serveur écoute par défaut sur le port **3331**.

---

### 2. Lancer la télécommande Java Swing

```bash
cd Java-Swing/src
make compile
make run
```

---

## Protocole de Communication

Format des échanges textuels sur la socket TCP (port 3331) :

```text
Client  --->  "show media franck"   --->  Serveur
Client  <---  "Photo: franck ..."   <---  Serveur

Client  --->  "show groupe Contenu" --->  Serveur
Client  <---  "Groupe: Contenu ..." <---  Serveur

Client  --->  "play video1"          --->  Serveur
Client  <---  "Playing video1"       <---  Serveur
```

---

## Auteur

**Wassim Smati** — [GitHub](https://github.com/Wassim-Smati)  
Élève-Ingénieur à **Télécom Paris**  
Projet réalisé dans le cadre de l'UE INF224.
