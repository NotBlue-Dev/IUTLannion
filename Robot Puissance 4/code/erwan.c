#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NB_LIGNES 6
#define NB_COLONNES 7
#define MILLIEU (NB_COLONNES / 2)

typedef int t_grille[NB_LIGNES][NB_COLONNES];

int main(int argc, char** argv);
void chargerGrille(char** argv, t_grille grille);
int trouverLigne(t_grille laGrille, int col);
bool estVainqueur(t_grille laGrille, int lig, int col);
int deuxAligner(t_grille laGrille, int x, int y, int *bloqueX, int *bloqueY, int joueur, int adversaire);

const int VIDE = 0;
const int JOUEUR = 1;
const int ADVERSAIRE = 2;


bool estVainqueur(t_grille laGrille, int lig, int col){
    // consiste à regarder si une ligne de 4 pions s'est formée autour du pion qui vient de tomber en (lig, col)
    int lePion = laGrille[lig][col];
    int cpt,i,j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<NB_LIGNES && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions à l'Est et à l'Ouest
    j = col;
    cpt = 0;
    // on regarde à l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde à l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=4 ){
        return true;
    }
    return false;
}

int chercherLigne(t_grille laGrille, int col){
    int ligne = -1;

    while (ligne<NB_LIGNES-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}


int deuxAligner(t_grille laGrille, int x, int y, int *bloqueX, int *bloqueY, int joueur, int adversaire) {
    if(laGrille[x][y] != VIDE && laGrille[x][y] != joueur) {
        int pion = adversaire;
        int compteur,i,j;
        i = x;

        compteur = 0;

        while (i>=0 && laGrille[i][y]==pion){
            compteur++;
            i--;
        }
        i = x+1;

        while (i<NB_LIGNES && laGrille[i][y]==pion){
            compteur++;
            i++;
        }
        if (compteur>=2){
            if(laGrille[x-1][y] == VIDE) {
                *bloqueX = x;
                *bloqueY = y;
                return true;
            }
        }

        j = y;
        compteur = 0;

        while (j>=0 && laGrille[x][j]==pion){
            compteur++;
            j--;
        }
        j = y+1;

        while (j<NB_COLONNES && laGrille[x][j]==pion){
            compteur++;
            j++;
        }

        if (compteur>=2){
            if(laGrille[x][y-1] == VIDE) {
                *bloqueX = x;
                *bloqueY = y-1;
            } else if(laGrille[x][j] == VIDE) {
                *bloqueX = x;
                *bloqueY = j;
            }
            return true;
        }
    }
    return false;
}


int maStrategie(t_grille laGrille)
{
    int  x ,y, bloqueX, bloqueY;
    bool aligner;

    for (y = 0; y < NB_COLONNES; y++)
    {
        x = chercherLigne(laGrille, y);

        if(x < NB_LIGNES) x++;

        if(x != -1) {
            aligner = deuxAligner(laGrille, x,y, &bloqueX, &bloqueY, JOUEUR, ADVERSAIRE);
            if(aligner) {
                if(bloqueX < NB_LIGNES && bloqueY < NB_COLONNES && bloqueX > 0 && bloqueY >= 0) {
                    // on verifie qu'il n'y pas rien sous la case ou on veut placer
                    // sinon on place ailleurs
                    if(laGrille[bloqueX+1][bloqueY] != VIDE) {
                        return bloqueY;
                    }
                }
            }
        }
    }

    if(chercherLigne(laGrille, MILLIEU) != -1){
        return MILLIEU;
    } else {
        for (y = 0; y < NB_COLONNES; y++)
        {
            x = chercherLigne(laGrille, y);

            if(x != -1) {
                aligner = deuxAligner(laGrille, x,y, &bloqueX, &bloqueY, JOUEUR, ADVERSAIRE);
                if(aligner) {
                    if(bloqueX < NB_LIGNES && bloqueY < NB_COLONNES && bloqueX > 0 && bloqueY >= 0) {
                        // on verifie qu'il n'y pas rien sous la case ou on veut placer
                        // sinon on place ailleurs
                        if(laGrille[bloqueX+1][bloqueY] != VIDE) {
                            return bloqueY;
                        }
                    }
                }
            }
        }
        // on remplis les colonnes des bords
        for (y = 0; y < NB_COLONNES; y++)
        {
            x = chercherLigne(laGrille, y);

            if(x != -1) {
                if(y == 0 || y == NB_COLONNES-1) {
                    return y;
                }
            } else {
                // on place a l'endroit ou on a aligner deux pions
                for (y = 0; y < NB_COLONNES; y++)
                {
                    x = chercherLigne(laGrille, y);

                    if(x != -1) {
                        aligner = deuxAligner(laGrille, x,y, &bloqueX, &bloqueY, ADVERSAIRE, JOUEUR);
                        if(aligner) {
                            if(bloqueX < NB_LIGNES && bloqueY < NB_COLONNES && bloqueX > 0 && bloqueY >= 0) {
                                // on verifie qu'il n'y pas rien sous la case ou on veut placer
                                // sinon on place ailleurs
                                if(laGrille[bloqueX+1][bloqueY] != VIDE) {
                                    return bloqueY;
                                } else {
                                    y = rand() % NB_COLONNES;
                                    x = chercherLigne(laGrille, y);
                                    while(x == -1) {
                                        y = rand() % NB_COLONNES;
                                        x = chercherLigne(laGrille, y);
                                    }
                                    return y;
                                }
                            } else {
                                y = rand() % NB_COLONNES;
                                x = chercherLigne(laGrille, y);
                                while(x == -1) {
                                    y = rand() % NB_COLONNES;
                                    x = chercherLigne(laGrille, y);
                                }
                                return y;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
    
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
    for(int i = 0; i < NB_LIGNES; i++)
        for(int j = 0; j < NB_COLONNES; j++)
            grille[i][j] = atoi(argv[i * NB_COLONNES + j + 1]);
}
