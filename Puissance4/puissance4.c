/**
*
* \brief Programme permettant de jouer au jeux du puissance 4
*
* \author Enzo Dubocage
*
* \version 1.0
*
* \date 22 Novembre 2022
*
* \bug j'ai oublier de retirer la déclaration de l'entier x dans initGrille() et k dans afficheGrille() et typedef indiceTab que j'ai oublier de retirer aussi
* \bug problemes d'affichage des accents sur windows (utf-8 que je n'ai pas du déclarer)
*
* Ce programme permet de jouer au jeux du puissance 4 a deux joueurs sur un terminal
* On utilise les touches q,d et espace pour jouer
* Il y'a la possibilités de rejouer et le programme respecte la maquette
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//declaration des variables globales (constantes)

/**
*
* \def JAUNE
*
* \brief constante qui permet de definir la couleur jaune dans le tableau
*
*/
const int JAUNE = 1;

/**
*
* \def JAUNE
*
* \brief constante qui permet de definir la couleur rouge dans le tableau
*
*/
const int ROUGE = 2;

/**
*
* \def JAUNE
*
* \brief constante qui permet de definir un espace vide dans le tableau
*
*/
const int VIDE = 0;

/**
*
* \def NB_LIGNES
*
* \brief constante qui permet de definir le nombre de lignes du tableau
*
*/
#define NB_LIGNES 6

/**
*
* \def GAGNE
*
* \brief constante qui permet de definir le nombre de pions alignés pour gagner
*
*/
#define GAGNE 4

/**
*
* \def NB_COLONNES
*
* \brief constante qui permet de definir le nombre de colonnes du tableau
*
*/
#define NB_COLONNES 7

/**
*
* \def NB_DEBUT
*
* \brief constante qui permet de definir le millieu du tableau (pour le placement par défaut des pions)
*
*/
#define NB_DEBUT (NB_COLONNES/2)+1

/**
*
* \typedef tab2D
*
* \brief tableau 2D de 6 lignes et 7 colonnes de type int
*
* Le tab2D est un tableau a deux dimensions qui contient les pions du jeux
* définit par les constantes NB_LIGNES et NB_COLONNES
*
*/
typedef int tab2D[NB_LIGNES][NB_COLONNES];
/**
*
* \typedef top
*
* \brief tableau 1D de 7 cases de type int
*
* Le top est un tableau a une dimension qui permet d'afficher les valeurs du tableau au dessus tableau de jeux
* il permet de déplacer le curseur de placement des pions
*
*/
typedef int top[NB_COLONNES];

tab2D tab;
top topTab;
tab2D winTab;

// entete des fonctions et procedures

void initGrille(tab2D);
void afficher (tab2D, int, int, bool);
bool grillePleine (tab2D);
void jouer(tab2D, int, int*, int*, char[20]);
int choisirColonne (tab2D, int, int, char[20]);
int trouverLigne (tab2D, int);
void initWinner();
bool estVainqueur (tab2D, int, int);
void finDePartie (int ,char[20]);
char verifInput(char[20]);
int main();

//make a doxygen comment for this function

/**
*
* \fn char verifInput(char joueur)
*
* \brief fonction qui permet de verifier l'input du joueur
*
* \param joueur : chaine de caractère qui contient le nom du joueur
*
* \return input : retourne le caractère entré par le joueur
*
* Cette fonction permet de verifier l'input du joueur, si il correspond bien a q,d ou espace et permet d'éviter le retour charriot
*
*/
char verifInput(char joueur[20]) {
    char input;
    scanf("%c", &input);
    while (input != ' ' && input != 'q' && input != 'd') {
        // si c'est le caractere "entrer" (10) on affiche rien et on rescanne
        if(input != 10) {
            printf("\n");
            printf("Erreur, entrée : q pour aller a gauche, d pour aller a droite, espace pour placer ! \n");
            printf("\nTour du joueur %s : ", joueur);
        }
        scanf("%c", &input);
    }
    printf("\n");
    return input;
}

