Rôle personnel:

Conception de la partie algorithmique du code qui permettra le calcul de l'angle du moteur pas à pas (moteur step). Et aussi le nombre de tours que devra effectuer le moteur 12 Volt Nema 17 qui correspondra en fait à la distance de parcourt de celui-ci.

Séance du Lundi 3 Décembre (1)

Lors de cette première scéance avec la pixycam, nous avons réussi à identifier des objets de différentes couleurs (rouge, bleu et jaune).
Dans un premier temps on a fait l'aquisition des objets, et ensuite la caméra peut détecter les objets n'importe où dans son champs de vision.
Cela nous permettra pour les scéances futures d'identifier les différentes boules de billard et surtout de déterminer leurs positions en fonction du champs de vision rectangulaire de la pixycam.
Schéma de l'acquisition des différents objets:


![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/acquisition_tournevis.png)




Séance du Lundi 10 décembre (2):

Maintenant que nous avons en possession notre billard, nous avons déterminer l'objectif précis de notre projet.
L'objectif est de pouvoir mettre une bille objet n'importe où dans le billard et, grâce à une bille blanche que nous allons propulser sur la bille objet, la bille objet ira automatiquement dans le trou.
Nous n'allons utiliser que deux trous sur les six trous du billard; deux trous d'extrémité.
Nous nous sommes fixé comme objectif de mi-projet de prendre toujours la même position de la boule blanche.
En revanche, pour la fin de projet, le bille blanche pourra être placée sur une ligne le long de la largeur du billard.

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/billard_initial.jpg)


Séance du lundi 17 décembre (3):

Lors de cette séance nous avons principalement trouvé les équations mathématiques qui nous permettrons de calculer les endroits précis d'impact voulu. Le principe est simple:
à partir des coordonées de la bille blanche et de la bille objet (en deux dimension, coordonnées cartésiens), nous pouvons calculer les coordonnées de "tire", c'est à dire où exactement nous devons lancer la bille blanche. Cette position ne sera rien d'autre que le prolongement d'une distance du diamètre des boules du vecteur trou ---> bille objet en partant de la bille objet.
Pour la rotation du module, c'est un simple calcul d'angle en fonctions des coordonnées des deux billes et du trou.
Notre recherche est schématisé, légendé et expliqué sur les photos ci-dessous.

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/calculs_angle_et_dist.jpg)

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/schema_billard.jpg)

Séance du lundi 14 janvier (4):

Nous avons récupéré une grande partie du matériel nécéssaire à la conception du projet:

-Découpage de la tige fileté pour supporter le module de translation.
-Découpage de la tige coulisante pour envoyer l'impact.
-No













