#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>     // Timer
#include <time.h>   // Minuteur sans attente

// CONSTANTES :

// Les dimensions
#define LIGNE 31        // Taille de la ligne
#define COLONNE 28      // Taille de la colonne

#define MIN_LIGNE 0    // Index minimum de la grille (ligne)
#define MAX_LIGNE 30    // Index maximum de la grille (ligne)

#define MIN_COLONNE 0    // Index minimum de la grille (colonne)
#define MAX_COLONNE 27    // Index maximum de la grille (colonne)

// Sprites
#define MURS 0           // Mur vaut 0 dans la grille
#define CASE_VIDE 1     // Case vide vaut 1 dans la grille
#define BARRIERE 2      // Barriere vaut 2 dans la grille
#define PASTILLE 3      // Pastille vaut 3 dans la grille
#define PILULE 4        // Pilule de puissance vaut 4 dans la grille
#define FANTOME 5       // Fantôme vaut 5 dans la grille

// Les 4 positions du pacman
#define PHAUT 6        // Pacman avec la position HAUT
#define PBAS 7          // Pacman avec la position BAS
#define PGAUCHE 8       // Pacman avec la posiition GAUCHE
#define PDROITE 9       // Pacman avec la position DROITE

// Couleur (autre que ceux déjà défini par ncurses)
#define COLOR_ORANGE 8
#define COLOR_PINK 9

// Coordonnée des apparitions de fruits
#define FX 17
#define FY 12

