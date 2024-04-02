
# SAE1 - Pacman

Ce projet a été réalisé dans le cadre d'une SAE (Situation d'Apprentissage et d'Evaluation) en première année de BUT GEII (Bachelor Universitaire de Technologie || Génie Électrique et Informatique Industrielle) durant le premier semestre.

Le projet est écrit en langage C, compilable et exécutable dans un environnement Linux.







## Compilation

Pour compiler le fichier pacman1.c, utilisez la commande suivante :

```bash
    gcc pacman1.c -o pacman1 && ./pacman1
```

(Avant de procéder, veuillez installer ncurses.h sur Linux ou via WSL sur Windows)

Pour compiler le fichier jeupacman.c, utilisez la commande suivante :

```bash
    gcc jeupacman.c -o jeupacman -lncurses && ./jeupacman
```

    
## Captures d'écran

![App Screenshot](https://i.ibb.co/GFM3mbK/image.png)

![App Screenshot](https://i.ibb.co/gwVbD32/image2.png)

![App Screenshot](https://i.ibb.co/x35bt6n/image3.png)


## Sujet

Le but du jeu consiste à déplacer un personnage nommé Pac-Man à l’intérieur d’un labyrinthe afin de lui faire manger toutes les petites pastilles
jaunes qui s’y trouvent. 

Au sein de ce labyrinthe, on trouve 1 à 4 fantômes
qui sont les ennemis du Pac-Man.

L’utilisateur doit donc éviter de se faire
dévorer par l’un d’entre eux.

Le but étant de créer une version simplifié du jeu pacman afin de mettre en pratique les bases du langage C.

Le projet devra implémenter plusieurs fonctionnalités de base. On utilisera des fonctions pour simplifier le
code du main() et certaines variables globales pour simplifier les fonctions.

1. Programmer la grille comme un tableau 2D. Il faudra se définir des valeurs pour les obstacles, les cases avec une pastille
Dans un premier temps, on pourra utiliser une grille de taille modeste (10×10 par exemple, ou plus petite
pour les tests initiaux). 
On programmera cette grille « en dur » avec une initialisation de tableau 2D.

2. Programmer les fonctionnalités permettant de visualiser le labyrinthe. Dans un premier temps, vous pourrez réaliser une interface en mode console à l’aide de la fonction printf().

3. Programmer les fonctionnalités permettant à l’utilisateur de choisir un nombre de fantôme (1 à 4).

4. Programmer les fonctionnalités permettant de placer aléatoirement les fantômes dans le labyrinthe. Attention aux murs.

5. Programmer les fonctionnalités permettant au Pac-Man de se déplacer aléatoirement sans toucher les murs.

6. Gérer un score, par exemple la capacité à prendre en compte le nombre de pastilles mangées.

\
Le code source jeupacman.c contient la suite du projet mais en bonus (réalisé avec ncurses.h) :

7. Programmer les fonctionnalités permettant à l’utilisateur de déplacer le Pac-Man en appuyant sur les touches du clavier

8. Programmer les fonctionnalités de sauvegarde d’une partie en cours et de chargement d’une partie sauvegardée.

9. Programmer les règles du Pac-Man

Personnellement, j'ai implémenté un système de récolte de fruits qui apparaissent sur la carte, ainsi que le changement de couleur des fantômes lorsque Pac-Man mange une pilule de puissance.

Je n'ai pas eu le temps d'implémenter Pac-Man pour qu'il soit capable de manger les fantômes, ni les déplacements des fantômes à l'aide d'algorithmes complexes comme A* ou Dijkstra.
