# Avant séance

## Structuration du code 

Séparation en code en tests, modules et fichiers principaux.

## Adaptation du code du webserver pour le transformer en module

- Création d'un fichier ```Constants.h``` pour regrouper toutes les constantes relatives à la configuration de l'Arducam
  (Pins utilisés, ...) et des identifiants (Wifi nécessaire pour diffusion des images sur un webserver)
- Adaptation du code d'exemple de webserver en une classe LiveStream structurée en plusieurs fonctions (```stream_handler``` qui sert à réaliser la capture, 
```startCameraServer``` servant à démarrer le serveur Web qui diffusera les images en direct, ```init``` qui définit les headers
et différentes métadonnées et ```main``` s'occupant d'initialiser les autres variables et appeler les fonctions nécessaires).

# Pendant la séance

- Recherche d'informations concernant la reconnaissance faciale
- Configuration d'un module Wifi pour que la carte ESP puisse diffuser un flux vidéo en direct sur un réseau local
  (aussi bien Eduroam qu'Unice Hotspot nécessitent une connexion avec les identifiants universitaires et ne répondaient donc pas aux besoins)
- Après s'être rendu compte que l'ESP32 ne répondait pas à nos besoins, recherche de plusieurs solutions alternatives
  (Optical Flow, Pixy, K210)
- Recherche de programmes et début d'écriture pour la reconnaissance faciale sur le K210