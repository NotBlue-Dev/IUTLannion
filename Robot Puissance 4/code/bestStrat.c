#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <windows.h>
#include <time.h>

#define NB_LIGNES 6
#define NB_COLONNES 7
#define DEBUT (NB_COLONNES / 2)

typedef int t_grille[NB_LIGNES][NB_COLONNES];

int trouveColonne(t_grille laGrille, int lePion);
int aleatoire(t_grille laGrille, int x, int lePion);
int PossibGagnant(t_grille laGrille, int *alX, int *alY, int *lePion);
int TroisAligner(t_grille laGrille, int x, int y, int *alX, int *alY, int *lePion);
int main(int argc, char** argv);
void chargerGrille(char** argv, t_grille grille);
int chercherLigne(t_grille laGrille, int col);
bool choixGDTop(t_grille laGrille2, int x, int i, int lePion);
bool estVainqueur(t_grille laGrille, int lig, int col);
int peutGagner(t_grille laGrille, char pion);
int compterAlignesColonne(t_grille laGrille, int colonne, int ligne, char pion);
int compterAlignesLigne(t_grille laGrille, int ligne, int colonne, char pion);
int compterAlignesLigneDG(t_grille laGrille, int ligne, int colonne, char pion);
bool colonne_pleine(t_grille laGrille, int colonne);

const int VIDE = 0;
const int JOUEUR = 1;
const int ADVERSAIRE = 2;

bool colonne_pleine(t_grille laGrille, int colonne) {
  if (laGrille[0][colonne] != VIDE) {
    return true;
  }
  return false;
}

int compterAlignesColonne(t_grille laGrille, int colonne, int ligne, char pion) {
    int cpt;
    cpt = 0;
    while (((ligne < NB_LIGNES-1) && (laGrille[ligne][colonne] != pion && laGrille[ligne][colonne] != VIDE) && colonne_pleine(laGrille, colonne) == false)) {
        cpt++;
        ligne--;
    }
    if (cpt != 1){
        if (laGrille[ligne][colonne]  == VIDE){
            return cpt;
        }
    }
    return -1;
}

int compterAlignesLigne(t_grille laGrille, int ligne, int colonne, char pion) {
    int i = colonne;
    int nbAlignes = 0;
    while (i <= NB_COLONNES && (laGrille[ligne][i] != pion && laGrille[ligne][i] != VIDE)) {
        nbAlignes++;
        i++;
    }
    if(nbAlignes != 1){
        if(laGrille[ligne][i] == VIDE){
            return nbAlignes;
        }
    }
    return-1;
}

int compterAlignesLigneDG(t_grille laGrille, int ligne, int colonne, char pion) {
    int i = colonne;
    int nbAlignes = 0;
    while (i >= 0 && (laGrille[ligne][i] != pion && laGrille[ligne][i] != VIDE)) {
        nbAlignes++;
        i--;
    }
    if(nbAlignes != 1){
        if(laGrille[ligne][i] == VIDE){
            return nbAlignes;
        }
    }
    return-1;
}

int peutGagner(t_grille laGrille, char pion){
    int i,j, gagne_ligneGD, gagne_ligneDG, gagne_colonne;
    int colonne_gagnante = -1;
    for (i = NB_LIGNES-1; i >= 0; i--) {
        for (j = 0; j <= NB_COLONNES; j++) {
            gagne_ligneGD = compterAlignesLigne(laGrille, i, j, pion);
            if(gagne_ligneGD == 3 && laGrille[i][j+1] == VIDE){
                colonne_gagnante = j + gagne_ligneGD;
            }
            gagne_ligneDG = compterAlignesLigneDG(laGrille, i, j, pion);
            if(gagne_ligneDG == 3 && laGrille[i][j-1] == VIDE){
                colonne_gagnante = j - gagne_ligneDG;
            }
            gagne_colonne = compterAlignesColonne(laGrille, i, j, pion);
            if (gagne_colonne == 3 && laGrille[i-1][gagne_colonne] == VIDE){
                colonne_gagnante = j;
            }
        }
    }
    return colonne_gagnante;
}

