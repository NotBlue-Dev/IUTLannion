#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <unistd.h>
#include <windows.h>
#include <time.h>

// les constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define DEBUT (NB_COLONNES/2)
#define VIDE ' '
#define INCONNU ' '


//bloque couille des fois

const int N = 50;

// les types
typedef int Grille[NB_LIGNES][NB_COLONNES];

// prototypes des fonctions
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void faireJouerA(Grille laGrille, char pion, int * ligne, int * colonne);
void faireJouerB(Grille laGrille, char pion, int * ligne, int * colonne);
int choisirColonne(Grille laGrille, char pion);
int choisirColonneStrategie1(Grille laGrille, char pion);
int choisirColonneStrategie2(Grille laGrille, char pion);
int choisirColonneStrategie3(Grille laGrille, char pion);
int choisirColonneStrategie4(Grille laGrille, char pion);
int choisirColonneStrategieBest(Grille laGrille, char pion);
int trouveColonne(Grille laGrille, char pion, char lePion);
int aleatoire(Grille laGrille, int x, char pion, char lePion);
int PossibGagnant(Grille laGrille, char pion, int *alX, int *alY, char *lePion);
int TroisAligner(Grille laGrille, char pion, int x, int y, int *alX, int *alY, char *lePion);
int chercherLigne(Grille laGrille, int col);
bool estVainqueur(Grille laGrille, int lig, int col);
bool choixGDTop(Grille laGrille2, int x, char pion, int i, char lePion);
void finDePartie(char vainqueur);

int equal = 0;

// Programme principal. C'est le pion A qui commence à jouer
int main()
{
    int winX = 0;
    int winO = 0;

    int i;
    for (i = 0; i < N; i++)
    {
        srand(time(NULL));
        int nbPionsX, nbPionsO;
        nbPionsO = 0;
        nbPionsX = 0;
        Grille laGrille;
        char vainqueur=INCONNU;
        int ligne, colonne;
        initGrille(laGrille);
        afficher(laGrille, PION_A);
 
        while (vainqueur==INCONNU && !grillePleine(laGrille)){
            faireJouerA(laGrille, PION_A, &ligne, &colonne);
            afficher(laGrille, PION_B);
            nbPionsX++;
            if (estVainqueur(laGrille, ligne, colonne) ){
                vainqueur = PION_A;
                winX++;
            } else if (!grillePleine(laGrille)){
                faireJouerB(laGrille, PION_B, &ligne, &colonne);
                afficher(laGrille, PION_A);
                nbPionsO++;
                if (estVainqueur(laGrille, ligne, colonne) ){
                    vainqueur = PION_B;
                    winO++;
                }
            }
            printf("%d", i);
        }
        finDePartie(vainqueur);
        printf("X:%d O:%d \n", nbPionsX, nbPionsO);
        
    }
    Sleep(5000);
    printf("joueur X : %d victoires \n", winX);
    printf("joueur O : %d victoires \n", winO);
    printf("%d parties nulles \n", equal);
    system(EXIT_SUCCESS);
}


void initGrille(Grille laGrille){
    int l, c;
    for (l=0 ; l<NB_LIGNES ; l++){
        for (c=0 ; c<NB_COLONNES ; c++){
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion){
    int l, c;
    system("cls");  // changer en "clear" sur Linux
    printf("\t");
    printf("  %c\n", pion);
    printf("\t\xDA");
    for (c=0; c<NB_COLONNES-1 ; c++){
        printf("\xC4\xC4\xC4\xC2");
    }
    printf("\xC4\xC4\xC4\xBF\n");
    for (l=0 ; l<NB_LIGNES-1 ; l++){
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("\xB3 %c ", laGrille[l][c]);
        }
        printf("\xB3\n");
        printf("\t\xC3");
        for (c=0; c<NB_COLONNES-1 ; c++){
            printf("\xC4\xC4\xC4\xC5");
        }
        printf("\xC4\xC4\xC4\xB4\n");
    }
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
        printf("\xB3 %c ", laGrille[l][c]);
    }
    printf("\xB3\n");
    printf("\t\xC0");
    for (c=0; c<NB_COLONNES-1 ; c++){
        printf("\xC4\xC4\xC4\xC1");
    }
    printf("\xC4\xC4\xC4\xD9\n");
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
        printf("  %d ", c);
    }
    printf("\n\n");
}