/**
*
* \fn int choisirColonne(tab2D tab, int couleur, int colonne, char nomJoueur[20])
*
* \brief fonction qui permet de choisir la colonne ou placer le pion
*
* \param nomJoueur : chaine de caractère qui contient le nom du joueur
* \param tab : tableau 2D de jeux, de 6 lignes et 7 colonnes de type int
* \param couleur : entier qui permet de definir la couleur du pion
* \param colonne : entier qui permet de definir la colonne ou est deja placer le pion
*
* \return colonne : retourne la colonne ou placer le pion
*
* Cette fonction permet de choisir la colonne ou placer le pion, elle permet de se déplacer a gauche ou a droite de la colonne ou est deja placer le pion
*
*/
int choisirColonne(tab2D tab, int couleur, int colonne, char nomJoueur[20]) {
    char input;
    printf("\nq pour aller a gauche, d pour aller a droite, espace pour placer : ");
    input = verifInput(nomJoueur);
    while(input != ' ') {
        switch (input)
        {
        case 'd':
            // si on est pas a la derniere colonne on peut aller a droite
            if(colonne<NB_COLONNES) {
                colonne++;
                afficher(tab, couleur, colonne, false);
            } else {
                afficher(tab, couleur, colonne, false);
                printf("\nErreur, vous ne pouvez pas aller plus loin de ce coté \n");
            }
            printf("\nTour du joueur %s : ", nomJoueur);
            input = verifInput(nomJoueur);
            break;
        case 'q':
            // si on est pas a la premiere colonne on peut aller a gauche
            if(colonne>1) {
                colonne--;
                afficher(tab, couleur, colonne, false);
            } else {
                afficher(tab, couleur, colonne, false);
                printf("\nErreur, vous ne pouvez pas aller plus loin de ce coté \n");
            }
            printf("\nTour du joueur %s : ", nomJoueur);
            input = verifInput(nomJoueur);
            printf("\n");
            break;
        default:
            break;
        }
    }
    return colonne-1;
}

/**
*
* \fn int trouverLigne(tab2D tab, int colonne)
*
* \brief fonction qui permet de trouver la ligne ou placer le pion
*
* \param tab : tableau 2D de jeux, de 6 lignes et 7 colonnes de type int
* \param colonne : entier qui permet de definir la colonne ou on veut placer le pion
* \return ligne : retourne la ligne ou placer le pion ou -1 si impossible
*
* Cette fonction permet de trouver la ligne ou placer le pion, elle permet de verifier si la colonne est pleine
*
*/
int trouverLigne(tab2D tab, int colonne) {
    int i;
    // on parcours le tableau a l'envers pour ajouter le pion en bas de la colonne
    for(i=NB_LIGNES-1; i>=0; i--) {
        if(tab[i][colonne] == VIDE) {
            return i;
        }
    }
    return -1;
}

/**
*
* \fn void finDePartie(int couleur, char joueur)
*
* \brief fonction qui permet d'afficher le vainqueur/égaliter et de relancer une partie/termier le programme
*
* \param couleur : entier qui permet de definir la couleur du pion gagnant
* \param joueur : chaine de caractère qui contient le nom du joueur
*
* Cette fonction permet d'afficher le vainqueur/égaliter et de relancer une partie/termier le programme
*
*/
void finDePartie(int couleur, char joueur[20]) {
    char input;
    if(couleur == ROUGE) {
        printf("%s Rouge a gagné, voulez-vous rejouer ? (y/n) !\n", joueur);
    } else if (couleur == JAUNE) {
        printf("%s Jaune a gagné, voulez-vous rejouer ? (y/n) !\n", joueur);
    } else {
        printf("Aucun vainqueur, il y a égalité, voulez-vous rejouer ? (y/n) :");
    }

    scanf("%c",&input);
    printf("\n");

    while (input != 'y' && input != 'n') {
        // si c'est le caractere "entrer" (10) on affiche rien et on rescanne
        if(input != 10) {
            printf("Entrer y ou n ! (yes/no): ");
        }
        scanf("%c", &input);
        printf("\n");
    }

    switch (input) {
        case 'y':
            // on relance le jeu
            main();
            break;
        case 'n':
            // on quitte le programme (equivalant au return EXIT_SUCCESS)
            exit(0);
            break;
        default:
            break;
    }

}

