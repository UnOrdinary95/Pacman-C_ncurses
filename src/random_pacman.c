#include <stdlib.h>
#include <stdio.h>
#include <time.h>       // Utile pour générer des nombres !
#include <unistd.h>     // Timer


// CE CODE COUVRE LES QUESTIONS DE 1 A 6 !

// CONSTANTES :
#define DIMENSION 10    // Pour créer une grille 10 * 10
#define MIN_GRILLE 0    // Index minimum de la grille
#define MAX_GRILLE 9    // Index maximum de la grille

#define CASE_VIDE -1    // Case vide vaut -1 dans la grille 
#define OBSTACLE 0      // Obstacle vaut 0 dans la grille
#define PASTILLE 1      // Pastille vaut 1 dans la grille
#define PILULE 2        // Pilule de puissance vaut 2 dans la grille
#define FANTOME 3       // Fantôme vaut 3 dans la grille
#define PACMAN 4        // Pacman vaut 4 dans la grille

// VARIABLES GLOBAUX :

// On initialise une grille :
int grille[DIMENSION][DIMENSION] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 1, 4, 1, 1, 1, 1, 2, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {0, 2, 1, 1, 1, 1, 1, 1, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

// On initialise les coordonnées de Pacman :
int px = 1;  // Position X (ligne d'un tableau 2D) de Pacman
int py = 3;  // Position Y (colonne d'un tableau 2D) de Pacman

// On initialise le score :
int score = 0;

// FONCTIONS :

// Cette fonction affiche la grille avec des caractères Unicode
void print_grille() 
{
    for(int j = 0; j < DIMENSION; j++)
    {
        for(int i = 0;i < DIMENSION;i++)
        {
            if(grille[j][i] == CASE_VIDE)
                printf("   ");
            else if(grille[j][i] == OBSTACLE)
                printf(" \u2588 ");
            else if(grille[j][i] == PASTILLE)
                printf(" \u2022 ");
            else if(grille[j][i] == PILULE)
                printf(" \u25C6 ");
            else if(grille[j][i] == FANTOME)
                printf(" \u2623 ");
            else if(grille[j][i] == PACMAN)
                printf(" \u0D9E ");
        }
        printf("\n");
    }
} 

// Cette fonction demande à l'utilisateur le nombre de fantôme à placer dans la grille
int how_many_ghost()
{
    int nbr=0;
    do
    {
        printf("Définir le nombre de fantôme entre 1 et 4 : ");
        scanf("%d", &nbr);
        if(nbr < 1 || nbr > 4){
            printf("Veuillez saisir un nombre entre 1 et 4.\n");
        }
    }
    while (nbr < 1 || nbr > 4);
        
    printf("Nombre de fantôme(s) = %d\n", nbr);
    return nbr;
}

// Cette fonction prend en paramètre le nombre de fantôme et les place aléatoirement dans la grille
void replace_ghost(int n)
{
    for (int k = 0; k != n; k++)
    {
        int alea_ligne;
        int alea_colonne;

        while (1)
        {
            alea_ligne = rand()%DIMENSION;  // Valeur aléatoire entre 0 et DIMENSION - 1 (ou 9)
            alea_colonne = rand()%DIMENSION;    // Valeur aléatoire entre 0 et DIMENSION - 1 (ou 9)

            // On cherche à remplacer la pastille ou la pilule par un fantôme avant de break
            if (grille[alea_ligne][alea_colonne] == PASTILLE || grille[alea_ligne][alea_colonne] == PILULE)
            {
                grille[alea_ligne][alea_colonne] = FANTOME;
                break;
            }
        }
    } 
}
 
// Cette fonction prend en paramètre un chiffre de 1 à 4, effectue le déplacement de pacman + affiche score
void pm_movement(int p)
{
    grille[px][py] = CASE_VIDE; // La position initiale de Pacman devient une case vide

    switch(p)
    {
        case(0):    // HAUT
            px = px - 1;
            // GESTION DU SCORE :
            if (grille[px][py] == PASTILLE || grille[px][py] == PILULE)
                    score++;
            break;
        case(1):    // BAS
            px = px + 1;
            // GESTION DU SCORE :
            if (grille[px][py] == PASTILLE || grille[px][py] == PILULE)
                    score++;
            break;
        case(2):    // GAUCHE
            py = py - 1;
            // GESTION DU SCORE :
            if (grille[px][py] == PASTILLE || grille[px][py] == PILULE)
                    score++;
            break;
        case(3):    // DROITE
            py = py + 1;
            // GESTION DU SCORE :
            if (grille[px][py] == PASTILLE || grille[px][py] == PILULE)
                    score++;
            break;
    }

    grille[px][py] = 4; // Affichage du Pacman dans une nouvelle case
    print_grille();
    printf("\nScore : %d\n", score);
}

// MAIN :
int main() {
    // Code ici
    srand(time(NULL)); // Garantit une séquence pseudo-aléatoire différente à chaque exécution du programme.
    
    // TEST AFFICHAGE DE LA GRILLE :
    printf("Grille Initiale :\n");
    print_grille();

    // TEST COMBIEN DE FANTOME :
    int f = how_many_ghost();

    // TEST PLACEMENT ALEATOIRE DES FANTOMES :
    replace_ghost(f);
    printf("\nGrille avec fantôme :\n");    
    print_grille();
    printf("\n");
    sleep(3);

    // TEST DEPLACEMENT ALEATOIRE DE PACMAN (60 Itérations / 60 Pas)
    int i = 0;

    while (i < 60)
    {
        int movement_Possible[4] = {1, 2, 3, 4};    
        // Les issues possibles sont insérées dans ce tableau
        // -1 : L'issue n'est pas possible

    
        if(px == MIN_GRILLE || grille[px-1][py] == OBSTACLE || grille[px-1][py] == FANTOME)
            movement_Possible[0] = -1; 
        if(px == MAX_GRILLE || grille[px+1][py] == OBSTACLE || grille[px+1][py] == FANTOME)
            movement_Possible[1] = -1;
        if(py == MIN_GRILLE || grille[px][py-1] == OBSTACLE || grille[px][py-1] == FANTOME)
            movement_Possible[2] = -1;
        if(py == MAX_GRILLE || grille[px][py+1] == OBSTACLE || grille[px][py+1] == FANTOME)
            movement_Possible[3] = -1;

        int alea_move;  // Choisi une issue possible aléatoirement
        do
        {
            alea_move = rand() % 4;
        }
        while (movement_Possible[alea_move] == -1); // On veut ignorer les issues impossibles

        switch(alea_move)   // Réalise le déplacement en fonction du chiffre obtenue
        {
            case(0):
                pm_movement(0);
                break; 
            case(1):
                pm_movement(1);
                break;
            case(2):
                pm_movement(2);
                break; 
            case(3):
                pm_movement(3);
                break;
        }
        sleep(1);  // Pause pendant la durée spécifiée (ici 1 seconde de pause)
        i++;
    } 

    // Retourner EXIT_SUCCESS pour indiquer une sortie réussie (sinon EXIT_FAILURE)
    return EXIT_SUCCESS;
}