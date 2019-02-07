# Rôle personnel :
- Programmation de la PixyCam pour l'acquisition
- Programmation de l'Arduino pour faire le lien entre l'acquisition video et les moteurs
- Construction de la PixyPerche (featuring Lyonnel Dahan)
- Construction du module + rail (featuring Lyonnel Dahan)

# Séance du Lundi 3 Décembre (1)

Grâce à la PixyCam fourni la séance précédente, nous avons réalisé des acquisitions diverses des objets du laboratoire :

Tout d'abord, pour se familiariser avec la définition des signatures, nous avons réalisé l'acquisiton de la signature du bracelet de Maxime.


![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/acquisition_bracelet.png)

Ensuite, nous avons enseigné à la PixyCam des objets de différentes Formes / Couleurs :
- Tournevis rouge
- Tournevis jaune
- Pince vertes

Pour ce qui est de la manière de définir une signature, il faut tout d'abord brancher la PixyCam à l'ordinateur. On laisse ensuite son doigt appuyé sur le seul bouton de la PixyCam pour faire défiler les couleurs qui correspondent aux emplacements de signatures. Ainsi, on a un cycle de couleurs qui nous permet de choisir et de définir un total de 8 signatures. Voici donc les signatures que l'on définit :
1 - Bille Jaune
2 - Bille Bleue
3 - Gommette 1 (point de référence 1)
4 - Gommette 2 (point de référence 2)

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

Nous avons accueilli Mattéo, 13 ans, qui a été à l'origine d'un déficit de temps sur la séance.
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


## Appairage Pixy-Arduino

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

# Séance du Lundi 7 Janvier (4)

Objectif de la séance : Récupérer le maximum de matériel pour la fabriquation du module queue-de-billard sur le rail.

Durant cette séance, Monsieur Masson nous a régalé en nous fournissant 99.9%  de ce qu'il nous fallait à savoir :
- Une tige filetée
- Une tige coulissante
- Un écrou (pour la tige filetée)
- Une prise à roulement (pour la tige filetée)
- Deux fixations (pour la tige coulissante)
- Un coulisseau (pour la tige coulissante)
- Un moteur pas à pas 12V Nema 17
- Un coupleur (pour le moteur)

Le seule élément manquant est le driver pour le moteur Nema 17.

Ainsi, nous avons retaillé les tiges aux bonnes dimensions pour notre billard en coupant large (45cm contre 31.6cm pour la largeur du billard) pour pouvoir tirer avec les angles les plus extrêmes. En effet, lorsque le module qui coulisse se trouve en butée, il faut compter la demi largeur du module ainsi que le décalage pour donner le coup de queue dans le bon angle.


# Travail d'un Jeudi 10 Janvier

Avec l'aide d'un ami sur Nice (Lyonnel Dahan), il nous a été possible de fabriquer à l'aide de bois de palette la PixyPole (perche pour la PixyCam). Il a été éprouvant en terme de conception d'ériger une perche stable, légèrement reglable la plus légère possible et la plus démontable possible.

Après 6 heures de travail pour confectionner cette fameuse perche, nous obtenons un signal video sur l'ordinateur qui est digne d'un jeu de billard :

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/pictural_ball_scrap.png)


Comme on l'a vu précédemment, il faut passer en mode "Raw" pour que la PixyCam envoie les informations des blocks en direct sur l'Arduino (qu'on affiche via le Serial) :


![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/raw_ball_scrap.png)

Côté programme, il nous suffira d'établir une échelle pour savoir combien représente une mesure réelle par rapport à une mesure de la PixyCam.

# Travail d'un Vendredi 11 Janvier

Après la PixyPole, c'est au tour du module avec la pseudo-queue de billard d'être usinée ; la fabrication suit les idées du gribouillage, moyennant quelques rectifications :
- L'elastique est fixé directement sur le coulisseau
- On tire la tige (qui fait office de queue) pour armer le coup
- Il n'est plus question de courroie mais de tige filetée (avec le moteur Nema 17 au bout)

Il faut donc intégrer le petit moteur step au module pour ce qui est de la rotation, avec le coulisseau parfaitement dans l'axe du pan du moteur. Pour cela, nous avons fait mes marquages et travaillé précisément au foret. Enfin, n'ayant qu'un seul écrou, nous avons du le coller (à la colle chaude) en l'ayant vissé sur la tige filetée afin de l'aligner parfaitement avec la tige de coulissement.

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/module_front.jpg)
![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/module_back.jpg)
![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/module_rail.jpg)