/**
*
* \fn bool estVainqueur(tab2D tab, int colonne, int ligne)
*
* \brief fonction qui permet de verifier si le joueur a gagné
*
* \param tab : tableau 2D de jeux, de 6 lignes et 7 colonnes de type int
* \param colonne : entier qui permet de definir la colonne ou est placer le pion
* \param ligne : entier qui permet de definir la ligne ou est placer le pion
* \return bool : retourne true si le joueur a gagné, false sinon
*
* Cette fonction permet de verifier si le joueur a gagné, elle permet de verifier si il y a 4 pions de la meme couleur alignés verticalement, horizontalement ou en diagonale
* Elle permet aussi d'écrire dans le tableau winTab les pions gagnants pour afficher leur contours en vert
* \note : cette fonction est appelé a chaque fois qu'un pion est placer
*
*/
bool estVainqueur(tab2D tab, int colonne, int ligne) {
    initWinner();
    int i, compteur, couleur;
    couleur = tab[ligne][colonne];
    compteur = 1;
    winTab[ligne][colonne] = couleur;

    // on verifie si il y a GAGNE pions de la meme couleur alignés verticalement
    for (i = 1; i < GAGNE; i++) 
    {
        // si on est pas a la derniere ligne et que la couleur du pion est la meme que celle du pion en dessous on ajoute 1 au compteur
        if (colonne - i >= 0 && tab[ligne][colonne - i] == couleur) 
        {
            compteur++;
            winTab[ligne][colonne - i] = couleur;
        }
        // si on est pas a la premiere ligne et que la couleur du pion est la meme que celle du pion au dessus on ajoute 1 au compteur
        if (colonne + i < NB_COLONNES && tab[ligne][colonne + i] == couleur) 
        {
            compteur++;
            winTab[ligne][colonne + i] = couleur;
        }
        if (compteur == GAGNE) 
        {
            return true;
        }
    }

    compteur = 1;

    // on verifie si il y a GAGNE pions de la meme couleur alignés horizontalement
    for (i = 1; i < GAGNE; i++) 
    {
        // si on est pas a la premiere ligne et que la couleur du pion est la meme que celle du pion a gauche on ajoute 1 au compteur
        if (ligne - i >= 0 && tab[ligne - i][colonne] == couleur) 
        {
            compteur++;
            winTab[ligne - i][colonne] = couleur;
        }
        // si on est pas a la derniere ligne et que la couleur du pion est la meme que celle du pion a droite on ajoute 1 au compteur
        if (ligne + i < NB_LIGNES && tab[ligne + i][colonne] == couleur) 
        {
            compteur++;
            winTab[ligne + i][colonne] = couleur;
        }
        if (compteur == GAGNE) 
        {
            return true;
        }
    }

    compteur = 1;

    // on verifie si il y a GAGNE pions de la meme couleur alignés en diagonale (haut gauche vers bas droite)
    for (i = 1; i < GAGNE; i++) 
    {
        // si on est pas a la premiere ligne ni colonne et que la couleur du pion est la meme que celle du pion en haut a gauche on ajoute 1 au compteur
        if (ligne - i >= 0 && colonne - i >= 0 && tab[ligne - i][colonne - i] == couleur) 
        {
            compteur++;
            winTab[ligne - i][colonne - i] = couleur;
        }
        // si on est pas a la derniere ligne ni colonne et que la couleur du pion est la meme que celle du pion en bas a droite on ajoute 1 au compteur
        if (ligne + i < NB_LIGNES && colonne + i < NB_COLONNES && tab[ligne + i][colonne + i] == couleur) 
        {
            compteur++;
            winTab[ligne + i][colonne + i] = couleur;
        }
        if (compteur == GAGNE) 
        {
            return true;
        }
    }
    compteur = 1;

    // on verifie si il y a GAGNE pions de la meme couleur alignés en diagonale (haut droite vers bas gauche)
    for (i = 1; i < GAGNE; i++) 
    {
        // si on est pas a la premiere ligne ni derniere colonne et que la couleur du pion est la meme que celle du pion en haut a droite on ajoute 1 au compteur
        if (ligne - i >= 0 && colonne + i < NB_COLONNES && tab[ligne - i][colonne + i] == couleur) 
        {
            compteur++;
            winTab[ligne - i][colonne + i] = couleur;
        }
        // si on est pas a la derniere ligne ni premiere colonne et que la couleur du pion est la meme que celle du pion en bas a gauche on ajoute 1 au compteur
        if (ligne + i < NB_LIGNES && colonne - i >= 0 && tab[ligne + i][colonne - i] == couleur) 
        {
            compteur++;
            winTab[ligne + i][colonne - i] = couleur;
        }
        if (compteur == GAGNE) 
        {
            return true;
        }
    }
    
    return false;

}