// renvoie true si 3 pions aligner et renvoie les coordonnées ou placer le 4eme pion pour bloquer
int TroisAligner(t_grille laGrille, int x, int y, int *alX, int *alY, int *lePion) {
    if(laGrille[x][y] != VIDE && laGrille[x][y] != JOUEUR) {
        *lePion = laGrille[x][y];
        int cpt1,i,j,cpt2;
        i = x;
        // deux compteur pour compter le nombre de pions au Nord et au Sud / Est et Ouest
        cpt1 = 0;
        cpt2 = 0;
        // regarder la verticale, en comptant le nombre de pions au Nord et au Sud
        while (i>=0 && laGrille[i][y]==*lePion){
            cpt1++;
            i--;
        }
        i = x+1;

        while (i<NB_LIGNES && laGrille[i][y]==*lePion){
            cpt2++;
            i++;
        }
        if (cpt1+cpt2>=3){
            // si on a 3 pions alignés, on regarde si le 4eme pion est vide (NORD OU SUD)
            if(laGrille[x-1][y] == VIDE) {
                // on rend les coordonnées du 4eme pion
                *alX = x;
                *alY = y;
                return true;
            }
            //recuperer les coordonnées du futur 4eme pion (VIDE)
        }

        // regarder l'horizontale, en comptant le nombre de pions à l'Est et à l'Ouest
        j = y;
        cpt1 = 0;
        cpt2 = 0;
        // on regarde à l'est
        while (j>=0 && laGrille[x][j]==*lePion){
            cpt1++;
            j--;
        }
        j = y+1;
        // on regarde à l'ouest
        while (j<NB_COLONNES && laGrille[x][j]==*lePion){
            cpt2++;
            j++;
        }

        if (cpt1+cpt2>=3){
            // si on a 3 pions alignés, on regarde si le 4eme pion est vide (EST OU OUEST)
            if(laGrille[x][y-1] == VIDE) {
                // on rend les coordonnées du 4eme pion
                *alX = x;
                *alY = y-1;
            } else if(laGrille[x][j] == VIDE) {
                // on rend les coordonnées du 4eme pion
                *alX = x;
                *alY = j;
            }
            return true;
        }
        // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
        i = x;
        j = y;
        cpt1 = 0;
        cpt2 = 0;
        // on regarde au Nord Ouest
        while (j>=0 && i>=0 && laGrille[i][j]==*lePion){
            cpt1++;
            i--;
            j--;
        }
        i = x+1;
        j = y+1;
        // on regarde au Sud Est
        while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==*lePion){
            cpt2++;
            i++;
            j++;
        }
        if (cpt1+cpt2>=3){
            // si on a 3 pions alignés, on regarde si le 4eme pion est vide (EST OU OUEST)
            if(laGrille[i+1][j+1] == VIDE) {
                // on rend les coordonnées du 4eme pion
                *alX = i+1;
                *alY = j+1;
            } else if(laGrille[x-cpt1][y-cpt1] == VIDE) {
                // on rend les coordonnées du 4eme pion
                *alX = x-cpt1;
                *alY = y-cpt1;
            }
            return true;
        }
        // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
        i = x;
        j = y;
        cpt1 = 0;
        cpt2 = 0;
        // on regarde au Nord Est
        while (j<NB_COLONNES && i>=0 && laGrille[i][j]==*lePion){
            cpt1++;
            i--;
            j++;
        }
        i = x+1;
        j = y-1;
        // on regarde au Sud Ouest
        while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==*lePion){
            cpt2++;
            i++;
            j--;
        }
        if (cpt1+cpt2>=3){
            // si on a 3 pions alignés, on regarde si le 4eme pion est vide (EST OU OUEST)
            if(laGrille[i+1][j-1] == VIDE) {
                // on rend les coordonnées du 4eme pion
                *alX = i+1;
                *alY = j-1;
            } else if(laGrille[x-cpt1][y+cpt1] == VIDE) {
                // on rend les coordonnées du 4eme pion
                *alX = x-cpt1;
                *alY = y+cpt1;
            }
            return true;
        }
    }
    return false;
}