# Séance du Lundi 14 Janvier (5)

Durant cette séance de présentation des projets, j'ai fixé les longeurs de cablâge nécessaire pour tous les composant du billard : en effet, il était primordial de recouper un câble pour le bus ISCP de l´arduino qui est relié à la PixyCam en haut de la perche ! De plus, j'ai soudé des câbles femelles sur les fils du moteur Nema 17 afin de facilitter les branchements sur la carte Arduino.

Ayant fait marché l'ensemble des moteurs plus tôt dans la journée, j'ai été déçu de ne pas pouvoir montrer le potentiel actuel du billard et le réel avancement du projet : il ne reste désormais plus qu'a systematiser nos calculs et à traverser une longue phase de tests et d´ajustements ! Cependant, voici un extrait YOUTUBE des deux moteurs (translation et rotation) en marche :

https://youtu.be/6LOCkjsy5lc

# Travail durant la semaine de fin de semestre

Durant cette semaine, j'ai rédigé le [programme final](https://github.com/AntoineFacq/Billarduino/tree/master/code/Billarduino) à uploader sur l'arduino. Celui ci est orienté objet, c'est à dire qu'il est découpé en classes qui peuvent hériter des propriétés d'autres classes.

Par exemple, pour les classes relatives aux moteurs, TranlationMotor et RotationMotor héritent de Motor qui lui même hérite de Stepper. Le blabla n'étant jamais clair, voici comment on récapitule cela :
```

                          | --- <TranslationMotor>
<Stepper> --- <Motor> --- |
                          | --- <RotationMotor>
```


C'est donc sur ce modèle là que j'ai créé des classes qui permettent de définir un "Point", une "Scale" (échelle) à partir de deux points pour pouvoir ainsi faciliter nos calculs

## Structure du programme
- Initialisation des modules [Pixy, TranlationMotor, RotationMotor], des constantes et des longueurs en centimètres au sein du programme principal (Billarduino.ino)
- Réalisation de l'acquisition (à l'aide de SPI.h et Pixy.h) uniquement si on détecte les 4 éléments nécessaires à savoir les deux billes et les deux gomettes.
- Réorganisation des points de l'échelle
- Définition des points indispensables au calcul (comme le centre des deux poches) à partir de l'échelle
- Application des calculs pour la trajectoire (L, PHI) qui correcpondent respectivement à la rotation et la translation

Ainsi, à partir du signal de la camera, on se retrouve avec notre module prêt à faire feu !

Cependant, ce qu'il reste désormais à faire est de tester tout cela. A noter que l'orientation objet du programme facilitera la corrction des erreurs et l'implémentation de fonctionnalité qui auraient pu être oubliées durant la rédaction initiale.

Le code est disponible [ici](https://github.com/AntoineFacq/Billarduino/tree/master/code/Billarduino).



# Séance du Mercredi 06 Févrirer (6)

Durant cette séance, j'ai pu résoudre toutes les erreurs du code pour que la compilation soit menée à bien. Grâce à l'IDE Arduino et la structuration du code, celui ci ne devrait pas oser de problèmes à l'exécution.

Nous avons aussi réusiner la plateforme de maintient de la queue de billard et du coulisseau pour les raisons suivantes :
- La plateforme s'était fendu lors de son usinage : cela ne posait fondamentalement pas de problème, mais doutant sur le degrès d'imprécision qu'elle apportait à l'ensemble, il était nécessaire de la refaire.
- Le rebord de la plateforme devait de toute façon être raboté car il ne permettait pas la complète rotation du module en butée du billard. Pour faire simple, ça "touchait" le bord quand on faisait tourner le module.

Le choix d'un bois de récupération plus approprié a permis de résoudre ce problème. Voici donc une photo de la nouvelle plateforme. On notera que j'ai aussi installé les elastiques de rappel pour propulser la queue de billard :

![PHOTO](https://github.com/AntoineFacq/Billarduino/blob/master/rapports/images/new_platform.jpg)

De plus, nous avons créé une rallonge de 6 cables afin que le module puisse translater sur toute la longueur de la tige filetée.
