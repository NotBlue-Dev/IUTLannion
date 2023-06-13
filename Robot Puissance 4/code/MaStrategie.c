#include <stdio.h>
#include <stdlib.h>

#define LIGNE 6
#define COLONNE 7

typedef int t_grille[LIGNE][COLONNE];

int main(int argc, char** argv);
void chargerGrille(char** argv, t_grille grille);

const int VIDE = 0;
const int JOUEUR = 1;
const int ADVERSAIRE = 2;

/*
* VOTRE STRATEGIE
*/
int maStrategie(t_grille grille)
{
    // TODO: Votre strategie de victoire. La seule fonction que vous aurez à modifier.
    // libre à vous d'en créer d'autres pour aérer votre code. 
    // La variable grille est un tableau à deux dimensions d'entiers, c'est la grille du tour. 
    // Un VIDE représente une case vide, 1 représente vos jetons et 2 représente les jetons adverses.
    // A vous de choisir le meilleur prochain coup !

    int meilleureClonne;
    int i = 0;

    do{
        meilleureClonne = ((long int)&meilleureClonne + i) % COLONNE; // On choisit une colonne au hasard
        i++;
    }while(grille[0][meilleureClonne] != VIDE); // On change de colonne si elle est pleine

    // Retourne la meilleure colonne à jouer
    return meilleureClonne;
}

// La fonction principale reçoit la grille du tour et retourne le coup choisi
// Vous n'avez pas à modifier cette fonction
int main(int argc, char** argv) 
{
    t_grille grille;

    chargerGrille(argv, grille);

    return maStrategie(grille);
}

// Charge la grille du tour actuel
// Vous n'avez pas à modifier cette fonction
void chargerGrille(char** argv, t_grille grille) 
{
    for(int i = 0; i < LIGNE; i++)
        for(int j = 0; j < COLONNE; j++)
            grille[i][j] = atoi(argv[i * COLONNE + j + 1]);
}
