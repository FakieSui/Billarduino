# Rôle personnel :
- Programmation de la PixyCam pour l'acquisition
- Programmation de l'Arduino pour faire le lien entre l'acquisition video et les moteurs


# Séance du Lundi 3 Décembre (1)

Grâce à la PixyCam fourni la séance précédente, nous avons réalisé des acquisitions diverses des objets du laboratoire :

Tout d'abord, pour se familiariser avec la définition des signatures, nous avons réalisé l'acquisiton de la signature du bracelet de Maxime.


![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/acquisition_bracelet.png)

Ensuite, nous avons enseigné à la PixyCam des objets de différentes Formes / Couleurs :
- Tournevis rouge
- Tournevis jaune
- Pince vertes

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/acquisition_tournevis.png)

Il est intéressant de remarquer qu'au niveau du Tournevis Rouge, on voit au niveau de la colerette jaune que la PixyCam croit détecter un "Tournevis Jaune"
On s'attend donc par déduction à ne pas choisir des objets de couleurs voisines ou des objets multicolors, dans le potentiel risque d'avoir des problèmes d'acquisition.

# Séance du Lundi 10 Décembre (2)

Le billard modèle réduit nous a été fourni par Monsieur Masson (évènement providentiel)
Nous avons ensuite réalisé l'acquition des billes de billard dirèctement sur le tapis de jeu.


![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/billard_initial.jpg)

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/acquisition_bille.png)

Il nous manque la photo de l'acquisition des billes à même le billard.

Nous avons commencé à étudier concrètement comment le projet fonctionnera, ce qui nous as permis d'établir les étapes du fonctionnement du projet :
1- Mise sous tension de l'ensemble [Arduino PixyCam]
2- Acquisition vue du dessus du billard et de la position des billes
3- Calcul de la distance au bord et de l'angle de la queue de billard en fonction des positions des billes
4- Placement du module Queue de Billard grâce aux moteurs à l'emplacement calculé
5- Mise sous tension de la queue de billard avec un elastique tiré à l'aide d'un moteur
6- On relache le moteur pour percuter la bille blanche
7- A l'impact, grâce à nos calculs, la bille blanche percute la bille objet qui se dirige dans le trou.


# Séance du Lundi 17 Décembre (3)

Nous avons accueilli Mattéo, 13 ans, qui a été à l'origine d'un déficit de temps sur la séance
Cependant, nous avons étudié les formules permettant de déterminer les informations clés à la préparation du tir (soit [PHI, L])

Voici sur la feuille suivante l'ensemble des calculs qui ont fait l'objet de notre travail (aucun résultat sur internet n'a été trouvé)


![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/calculs_angle_et_dist.jpg)

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/schema_billard.jpg)

De plus nous avons commencé à étudier le fonctionnement des moteurs pas à pas :


![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/moteur_step.jpg)

# Travail des vacances (noël)
Gribouillage pour la confection du module basé sur 3 moteurs pas à pas (steppers) :
- Translation (déplacement du module)
- Rotation (pivot du module)
- Translation (impact dans la bille avec relâchement du stepper)
![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/50002E56-34F4-4C36-9A6F-B8EEDA670598.jpeg)
Début de la rédaction de l'état de l'art  
Début de la rédaction du planning de répartition des tâches  
Ajouts dans la liste de matériel (maintenant plus complète)  


## Accouplement Pixy Arduino

Après avoir montré que l'on pouvait visionner l'identification des signatures sur le PC, il faut maintenant passer à un dialogue en canal direct Arduino-PixyCam, et voici le fruit de ce travail :

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/pixy_with_arduino.jpg)
![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/pixy_to_arduino.png)

A défaut d'avoir une accueil de fiche femelle ISCP sur la carte Atmel (fiche qui permet la connexion entre Arduino et PixyCam), on connecte la fiche à l'arduino à l'aide de fils males-males sur des pins biens précis, comme spécifié sur le document suivant :

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/iscp_connection.jpg)


Ensuite, on lance le logiciel PixyCam, et ayant déjà défini les signatures précédemment, on passe le logiciel en mode "Default Program" pour que la PixyCam puisse transmettre les informations d'acquisition à l'Arduino. Sinon, la Pixy n'a pas assez de puissance pour transmettre un signal video et envoyé les informations à l'arduino !

Après avoir pointé les deux billes de billard, voici le "var dump" (debug) de ce que contient de tableau de blocks (objets identifiés) :

```
Detected 2:
  block 0: sig: 1 x: 37 y: 139 width: 46 height: 47
  block 1: sig: 2 x: 276 y: 98 width: 51 height: 52
```

On nous dit bien en effet que deux blocks ont été détectés, puis on donne la liste de ceux ci ; on sait que la signature 1 correspond à la bille jaune et la 2 à la bleu (cf Séance du Lundi 10 Décembre). On peut récupérer les coordonnées (x, y) et la hauteur (height) et largeur (width) des objets identifiés
