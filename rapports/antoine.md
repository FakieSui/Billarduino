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
Début de la rédaction de l'état de l´art
Début de la rédaction du planning de répartition des tâches
Ajouts dans la liste de matériel (maintenant plus complète)