// Fonction qui sert a verifier si il faut bloquer en utilisant la fonction TroisAligner
// la fonction TroisAligner ne verifie qu'a partir d'un pion donc on parcours tout les pions enemies en haut des lignes
int PossibGagnant(t_grille laGrille, int *alX, int *alY, int *lePion) {
    int y,x;                                                
    bool aligner;

    for (y = 0; y < NB_COLONNES; y++)
    {
        x = chercherLigne(laGrille, y);

        //on veut check les pions d'en dessous de la ligne rendu (car elle est vide)
        if(x < NB_LIGNES) x++;

        if(x != -1) {
            aligner = TroisAligner(laGrille, x,y, &(*alX), &(*alY), &(*lePion));
            if(aligner) {
                return aligner;
            }
            // on check encore une ligne en dessous au cas ou un pion sois encercler (ex diagonale)
            if(x++ < NB_LIGNES && !aligner) {
                aligner = TroisAligner(laGrille, x++,y, &(*alX), &(*alY), &(*lePion));
                if(aligner) {
                    return aligner;
                }
            }
        }
    }
    return false;
}

// Fonction qui sert renvoie une colonne aléatoire en verifiant que cette colonne ne permet pas la victoire a l'ennemie
int aleatoire(t_grille laGrille2, int x, int lePion) {
    int random,y,safe;
    bool win;
    safe = 0;

    random = rand() % NB_COLONNES;
    y = chercherLigne(laGrille2, random);
    win = choixGDTop(laGrille2, x, random, lePion);
    // tant que ca risque de faire gagner l'ennemie ou que la colonne est pleine
    while(win || y == -1) {
        random = rand() % NB_COLONNES;
        y = chercherLigne(laGrille2, random);
        win = choixGDTop(laGrille2, x, random, lePion);
        //safe lock (apres 3*NB_COLONNES essais on renvoie une colonne random peut importe si elle fais win)
        if(safe>NB_COLONNES*3) {
            return random;
        }
        safe++;
    }

    return random;
}

// permet de choisir la colonne ou jouer (a gauche/droite du pion, en haut du pion, ou aléatoire) tout en verifiant que cette colonne ne permet pas la victoire a l'ennemie
int trouveColonne(t_grille laGrille2, int lePion) {
    int i, x, peut_gagner;
    bool win;

    for(i = 0; i < NB_COLONNES; i++) {
        x = chercherLigne(laGrille2, i)+1;
        if(x-1 != -1) {
            // on cherche un emplacement ou on a un de nos pions
            if(laGrille2[x][i] == JOUEUR) {
                // a gauche
                peut_gagner = peutGagner(laGrille2, lePion);
                if(peut_gagner != -1){
                    return peut_gagner;
                }

                if(i != 0 && laGrille2[x][i-1] == VIDE) {
                    win = choixGDTop(laGrille2, x, i-1, lePion);
                    if(!win) {
                        return i-1;
                    } else {
                        // au dessus
                        win = choixGDTop(laGrille2, x, i, lePion);
                        if(!win && laGrille2[x][i] == VIDE) {
                            return i;
                        } else {
                            //aléatoire
                            win = choixGDTop(laGrille2, DEBUT, i, lePion);
                            if(!win && laGrille2[x][DEBUT] == VIDE) {
                                return i;
                            } else {
                                return aleatoire(laGrille2, x, lePion);
                            }
                        }
                    }
                } else if (i != NB_COLONNES && laGrille2[x][i+1] == VIDE) {
                    peut_gagner = peutGagner(laGrille2, lePion);
                    if(peut_gagner != -1){
                        return peut_gagner;
                    }
                    // a droite
                    win = choixGDTop(laGrille2, x, i+1, lePion);
                    if(!win) {
                        return i+1;
                    } else {
                        // au dessus
                        win = choixGDTop(laGrille2, x, i, lePion);
                        if(win && laGrille2[x][i] == VIDE) {
                            return i;
                        } else {
                            //aléatoire
                            win = choixGDTop(laGrille2, DEBUT, i, lePion);
                            if(!win && laGrille2[x][DEBUT] == VIDE) {
                                return i;
                            } else {
                                return aleatoire(laGrille2, x, lePion);
                            }
                        }
                    }
                } else {
                    // au dessus
                    peut_gagner = peutGagner(laGrille2, lePion);
                    if(peut_gagner != -1){
                        return peut_gagner;
                    }
                    win = choixGDTop(laGrille2, x, i, lePion);
                    if(!win && laGrille2[x][i] == VIDE) {
                        return i;
                    } else {
                        //aléatoire
                        win = choixGDTop(laGrille2, DEBUT, i, lePion);
                        if(!win && laGrille2[x][DEBUT] == VIDE) {
                            return i;
                        } else {
                            return aleatoire(laGrille2, x, lePion);
                        }
                    }
                }
            }
        }
    }
    // si rien ne rentre dans nos conditions on prend la premiere colonne dispo
    int u;
    for (u = 0; u < NB_COLONNES; u++)
    {
        x = chercherLigne(laGrille2, u);
        if(x != -1) {
            return u;
        }
    }
    // si la grille est pleine on renvoie -5 pour dire que la grille est pleine
    return -5;
}