/**
*
* \fn void jouer(tab2D tab, int couleur, int* colonne, int* ligne, char joueur)
*
* \brief Fonction qui permet de jouer un pion
*
* \param tab : tableau de jeu (2D) 
* \param couleur : couleur du pion a jouer
* \param colonne : colonne qui prendra en valeur le résultat de choisirColonne (entrée/sortie)
* \param ligne : ligne qui prendra en valeur le résultat de trouverLigne (entrée/sortie)
* \param joueur : nom du joueur
*
* Cette fonction permet de jouer un pion en appelant les fonctions choisirColonne et trouverLigne et en redemandant la colonne/ligne si la colonne choisie est pleine
*
*/
void jouer(tab2D tab, int couleur, int* colonne, int* ligne, char joueur[20]) {
    *colonne = choisirColonne(tab, couleur, NB_DEBUT, joueur);
    *ligne = trouverLigne(tab, *colonne);
    if(*ligne == -1) {
        printf("Erreur, colonne pleine, veuillez recommencer (vous reprendrez a la colonne %d) !\n", NB_DEBUT);
        jouer(tab, couleur, colonne, ligne, joueur);
    } else {
        tab[*ligne][*colonne] = couleur;
    }
}

/**
*
* \fn void afficher(tab2D tab, int joueur, int colonne, bool win)
*
* \brief Fonction qui permet d'afficher le tableau de jeu
*
* \param tab : tableau de jeu (2D)
* \param joueur : prochain joueur a jouer (couleur)
* \param colonne : colonne du prochain pion a jouer 
* \param win : booléen qui indique si le dernier pion joué a gagné la partie
*
* Cette fonction permet d'afficher le tableau de jeu avec les pions et les numéros de colonnes
* Elle affiche aussi le prochain joueur a jouer et la colonne du prochain pion a jouer
* Si win vaut vraie, elle affiche la combinaison gagnante en vert
*
*/
void afficher(tab2D tab, int joueur, int colonne, bool win)
{
    int i,j,x,k;
    // on affiche le sur tableau qui permet de séléctionner la colonne
    for (j = 0; j < 2; j++)
    {
        for (i = 1; i <= NB_COLONNES; i++) {
            if(i == colonne)
            {
                if(joueur == JAUNE) {
                    printf("\033[33m ##### \033[0m");
                } else {
                    printf("\033[31m ##### \033[0m");
                }
            }
            else if(j == 1) {
                printf("\033[1;34m   %d   \033[0m", i);
            }
            else {
                printf("       ");
            }
        }
       printf("\n"); 
    }

    // on affiche le tableau de jeu
    for (i = 0; i < NB_LIGNES; i++)
    {
        printf("\033[1;34m|-----------------------------------------------|\033[0m\n");
        for (x = 0; x < 2; x++)
        {
            for (j = 0; j < NB_COLONNES; j++)
            {
                if(tab[i][j] == VIDE)
                {
                    printf("\033[1;34m|\033[0m");
                    printf("\033[37m#####\033[0m");
                    printf("\033[1;34m|\033[0m");
                }
                else if(tab[i][j] == JAUNE) {
                    if(win && winTab[i][j] == JAUNE) {
                        printf("\033[1;32m|\033[0m");
                        printf("\033[33m#####\033[0m");
                        printf("\033[1;32m|\033[0m");
                    } else {
                        printf("\033[1;34m|\033[0m");
                        printf("\033[33m#####\033[0m");
                        printf("\033[1;34m|\033[0m");
                    }
                }
                else if(tab[i][j] == ROUGE) {
                    if(win && winTab[i][j] == ROUGE) {
                        printf("\033[1;32m|\033[0m");
                        printf("\033[31m#####\033[0m");
                        printf("\033[1;32m|\033[0m");
                    } else {
                        printf("\033[1;34m|\033[0m");
                        printf("\033[31m#####\033[0m");
                        printf("\033[1;34m|\033[0m");
                    }
                }
            }
            printf("\n");
        }
    }
    printf("\033[1;34m|-----------------------------------------------|\033[0m\n");

}

/**
*
* \fn bool grillePleine(tab2D tab) 
*
* \brief Fonction qui permet de savoir si la grille est pleine
*
* \param tab : tableau de jeu (2D)
*
* \return bool : vrai si la grille est pleine, faux sinon
*
* Cette fonction permet de savoir si la grille est pleine en parcourant le tableau de jeu
*
*/       
bool grillePleine(tab2D tab) {
    int i, j;

    for(i=0;i<NB_LIGNES;i++){
        for(j=0;j<NB_COLONNES;j++){
            if(tab[i][j] == VIDE){
                // printf("%d",tab[i][j] );
                return false;
            }
        }
    }
    return true; 
}

