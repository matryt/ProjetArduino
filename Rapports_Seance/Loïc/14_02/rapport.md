# Avant la séance :
- Ajout de joints thoriques aux deux roues pour l'adhérence 
- Ajout/cablage d'un capteur de distance + fixation( colle ) sur l'avant du robot pour la detection des obstacles lorsque le robot se déplace
- Début des tests moteurs et servo moteurs avec la carte MaixDuino => les composants choisi correspondent bien au besoins prévu dans le cahier des charges
- cablage de l'alimentation de la carte MaixDuino via le vin et le gnd 
    - rallongement des cables pour pouvoir ramener les deux alimentations ( MaixDuino + pont en H ) au même endroit dans l'objectif de finaliser le cablage facilement vers la sortie du support de piles.
# Pendant la séance : 
- fixation plaque arrière en bois ( machine découpe laser ) au pistolet à colle sur le robot 
    => fixation du support de piles ( amovible pour le chargement ) avec une bande de velcros sur celle-ci 
- Test d'alimentation avec les piles => OK avec le code de test mais pose problème avec le code principale 
                                        - donc pas de problème de cablâge mais le problème viens bien du code principale
- Vérification de la configuration des pins dans le code principale => OK

	

# Prochaine Séance : 
- Ajout et cablage d'un bouton au niveau de la carte arduino 
- Continuer les testes en faisant fonctionner la carte MaixDuino et s'assurer de la bonne réception des données sur l'interface
- Teste pour savoir si la reconnaissance de visage marche correctement lorsque que le robot est en mouvement 