# TP C++ (INF224) - Partie multimédia

## Contenu réalisé
Ce projet implémente :
- une hiérarchie d'objets multimédia (`Photo`, `Video`, `Film`) ;
- un gestionnaire (`MultimediaManager`) avec tables d'objets et de groupes ;
- la sérialisation / désérialisation des objets multimédia (étape 12) ;
- la sérialisation / désérialisation des groupes sans duplication d'objets (références par nom) ;
- un traitement d'erreurs cohérent (étape 13) via exceptions `std::runtime_error` et retours raisonnables selon les cas.

## Choix principaux
- Les objets écrivent/lisent eux-mêmes leurs attributs via méthodes virtuelles (`writeData` / `readData`).
- Le type concret est persisté par `className()` et reconstruit via une fabrique dans `MultimediaManager`.
- Le format de fichier est texte ligne par ligne (utilisation de `getline`), ce qui évite les ambiguïtés sur les chaînes contenant des espaces.
- Les groupes stockent seulement les noms des médias pour éviter toute duplication d'objets partagés.

## Gestion d'erreurs
- Vérification des doublons de noms (objets et groupes).
- Validation de paramètres (noms, durées, chapitres).
- Vérifications robustes pendant la lecture de fichiers (fichiers tronqués, compteurs invalides, type inconnu, référence de groupe vers média absent).

## Build / exécution
- Compiler :
  ```bash
  make
  ```
- Exécuter :
  ```bash
  make run
  ```
- Nettoyer :
  ```bash
  make clean
  ```

## Note sur `main.cpp`
Comme recommandé dans le TP, `main.cpp` conserve deux versions de scénario via compilation conditionnelle (`#if VERSION_TP12_13` / `#else`).