bool grillePleine(Grille laGrille){
    bool plein = true;
    int c = 0;
    while (plein && c<NB_COLONNES){
        if (laGrille[0][c] == VIDE){
            plein = false;
        }
        c++;
    }
    return plein;
}

bool choixGDTop(Grille laGrille2, int x, char pion, int i, char lePion) {
    laGrille2[x][i] = pion;
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

void faireJouerA(Grille laGrille, char pion, int * ligne, int * colonne ) {
   *ligne = -1;
    do {
        *colonne = choisirColonne(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);
    laGrille[*ligne][*colonne] = pion;
}

void faireJouerB(Grille laGrille, char pion, int * ligne, int * colonne ) {
    *ligne = -1;
    do {
        *colonne = choisirColonneStrategieBest(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);

    laGrille[*ligne][*colonne] = pion;
}

int choisirColonneStrategie2(Grille laGrille, char pion) {
    int i,max,maxInd,tmp;
    max = chercherLigne(laGrille, 0);
    maxInd = 0;
    for (i = 1; i < NB_COLONNES; i++)
    {
        tmp = chercherLigne(laGrille,i);
        if(tmp>max) {
            max = tmp;
            maxInd = i;
        }
    }
    return maxInd;
}

// renvoie true si 3 pions aligner et renvoie les coordonnées ou placer le 4eme pion pour bloquer
int TroisAligner(Grille laGrille, char pion, int x, int y, int *alX, int *alY, char *lePion) {
    if(laGrille[x][y] != VIDE && laGrille[x][y] != pion) {
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
int PossibGagnant(Grille laGrille, char pion, int *alX, int *alY, char *lePion) {
    int y,x;                                                
    bool aligner;

    for (y = 0; y < NB_COLONNES; y++)
    {
        x = chercherLigne(laGrille, y);

        //on veut check les pions d'en dessous de la ligne rendu (car elle est vide)
        if(x < NB_LIGNES) x++;

        if(x != -1) {
            aligner = TroisAligner(laGrille, pion, x,y, &(*alX), &(*alY), &(*lePion));
            if(aligner) {
                return aligner;
            }
            // on check encore une ligne en dessous au cas ou un pion sois encercler (ex diagonale)
            if(x++ < NB_LIGNES && !aligner) {
                aligner = TroisAligner(laGrille, pion, x++,y, &(*alX), &(*alY), &(*lePion));
                if(aligner) {
                    return aligner;
                }
            }
        }
    }
    return false;
}

// Fonction qui sert renvoie une colonne aléatoire en verifiant que cette colonne ne permet pas la victoire a l'ennemie
int aleatoire(Grille laGrille2, int x, char pion, char lePion) {
    int random,y,safe;
    bool win;
    safe = 0;

    random = rand() % NB_COLONNES;
    y = chercherLigne(laGrille2, random);
    win = choixGDTop(laGrille2, x, pion, random, lePion);
    // tant que ca risque de faire gagner l'ennemie ou que la colonne est pleine
    while(win || y == -1) {
        random = rand() % NB_COLONNES;
        y = chercherLigne(laGrille2, random);
        win = choixGDTop(laGrille2, x, pion, random, lePion);
        //safe lock (apres 3*NB_COLONNES essais on renvoie une colonne random peut importe si elle fais win)
        if(safe>NB_COLONNES*3) {
            return random;
        }
        safe++;
    }

    return random;
}

// permet de choisir la colonne ou jouer (a gauche/droite du pion, en haut du pion, ou aléatoire) tout en verifiant que cette colonne ne permet pas la victoire a l'ennemie
int trouveColonne(Grille laGrille2, char pion, char lePion) {
    int i, x;
    bool win;

    for(i = 0; i < NB_COLONNES; i++) {
        x = chercherLigne(laGrille2, i)+1;
        if(x-1 != -1) {
            // on cherche un emplacement ou on a un de nos pions
            if(laGrille2[x][i] == pion) {
                // a gauche
                if(i != 0 && laGrille2[x][i-1] == VIDE) {
                    win = choixGDTop(laGrille2, x, pion, i-1, lePion);
                    if(!win) {
                        return i-1;
                    } else {
                        // au dessus
                        win = choixGDTop(laGrille2, x, pion, i, lePion);
                        if(!win && laGrille2[x][i] == VIDE) {
                            return i;
                        } else {
                            //aléatoire
                            win = choixGDTop(laGrille2, DEBUT, pion, i, lePion);
                            if(!win && laGrille2[x][DEBUT] == VIDE) {
                                return i;
                            } else {
                                return aleatoire(laGrille2, x, pion, lePion);
                            }
                        }
                    }
                } else if (i != NB_COLONNES && laGrille2[x][i+1] == VIDE) {
                    // a droite
                    win = choixGDTop(laGrille2, x, pion, i+1, lePion);
                    if(!win) {
                        return i+1;
                    } else {
                        // au dessus
                        win = choixGDTop(laGrille2, x, pion, i, lePion);
                        if(win && laGrille2[x][i] == VIDE) {
                            return i;
                        } else {
                            //aléatoire
                            win = choixGDTop(laGrille2, DEBUT, pion, i, lePion);
                            if(!win && laGrille2[x][DEBUT] == VIDE) {
                                return i;
                            } else {
                                return aleatoire(laGrille2, x, pion, lePion);
                            }
                        }
                    }
                } else {
                    // au dessus
                    win = choixGDTop(laGrille2, x, pion, i, lePion);
                    if(!win && laGrille2[x][i] == VIDE) {
                        return i;
                    } else {
                        //aléatoire
                        win = choixGDTop(laGrille2, DEBUT, pion, i, lePion);
                        if(!win && laGrille2[x][DEBUT] == VIDE) {
                            return i;
                        } else {
                            return aleatoire(laGrille2, x, pion, lePion);
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

int choisirColonneStrategieBest(Grille laGrille, char pion) {
    // on créer une copie de la grille pour ne pas la modifier
    Grille laGrille2;
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
    char lePion;
    bool aligner;
    aligner = PossibGagnant(laGrille2, pion, &alX, &alY, &lePion);

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
                    return trouveColonne(laGrille2, pion, lePion);
                }
            } else {
                return trouveColonne(laGrille2, pion, lePion);
            }
        } else {
            return trouveColonne(laGrille2, pion, lePion);
        }  
    }
}

int choisirColonneStrategie3(Grille laGrille, char pion) {
    int colD = 3;
    int colG = 3;
    int res = -1;
    while (res == -1) {
        if(chercherLigne(laGrille, colD) == -1) {
            if(chercherLigne(laGrille, colG) == -1) {
                colD += 1;
                colG -= 1;
            } else {
                res = colG;
            }
        } else {
            res = colD;
        }
    }
    return res;
}

int choisirColonneStrategie4(Grille laGrille, char pion) {
    return (rand() % NB_COLONNES-1);
}

int choisirColonneStrategie1(Grille laGrille, char pion) {
    int col,i;
    i = 0;
    while (i<NB_COLONNES) {
        col = chercherLigne(laGrille, i);
        if(col != -1) {
            return i;
        }
        i++;
    }
    return i;
}

int choisirColonne(Grille laGrille, char pion){
    int col;

    do{
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col<0 ||col>6);
    return col;
}

int chercherLigne(Grille laGrille, int col){
    int ligne = -1;

    while (ligne<NB_LIGNES-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col){
    // consiste à regarder si une ligne de 4 pions s'est formée autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
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

void finDePartie(char vainqueur){
    if (vainqueur != INCONNU){
        printf("Joueur %c vainqueur\n", vainqueur);
    } else {
        printf("MATCH NUL");
        equal++;
    }
}