/**
*
* \fn void initGrille(tab2D tab)
*
* \brief Fonction qui permet d'initialiser la grille de jeu
*
* \param tab : tableau de jeu (2D)
*
* Cette fonction permet d'initialiser la grille de jeu en mettant toutes les cases a VIDE
* Elle initialise aussi le tableau topTab qui permet d'afficher le sur tableau qui permet de séléctionner la colonne
*
*/    
void initGrille(tab2D tab){
    int i;
    int j;
    int x;
    // on initialise le tableau de jeu à 0
    for(i=0;i<NB_LIGNES;i++){
        for(j=0;j<NB_COLONNES;j++){
            tab[i][j] = VIDE;
        }
    }
    // on initialise le sur tableau à 0
    for(i=0;i<NB_COLONNES;i++){
        topTab[i] = VIDE;
    }
}

/**
*
* \fn void initWinner()
*
* \brief Fonction qui permet d'initialiser le tableau winTab
*
* Cette fonction permet d'initialiser le tableau winTab qui permet d'afficher la combinaison gagnante en vert (c'est un deuxieme tableau de jeux qui contient uniquement les pions gagnant)
*
*/    
void initWinner() {
    int i,j;
    // on initialise le tableau d'indice gagnant à 0
    for(i=0;i<NB_LIGNES;i++){
        for(j=0;j<NB_COLONNES;j++){
            winTab[i][j] = VIDE;
        }
    }
}

/**
*
* \fn int main()
*
* \brief Fonction principale du programme
*
* \return int : 0 si le programme s'est bien executé
*
* Cette fonction permet de demander le nom des joueurs, de lancer le jeu et de gérer les tours de jeu des joueurs
*
*/
int main()
{
    int vainqueur;
    char vainqueurNom[20];
    char joueur1[20];
    char joueur2[20];
    int ligne,colonne;
    tab2D g;
    bool win;    
    win = false;
    initGrille(g);
    vainqueur = VIDE;

    printf("______ _   _ _____ _____ _____  ___  _   _ _____ _____     ___\n");
    printf("| ___ \\ | | |_   _/  ___/  ___|/ _ \\| \\ | /  __ \\  ___|   /   |\n");
    printf("| |_/ / | | | | | \\ `--.\\ `--./ /_\\ \\  \\| | /  \\/ |__    / /| |\n");
    printf("|  __/| | | | | |  `--. \\`--. \\  _  | . ` | |   |  __|  / /_| |\n");
    printf("| |   | |_| |_| |_/\\__/ /\\__/ / | | | |\\  | \\__/\\ |___  \\___  |\n");
    printf("\\_|    \\___/ \\___/\\____/\\____/\\_| |_|_| \\_/\\____|____/      |_/\n\n\n");

    printf("Nom du joueur 1 (Rouge) : ");
    scanf("%s", joueur1);
    printf("Nom du joueur 2 (Jaune) : ");
    scanf("%s", joueur2);

    // on verifie que le nom ne dépasse pas 20
    while(strlen(joueur1) > 20) {
        printf("Erreur : Le nom entrée doit être un chaine de caractère et être inférieur à 20 caractères.\n");
        printf("Nom du joueur 1 (Rouge) : ");
        scanf("%s", joueur1);
    }
    while( strlen(joueur2) > 20) {
        printf("Erreur : Le nom entrée doit être un chaine de caractère et être inférieur à 20 caractères.\n");
        printf("Nom du joueur 2 (Jaune) : ");
        scanf("%s", joueur2);
    }

    printf("\n");

    afficher(g, ROUGE, NB_DEBUT, win);
    while(vainqueur == VIDE && !grillePleine(g)) {
        jouer(g, ROUGE, &colonne, &ligne, joueur1);
        afficher(g, JAUNE, NB_DEBUT, win);
        win = estVainqueur(g, colonne, ligne);
        if(win) {
            vainqueur = ROUGE;
        } else if (!grillePleine(g)) {
            jouer(g, JAUNE, &colonne, &ligne, joueur2);
            afficher(g, ROUGE, NB_DEBUT, win);
            win = estVainqueur(g, colonne, ligne);
            if(win) {
                vainqueur = JAUNE;
            }
            
        }
    }
    afficher(g, ROUGE, NB_DEBUT, win);
    finDePartie(vainqueur, vainqueurNom);
    return EXIT_SUCCESS;
}