// VARIABLES GLOBAUX :
int grille[LIGNE][COLONNE] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 4, 0, 1, 1, 0, 3, 0, 1, 1, 1, 0, 3, 0, 0, 3, 0, 1, 1, 1, 0, 3, 0, 1, 1, 0, 4, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 2, 2, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 0, 1, 1, 1, 1, 1, 1, 0, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 4, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 4, 0},
        {0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0},
        {0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

int grille2[LIGNE][COLONNE] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 4, 0, 1, 1, 0, 3, 0, 1, 1, 1, 0, 3, 0, 0, 3, 0, 1, 1, 1, 0, 3, 0, 1, 1, 0, 4, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 2, 2, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 0, 1, 1, 1, 1, 1, 1, 0, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 4, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 4, 0},
        {0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0},
        {0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0},
        {0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

// On initialise les coordonnées de Pacman :
int px = 29;  // Position X (ligne d'un tableau 2D) de Pacman 29
int py = 12;  // Position Y (colonne d'un tableau 2D) de Pacman 1
int p_isAlive = 1;

int gx[4] = {1,1,29,29};
int gy[4] = {1,26,1,26};
int g_isFrightened = 0;
int g_timer;

// On initialise le score :
int score = 0;

// FRUITS
int fruits[5] = {100,500,1000,3000,5000};
int nbr_f = 5;
int compteur = 0;

// FONCTIONS :
int chargerMeilleurScore() 
{
    FILE *fichier = fopen("me.txt", "r");
    int meilleurScore = 0;

    if (fichier != NULL) {
        fscanf(fichier, "%d", &meilleurScore);
        fclose(fichier);
    }

    return meilleurScore;
}

void sauvegarderMeilleurScore(int meilleurScore) {
    FILE *fichier = fopen("best_score.txt", "w");

    if (fichier != NULL) {
        fprintf(fichier, "%d", meilleurScore);
        fclose(fichier);
    }
}

void print_grille()
{
    for(int i = 0; i < LIGNE; i++)
    {
        for(int j = 0; j < COLONNE; j++)
        {
            if(grille[i][j] == CASE_VIDE)
            {
                attron(A_INVIS);
                printw(" x ");
                attroff(A_INVIS);
                // le caractère ' x ' sera invisible, le but ici c'est de représenter une case vide
            }
            if(grille[i][j] == MURS)
            {
                attron(A_REVERSE);
                printw("   ");
                attroff(A_REVERSE);
                // La fonction inverse le blanc et le noir
            }
            if(grille[i][j] == BARRIERE)
                printw(" = ");
            if(grille[i][j] == PASTILLE)
                printw(" · ");
            if(grille[i][j] == PILULE)
                printw(" o ");
            if(grille[i][j] == FANTOME)
            {
                if(i == gx[0] && j == gy[0])
                {   
                    if(g_isFrightened == 1)
                    {
                        attron(COLOR_PAIR(6));
                        printw(" M ");
                        attroff(COLOR_PAIR(6));
                    }
                    else
                    {
                        attron(COLOR_PAIR(1));
                        printw(" M ");
                        attroff(COLOR_PAIR(1));
                    }
                }
                if(i == gx[1] && j == gy[1])
                {
                    if(g_isFrightened == 1)
                    {
                        attron(COLOR_PAIR(6));
                        printw(" M ");
                        attroff(COLOR_PAIR(6));
                    }
                    else
                    {
                        attron(COLOR_PAIR(2));
                        printw(" M ");
                        attroff(COLOR_PAIR(2));
                    }
                }
                if(i == gx[2] && j == gy[2])
                {
                    if(g_isFrightened == 1)
                    {
                        attron(COLOR_PAIR(6));
                        printw(" M ");
                        attroff(COLOR_PAIR(6));
                    }
                    else
                    {
                        attron(COLOR_PAIR(3));
                        printw(" M ");
                        attroff(COLOR_PAIR(3));
                    }
                }
                if(i == gx[3] && j == gy[3])
                {
                    if(g_isFrightened == 1)
                    {
                        attron(COLOR_PAIR(6));
                        printw(" M ");
                        attroff(COLOR_PAIR(6));
                    }
                    else
                    {
                        attron(COLOR_PAIR(4));
                        printw(" M ");
                        attroff(COLOR_PAIR(4));
                    }
                }
            }
            if(grille[i][j] == PHAUT)
                printw(" v ");    
            if(grille[i][j] == PBAS)
                printw(" ^ ");
            if(grille[i][j] == PGAUCHE)
                printw(" > ");
            if(grille[i][j] == PDROITE)
                printw(" < ");
            if(grille[i][j] >= 100 && grille[i][j] <= 5000)
            {
                attron(COLOR_PAIR(5));
                printw(" B ");
                attroff(COLOR_PAIR(5));
            }    
        }
        printw("\n");
        refresh();
    }
}

// Cette fonction prend en paramètre un chiffre de 1 à 4, effectue le déplacement de pacman + affiche score
void pm_movement(int p, int s)
{
    grille[px][py] = CASE_VIDE; // La position initiale de Pacman devient une case vide

    switch(p)
    {
        case(0):    // HAUT
            px = px - 1;
            // COLLISION FANTOME
            if (grille[px][py] == FANTOME)
            {
                if(g_isFrightened == 0)
                {
                clear();
                mvprintw(LIGNE/2,COLONNE/2,"TU AS PERDU !!!");
                refresh();
                sleep(3);
                p_isAlive = 0;
                break;
                }    
            }
            // GESTION DU SCORE :
            if (grille[px][py] == PASTILLE)
            {
                score = score + 10;
                compteur = compteur + 1;
            }
            if (grille[px][py] == PILULE)
            {
                score = score + 50;
                g_isFrightened = 1;
                int g_timer = 25;
            }
            if (grille[px][py] >= 100 && grille[px][py] <= 5000)
                score = score + grille[px][py]; 
            grille[px][py] = PHAUT;
            break;
        case(1):    // BAS
            px = px + 1;
            // COLLISION FANTOME
            if (grille[px][py] == FANTOME)
            {
                if(g_isFrightened == 0)
                {
                clear();
                mvprintw(LIGNE/2,COLONNE/2,"TU AS PERDU !!!");
                refresh();
                sleep(3);
                p_isAlive = 0;
                break;
                }
            }
            // GESTION DU SCORE :
            if (grille[px][py] == PASTILLE)
            {
                score = score + 10;
                compteur = compteur + 1;
            }
            if (grille[px][py] == PILULE)
            {
                score = score + 50;
                g_isFrightened = 1;
                g_timer = 25;
            }
            if (grille[px][py] >= 100 && grille[px][py] <= 5000)
                score = score + grille[px][py]; 
            grille[px][py] = PBAS;
            break;
        case(2):    // GAUCHE
            py = py - 1;
            // COLLISION FANTOME
            if (grille[px][py] == FANTOME)
            {
                if(g_isFrightened == 0)
                {
                clear();
                mvprintw(LIGNE/2,COLONNE/2,"TU AS PERDU !!!");
                refresh();
                sleep(3);
                p_isAlive = 0;
                break;
                }
            }
            // GESTION DU SCORE :
            if (grille[px][py] == PASTILLE)
            {
                score = score + 10;
                compteur = compteur + 1;
            }
            if (grille[px][py] == PILULE)
            {
                score = score + 50;
                g_isFrightened = 1;
                g_timer = 25;
            }
            if (grille[px][py] >= 100 && grille[px][py] <= 5000)
                score = score + grille[px][py]; 
            grille[px][py] = PGAUCHE;
            break;
        case(3):    // DROITE
            py = py + 1;
            // COLLISION FANTOME
            if (grille[px][py] == FANTOME)
            {
                if(g_isFrightened == 0)
                {
                clear();
                mvprintw(LIGNE/2,COLONNE/2,"TU AS PERDU !!!");
                refresh();
                sleep(3);
                p_isAlive = 0;
                break;
                }
            }
            // GESTION DU SCORE :
            if (grille[px][py] == PASTILLE)
            {
                score = score + 10;
                compteur = compteur + 1;
            }
            if (grille[px][py] == PILULE)
            {
                score = score + 50;
                g_isFrightened = 1;
                g_timer = 25;
            }
            if (grille[px][py] >= 100 && grille[px][py] <= 5000)
                score = score + grille[px][py]; 
            grille[px][py] = PDROITE;
            break;
    }
    if(p_isAlive)
    {
        if(g_isFrightened == 1)
            g_timer = g_timer - 1;
        if(g_timer == 0)
            g_isFrightened = 0;
        switch(compteur)
        {
            case(50):
                grille[FX][FY] = fruits[0];
                grille2[FX][FY] = fruits[0];
                refresh();
                nbr_f = nbr_f - 1;
                break;
            case(65):
                grille[FX][FY] = CASE_VIDE;
                grille2[FX][FY] = CASE_VIDE;
                refresh();
                break;
            case(100):
                grille[FX][FY] = fruits[1];
                grille2[FX][FY] = fruits[1];
                nbr_f = nbr_f - 1;
                break;
            case(115):
                grille[FX][FY] = CASE_VIDE;
                grille2[FX][FY] = CASE_VIDE;
                refresh();
                break;
            case(150):
                grille[FX][FY] = fruits[2];
                grille2[FX][FY] = fruits[2];
                nbr_f = nbr_f - 1;
                break;
            case(165):
                grille[FX][FY] = CASE_VIDE;
                grille2[FX][FY] = CASE_VIDE;
                refresh();
                break;
            case(200):
                grille[FX][FY] = fruits[3];
                grille2[FX][FY] = fruits[3];
                nbr_f = nbr_f - 1;
                break;
            case(215):
                grille[FX][FY] = CASE_VIDE;
                grille2[FX][FY] = CASE_VIDE;
                refresh();
                break;
            case(250):
                grille[FX][FY] = fruits[4];
                grille2[FX][FY] = fruits[4];
                nbr_f = nbr_f - 1;
                break;
            case(265):
                grille[FX][FY] = CASE_VIDE;
                grille2[FX][FY] = CASE_VIDE;
                refresh();
                break;
        }
        clear();
        print_grille();
        mvprintw(LIGNE+1,0,"SCORE : %d", score);
        mvprintw(LIGNE+2,0,"MEILLEUR SCORE : %d", s);
        mvprintw(LIGNE+3,0,"FRUITS RESTANTS : %d", nbr_f);
        refresh();
    }
}

void g_movement(int p, int i, int s)
{
    grille[gx[i]][gy[i]] = grille2[gx[i]][gy[i]];

    switch(p)
    {
        case(0):
            gx[i] = gx[i] - 1;
            if(g_isFrightened == 0)
            {
                if (grille[gx[i]][gy[i]] == PHAUT || grille[gx[i]][gy[i]] == PBAS || grille[gx[i]][gy[i]] == PGAUCHE || grille[gx[i]][gy[i]] == PDROITE)
                {
                    clear();
                    mvprintw(LIGNE/2,COLONNE/2,"TU AS PERDU !!!");
                    refresh();
                    sleep(3);
                    p_isAlive = 0;
                    break;
                }
            }
            grille[gx[i]][gy[i]] = FANTOME;
            break;
        case(1):
            gx[i] = gx[i] + 1;
            if(g_isFrightened == 0)
            {
                if (grille[gx[i]][gy[i]] == PHAUT || grille[gx[i]][gy[i]] == PBAS || grille[gx[i]][gy[i]] == PGAUCHE || grille[gx[i]][gy[i]] == PDROITE)
                {
                    clear();
                    mvprintw(LIGNE/2,COLONNE/2,"TU AS PERDU !!!");
                    refresh();
                    sleep(3);
                    p_isAlive = 0;
                    break;
                }
            }
            grille[gx[i]][gy[i]] = FANTOME;
            break;
        case(2):
            gy[i] = gy[i] - 1;
            if(g_isFrightened == 0)
            {
                if (grille[gx[i]][gy[i]] == PHAUT || grille[gx[i]][gy[i]] == PBAS || grille[gx[i]][gy[i]] == PGAUCHE || grille[gx[i]][gy[i]] == PDROITE)
                {
                    clear();
                    mvprintw(LIGNE/2,COLONNE/2,"TU AS PERDU !!!");
                    refresh();
                    sleep(3);
                    p_isAlive = 0;
                    break;
                }
            }
            grille[gx[i]][gy[i]] = FANTOME;
            break;
        case(3):
            gy[i] = gy[i] + 1;
            if(g_isFrightened == 0)
            {
                if (grille[gx[i]][gy[i]] == PHAUT || grille[gx[i]][gy[i]] == PBAS || grille[gx[i]][gy[i]] == PGAUCHE || grille[gx[i]][gy[i]] == PDROITE)
                {
                    clear();
                    mvprintw(LIGNE/2,COLONNE/2,"TU AS PERDU !!!");
                    refresh();
                    sleep(3);
                    p_isAlive = 0;
                    break;
                }
            }
            grille[gx[i]][gy[i]] = FANTOME;
            break;
    }
    clear();
    print_grille();
    mvprintw(LIGNE+1,0,"SCORE : %d", score);
    mvprintw(LIGNE+2,0,"MEILLEUR SCORE : %d", s);
    mvprintw(LIGNE+3,0,"FRUITS RESTANTS : %d", nbr_f);
    refresh();
}
// MAIN :
int main() {
    // Code ici
    initscr();  // Initialise le terminal en mode curseur
    keypad(stdscr, TRUE);   // Désactivation de l'affichage des touches pressées
    noecho();   
    curs_set(0);  
    nodelay(stdscr, TRUE);  // Désactivation de la saisie en attente

    // On initialise les couleurs :
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);       // Initialisation de la couleur pour
    init_color(COLOR_PINK, 1000, 500, 800);
    init_pair(2, COLOR_BLACK, COLOR_PINK);      // Initialisation de la couleur pour 
    init_pair(3, COLOR_BLACK, COLOR_CYAN);      // Initialisation de la couleur pour 
    init_color(COLOR_ORANGE, 1000, 600, 100);
    init_pair(4, COLOR_BLACK, COLOR_ORANGE);    // Initialisation de la couleur pour

    init_pair(5, COLOR_BLACK, COLOR_GREEN);     // Fruits 

    init_pair(6, COLOR_RED, COLOR_WHITE);    // Fantome effrayé



    // Initialisation du meilleur score
    int meilleurScore = chargerMeilleurScore();

    // TEST DEPLACEMENT DE PACMAN AVEC NCURSES
    // Gérer l'entrée de l'utilisateur
    print_grille();
    int input;
    do
    {
        input = getch();
    }
    while(input != KEY_UP && input != KEY_DOWN && input != KEY_LEFT && input != KEY_RIGHT && input != 27);

    while(1)
    {
        int direction;
        switch (input)
        {
            case KEY_UP:
                // Changer la direction vers le haut
                direction = 0;
                break;
            case KEY_DOWN:
            // Changer la direction vers le bas
                direction = 1;
                break;
            case KEY_LEFT:
                // Changer la direction vers la gauche
                direction = 2;
                break;
            case KEY_RIGHT:
                // Changer la direction vers la droite
                direction = 3;
                break;
            case 27:
                if (score > meilleurScore)
                    {
                        meilleurScore = score;
                        sauvegarderMeilleurScore(meilleurScore);
                    }
                endwin(); // 27 = 'ESCAPE'
                return 0;
        }

        while(1)
        {   
            for(int i = 0; i<4; i++)
            {
                int movement_Possible[4] = {1, 2, 3, 4};    // Les issues possibles sont insérées dans ce tableau
                // -1 : L'issue n'est pas possible

                if(gx[i] == MIN_LIGNE || grille[gx[i]-1][gy[i]] == MURS || grille[gx[i]-1][gy[i]] == FANTOME || 
                grille[gx[i]-1][gy[i]] == BARRIERE)
                    movement_Possible[0] = -1; 
                if(gx[i] == MAX_LIGNE || grille[gx[i]+1][gy[i]] == MURS || grille[gx[i]+1][gy[i]] == FANTOME ||
                grille[gx[i]+1][gy[i]] == BARRIERE)
                    movement_Possible[1] = -1;
                if(gy[i] == MIN_COLONNE || grille[gx[i]][gy[i]-1] == MURS || grille[gx[i]][gy[i]-1] == FANTOME ||
                grille[gx[i]][gy[i]-1] == BARRIERE)
                    movement_Possible[2] = -1;
                if(gy[i] == MAX_COLONNE || grille[gx[i]][gy[i]+1] == MURS|| grille[gx[i]][gy[i]+1] == FANTOME ||
                grille[gx[i]][gy[i]+1] == BARRIERE)
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
                        g_movement(0,i,meilleurScore);
                        if(p_isAlive == 0)
                        {
                            if (score > meilleurScore)
                            {
                                meilleurScore = score;
                                sauvegarderMeilleurScore(meilleurScore);
                            }
                            endwin();
                            return 0;
                        }
                        break; 
                    case(1):
                        g_movement(1,i,meilleurScore);
                        if(p_isAlive == 0)
                        {
                            if (score > meilleurScore)
                            {
                                meilleurScore = score;
                                sauvegarderMeilleurScore(meilleurScore);
                            }
                            endwin();
                            return 0;
                        }
                        break;
                    case(2):
                        g_movement(2,i,meilleurScore);
                        if(p_isAlive == 0)
                        {
                            if (score > meilleurScore)
                            {
                                meilleurScore = score;
                                sauvegarderMeilleurScore(meilleurScore);
                            }
                            endwin();
                            return 0;
                        }
                        break; 
                    case(3):
                        g_movement(3,i,meilleurScore);
                        if(p_isAlive == 0)
                        {
                            if (score > meilleurScore)
                            {
                                meilleurScore = score;
                                sauvegarderMeilleurScore(meilleurScore);
                            }
                            endwin();
                            return 0;
                        }
                        break;
                }
                usleep(30000);  // Pause pendant la durée spécifiée
            }

            // Mettre à jour les coordonnées en fonction de la direction
            switch(direction)
            {
                case(0):
                    if (grille[px-1][py] != MURS && grille[px-1][py] != BARRIERE)
                    {    
                        pm_movement(direction,meilleurScore);
                        if(p_isAlive == 0)
                        {
                            if (score > meilleurScore)
                            {
                                meilleurScore = score;
                                sauvegarderMeilleurScore(meilleurScore);
                            }
                            endwin();
                            return 0;
                        }
                        usleep(200000);
                    }
                    break;
                case(1):
                    if (grille[px+1][py] != MURS && grille[px+1][py] != BARRIERE)
                    {    
                        pm_movement(direction,meilleurScore);
                        if(p_isAlive == 0)
                        {
                            if (score > meilleurScore)
                            {
                                meilleurScore = score;
                                sauvegarderMeilleurScore(meilleurScore);
                            }
                            endwin();
                            return 0;
                        }
                        usleep(200000);
                    }
                    break;
                case(2):
                    if (grille[px][py-1] != MURS && grille[px][py-1] != BARRIERE)
                    {    
                        pm_movement(direction,meilleurScore);
                        if(p_isAlive == 0)
                        {
                            if (score > meilleurScore)
                            {
                                meilleurScore = score;
                                sauvegarderMeilleurScore(meilleurScore);
                            }
                            endwin();
                            return 0;
                        }
                        usleep(200000);
                    }
                    break;
                case(3):
                    if (grille[px][py+1] != MURS && grille[px][py+1] != BARRIERE)
                    {    
                        pm_movement(direction,meilleurScore);
                        if(p_isAlive == 0)
                        {
                            if (score > meilleurScore)
                            {
                                meilleurScore = score;
                                sauvegarderMeilleurScore(meilleurScore);
                            }
                            endwin();
                            return 0;
                        }
                        usleep(200000);
                    }
                    break;
            }
            int new_input = getch(); // Attend une nouvelle entrée de l'utilisateur
            int i = 0;
            switch (new_input)
            {
                case KEY_UP:
                    if (new_input != input)
                        input = new_input;
                        i = 1;
                    break;
                case KEY_DOWN:
                    if (new_input != input)
                        input = new_input;
                        i = 1;
                    break;
                case KEY_LEFT:
                    if (new_input != input)
                        input = new_input;
                        i = 1;
                    break;
                case KEY_RIGHT:
                    if (new_input != input)
                        input = new_input;
                        i = 1;
                    break;
                case 27:
                    if (score > meilleurScore)
                        {
                            meilleurScore = score;
                            sauvegarderMeilleurScore(meilleurScore);
                        }
                    endwin(); // 27 = 'ESCAPE'
                    return 0;
            }
            if (i == 1)
                break;
        }
        
    }
    // Retourner EXIT_SUCCESS pour indiquer une sortie réussie (sinon EXIT_FAILURE)
    return EXIT_SUCCESS;
}