// Verifie que le move envoyer ne fais pas gagner l'ennemie
bool choixGDTop(t_grille laGrille2, int x, int i, int lePion) {
    laGrille2[x][i] = JOUEUR;
    bool win = false;
    int y,j;
    for(y = 0; y<NB_COLONNES; y++) {
        j = chercherLigne(laGrille2, y);
        laGrille2[j][y] = lePion;
        if(estVainqueur(laGrille2, j,y)) {
            win = true;
        }
        laGrille2[j][y] = VIDE;
    }
    return win;
}

/*
    Premier tour : on placer le pion au centre
 
    Tous les autres tours :
    si 3 pions alignés par l'adversaire alors : 
        on bloque (si on peut)
    Sinon : 
        Si placer notre pion à gauche/droite de notre dernier pion placé ne fais pas gagner l’adversaire (4 pions alignés) alors:
            on place le pion
        Sinon :
            Si placer notre pion a au dessus d’un de nos pions placé ne fais pas gagner l’adversaire (4 pions alignés) alors:
            on place le pion
        Sinon : 
            Si placer notre pion au centre de la grille ne fait pas gagner l’adversaire (4 pions alignés) alors:
            on place le pion
        Sinon : 
            tant que notre pion placé aléatoirement permet victoire ennemie :
                on essaye un autre endroit où on pourrait le placer (sans essayer les endroits déjà tentés)
            fin tant que
            on place le pion
        Fin si
    Fin si
*/

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

int maStrategie(t_grille laGrille)
{
    // TODO: Votre strategie de victoire. La seule fonction que vous aurez à modifier.
    // libre à vous d'en créer d'autres pour aérer votre code. 
    // La variable grille est un tableau à deux dimensions d'entiers, c'est la grille du tour. 
    // Un VIDE représente une case vide, 1 représente vos jetons et 2 représente les jetons adverses.
    // A vous de choisir le meilleur prochain coup !
// on créer une copie de la grille pour ne pas la modifier
    t_grille laGrille2;
    int i,j;
    for (i = 0; i < NB_LIGNES; i++)
    {
        for (j = 0; j < NB_COLONNES; j++)
        {
            laGrille2[i][j] = laGrille[i][j];
        }
    }

    // chaque pion placer = un tour
    int tour = 0;

    for (i = 0; i < NB_LIGNES; i++)
    {
        for (j = 0; j < NB_COLONNES; j++)
        {
            if(laGrille[i][j] != VIDE) {
                tour++;
            }
        }
    }

    int alX, alY;   
    alX = 0;
    alY = 0;                                                
    int lePion;
    bool aligner;
    aligner = PossibGagnant(laGrille2, &alX, &alY, &lePion);

    if(tour < 2) {
        return DEBUT;
    } else {
        if(aligner) {
            // on bloque (si on peut)
            if(alX < NB_LIGNES && alY < NB_COLONNES && alX > 0 && alY >= 0) {
                // on verifie qu'il n'y pas rien sous la case ou on veut placer
                // sinon on place ailleurs
                if(laGrille2[alX+1][alY] != VIDE) {
                    return alY;
                } else {
                    return trouveColonne(laGrille2, lePion);
                }
            } else {
                return trouveColonne(laGrille2, lePion);
            }
        } else {
            return trouveColonne(laGrille2, lePion);
        }  
    }
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
