# Avant la séance

- Modification des modules pour variabiliser le code
- Changement du système d'inclinaison du servomoteur 
- Création d'un module Bouton poussoir qui permettra de lancer le déplacement du robot uniquement après les vérifications nécessaires
- Organisation du code

# Pendant la séance
- Création du modèle 3D et découpe laser de la plaque arrière et du rebord fixé sur la plaque pour pouvoir y accrocher la batterie
- Test du programme avec Loïc : celui ci ne fonctionne pas mais pas de souci du côté des programmes de tests. Après vérification, le problème venait de l'initialisation des modules, qui n'était pas faite correctement
- Modification des différents modules après quelques recherches complémentaires sur les classes en C++
- Adaptation de différentes valeurs (angle minimal et maximal du servomoteur pour incliner la caméra, temps et vitesse de demi-tour, distance d'arrêt)
- Système de vitesse différent (moteur gauche visiblement plus puissant que le droit)
- Après avoir constaté le dysfonctionnement du rechargement automatiquement de l'interface lors de nouveau contenu, système de rechargement automatique toutes les secondes
- Temporisation sur l'envoi de données depuis la MaixDuino : données envoyées uniquement toutes les secondes
- Test de l'intégration de la MaixDuino sur le robot et avec l'ordinateur