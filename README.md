<div align="center">

  # 🎬 Distributed Multimedia Center
  ### C++ Engine & Java Swing Remote Controller

  [![Language - C++17](https://img.shields.io/badge/C%2B%2B-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
  [![Language - Java](https://img.shields.io/badge/Java-17%2B-ED8B00?style=for-the-badge&logo=openjdk&logoColor=white)](https://www.oracle.com/java/)
  [![GUI - Swing](https://img.shields.io/badge/GUI-Java%20Swing-5382A1?style=for-the-badge&logo=java&logoColor=white)](https://docs.oracle.com/javase/tutorial/uiswing/)
  [![Protocol - TCP/IP](https://img.shields.io/badge/Network-TCP%2FIP%20Sockets-4682B4?style=for-the-badge&logo=target&logoColor=white)]()
  [![Build - Make](https://img.shields.io/badge/Build-Makefile-064F8C?style=for-the-badge&logo=gnu&logoColor=white)]()
  [![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](LICENSE)

  <p align="center">
    <b>Un système distribué orienté objet complet comprenant un moteur de gestion multimédia hautement performant en C++ et une télécommande graphique en Java Swing communiquant via Sockets TCP.</b>
  </p>

  <sub>Projet développé dans le cadre du cours <b>INF224 (Paradigmes de Programmation)</b> à <b>Télécom Paris</b>.</sub>

</div>

---

## 📋 Sommaire

- [✨ Aperçu & Fonctionnalités](#-aperçu--fonctionnalités)
- [📐 Architecture Système](#-architecture-système)
- [🎯 Design Patterns & Concepts POO](#-design-patterns--concepts-poo)
- [📁 Structure du Projet](#-structure-du-projet)
- [🚀 Guide de Démarrage](#-guide-de-démarrage)
- [💬 Protocole de Communication](#-protocole-de-communication)
- [👤 Auteur](#-auteur)

---

## ✨ Aperçu & Fonctionnalités

Ce projet combine la puissance de **C++** pour le traitement système et la gestion mémoire avec la flexibilité de **Java Swing** pour la création d'interfaces graphiques utilisateur.

### ⚙️ Serveur C++ (Backend Multimédia)
- 🖼️ **Polymorphisme Multimédia** : Gestion unifiée de `Photo` (géolocalisation), `Video` (durée), et `Film` (gestion de chapitres avec durées).
- 👥 **Groupes & Collections** : Organisation en groupes dynamiques avec **références non-dupliquées** (pas de duplication en mémoire).
- 🧠 **Gestion Mémoire Intelligente** : Utilisation de smart pointers (`std::shared_ptr`, `std::intrusive_ptr`) garantissant zéro fuite mémoire.
- ⚡ **Serveur Sockets TCP Multithread** : Traitement simultané de requêtes réseau pour la recherche, l'affichage et la lecture à distance.
- 💾 **Persistance des Données** : Sérialisation et désérialisation personnalisées avec fabrique dynamique d'objets (Factory Pattern).

### 🖥️ Client Java Swing (IHM Télécommande)
- 🎨 **Interface Moderne & Intuitive** : Zone de console avec scroll automatique, barre d'outils (ToolBar) et menu contextuel.
- 📡 **Client TCP Synchrone** : Communication réseau transparente via Sockets Java avec gestion d'erreurs en cas de déconnexion.
- 🕹️ **Contrôle à Distance** : Envoi de commandes pour rechercher des médias/groupes ou lancer la lecture multimédia sur le serveur.

---

## 📐 Architecture Système

```mermaid
graph TD
    subgraph Client ["Client GUI (Java Swing)"]
        UI[MainFrame / Swing UI]
        NetClient[Client Socket TCP]
        UI -->|Saisie utilisateur| NetClient
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
        TCPServer -->|Parse commandes| Manager
        Manager --> Factory
        
        subgraph MediaCore ["Hiérarchie Multimédia POO"]
            Base[MultimediaObject]
            Photo[Photo]
            Video[Video]
            Film[Film]
            Groupe[Groupe / List]
            
            Base <|-- Photo
            Base <|-- Video
            Video <|-- Film
            Groupe -->|shared_ptr| Base
        end
        
        Manager --> MediaCore
    end
```

---

## 🎯 Design Patterns & Concepts POO

Ce projet met en œuvre les meilleures pratiques d'ingénierie logicielle et de programmation orientée objet :

| Concept | Implémentation dans le Projet |
| :--- | :--- |
| **Encapsulation & Abstraction** | Classe de base abstraite `MultimediaObject` avec méthodes virtuelles pures (`play()`, `className()`). |
| **Gestion Mémoire (Smart Pointers)** | Utilisation systématique de `std::shared_ptr` et alias de types (`MultimediaPtr`, `GroupePtr`, `PhotoPtr`). |
| **Pattern Fabrique (Factory)** | Reconstitution dynamique du type concret lors de la désérialisation via `createMediaByType()`. |
| **Sérialisation Polymorphique** | Méthodes virtuelles `writeData()` / `readData()` surchargeant le comportement I/O selon le type de média. |
| **Architecture Client-Serveur TCP** | Séparation claire des responsabilités entre le moteur C++ (I/O, logique) et le client Java (IHM). |
| **Robustesse & Robust Error Handling** | Levée d'exceptions `std::runtime_error`, validation des paramètres et protection contre les doublons. |

---

## 📁 Structure du Projet

```text
Projet-C-Java-Swing/
├── C++/                          # Moteur Backend C++
│   ├── main.cpp                  # Scénario de test & démonstration POO
│   ├── server.cpp                # Point d'entrée du Serveur TCP
│   ├── tcpserver.cpp / .h        # Wrapper de serveur Socket TCP multithreadé
│   ├── ccsocket.cpp / .h         # Encapsulation des sockets POSIX/BSD
│   ├── multimediamanager.cpp /.h # Gestionnaire de catalogue et groupes
│   ├── multimediaobject.cpp /.h  # Classe de base abstraite multimédia
│   ├── photo.cpp / .h            # Classe Photo (latitude, longitude)
│   ├── video.cpp / .h            # Classe Video (durée)
│   ├── film.cpp / .h             # Classe Film (tableau de chapitres)
│   ├── groupe.h                  # Collection de médias (std::list<MultimediaPtr>)
│   └── Makefile                  # Script de compilation C++
│
└── Java-Swing/                   # Client Télécommande Java
    └── src/
        ├── Main.java             # Lancement de l'application Swing
        ├── MainFrame.java        # Fenêtre principale et composants Swing
        ├── Client.java           # Gestionnaire de connexion Socket Java
        └── Makefile              # Script de compilation & exécution Java
```

---

## 🚀 Guide de Démarrage

### Prérequis
- **C++** : Compilateur compatible C++17 (`g++` ou `clang++`) et `make`.
- **Java** : JDK 17 ou supérieur (`javac`, `java`).

---

### 1️⃣ Lancer le Serveur C++

Dans un premier terminal, compilez et démarrez le serveur TCP backend :

```bash
cd C++
make clean && make
./myprog        # Mode test local
# OU pour le serveur TCP :
g++ -std=c++17 -Wall -Werror -o server server.cpp tcpserver.cpp ccsocket.cpp multimediamanager.cpp multimediaobject.cpp photo.cpp video.cpp film.cpp -lpthread
./server
```

> 🟢 **Résultat attendu** : Le serveur affiche `Serveur lancé ! Starting Server on port 3331`.

---

### 2️⃣ Lancer la Télécommande Java Swing

Dans un second terminal, compilez et lancez l'application graphique client :

```bash
cd Java-Swing/src
make compile
make run
```

---

## 💬 Protocole de Communication

Le client Java et le serveur C++ échangent des requêtes textuelles formatées via la connexion TCP (port `3331`) :

```text
Client  ───>  "show media franck"   ───>  Serveur
Client  <───  "Photo: franck ..."   <───  Serveur

Client  ───>  "show groupe Contenu" ───>  Serveur
Client  <───  "Groupe: Contenu ..." <───  Serveur

Client  ───>  "play video1"          ───>  Serveur
Client  <───  "Playing video1"       <───  Serveur
```

---

## 👤 Auteur

**Wassim Smati**
- 🎓 Élève-Ingénieur à **Télécom Paris**
- 🐙 GitHub : [@Wassim-Smati](https://github.com/Wassim-Smati)
- 💼 Project : **INF224 - Paradigmes de Programmation (C++ / Java)**

---

<div align="center">
  <sub>⭐ N'hésitez pas à mettre une étoile sur le dépôt si ce projet vous a plu ! ⭐</sub>
</div>
