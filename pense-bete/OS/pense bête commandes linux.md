# Pense bête pour les commandes linux :
Pour lancer un programme de façon asynchrome (plusieurs en même temps) on fait "commande &" (exemple ls -l &)

-fg -bg arrière-plan ; avant-plan defini en bas
## Commandes clavier
### ctrl : 
- V : kill un programme (signal 15)
- Z : pause un programme (signal 20 : TSTP (Terminal SToP))
## Les commandes classiques
- bg (backGround) : réveille le processus et le met en arrère plan

  ---
- cd (change directory) 
  - (cd sans rien ramène au home) 
  - (cd .. : aller sur le parent)

  ---
- cp (CoPy) : uniquement des fichiers ; -r pour copier un dossier

  ---
- fg (ForeGround) : on repasse un programme en avant-plans

   ---
- kill -`<SIGNAL> <PID>: `envoyer un signal à un programme
  - kill -9/-KILL `<PID>` : tue le programme avec le PID correpondant 
  - kill -L : affiche tout les signaux existant (64 différents)

  ---
- ls (LiSt)	liste les éléments du dossier actuel
  - -l donne plus de détail sur ce qui est demandé
  - -a montre les fichiers cachés, ils commencent par un .
  - -R fait de la récursivité

  ---
- man (MANual) une sorte de help

  ---
- mkdir (make directory) 
  - mkdir -p : remplace le dossier s'il existe

  ---
- mv `<src> <desti>` (MoVe, pour renommer : on bouge un fichier au même endroit sous un nouveau nom)

  ---
- ps (Process Status)
  - ps -d : mystère même le prof ne sais pas (ça selectionne tt les processus sauf le session leader ?!?)
  - ps -f : donne un format de listage complet
  - ps -e/ef/eF/ely : affiche tout les processus système
  - ps -edf : association de -e ; -d ; -f 
  - ps -axuwf :  affiche les processus en arborescence
  - pstree -pshl : pareil qu'au dessus

  ---
- pwd (print working directory)

  ---
- rm `<chemin>` (ReMove) : supprime des fichiers 
  - rmdir / rm -dir : (remove directory) ne marche que sur les répertoires vides sans contenu
  - -r : supprime le répertoire, même s'il est remplis

  ---
- tr `<cible> <nouveau nom>` < nom_fichier : permet de convertir les caractères de la source en d'autres caractères
  - -d : supprime tout les caractères de la source
  - -s : permet de supprimer toute redondance de successive pour en garder qu'un 
  - (TD5)

  ---
- wc (Word Count): renvoie le nombre de caractères, mots et lignes sans arguments
  - -l (lines): renvoie le nombre de lignes
  - -w (Word): nombre de mots
  - -c (character): nombre de caractères

---

- cat : ouvre les fichier au format txt

  ---

- colrm `<col1> [col2]`: supprimer des colones des fichiers textes

  ---
- cut -d `<sep>` -f `<champs>` : extrait de chaque ligne les valeurs du ou des champs utilisés, le séparateur de 'champs' est 'sep' 

  ---
- date : date+heure courante

  ---
- head : produire en sortie des lignes se trouvant en tête de la source donnée en entrée

  ---
- tail : fin (QUEUE) d'un fichier

  ---
- touch : créer un fichiers/des fichiers; on peut indiquer un chemin relatif ou absolu pour y arriver
 
  ---
- tree : arborescence des fichiers

  ---
- more : (en bas de l'écran ça affiche more) affiche le texte et le pagine

  ---
- less : affiche le texte dans une fenêtre isolée (comme l'affichage man)

  ---
- sort : trie les lignes de texte 
   - -k `<champ_deb,champ_fin>`: on donne une clé pour trier
   - -n : tri numérique
   - -r : inverser le tri
   - -t `<sep>`: on donne le séparateur entre les données
   - -u : Ne produit que des lignes uniques, les valeurs doubles sont omises

  ---
- uniq : dédoublonner 
  - -i : Minuscules et majuscules sont équivalentes
  - -d : fait l'inverse produit en sortie uniquement les lignes qui apparaissent plusieurs fois
  - -c : compte les répétitions des même caractères 

- which : localiser une commande (ls par exemple)

  ---
- who : QUI est connecthead : début (tête) d'un fichier
## Commandes application :
~~~
cc <nom>.c -o <nom> -Wall //compiler un fichier en C (C Compiler)
./<nom> //lancer l'executable du C
~~~
## Edition de texte
---
### cat lire des fichiers texte
- cat <nom_fichier>:

---
### Vi/Vim pour les éditer 
- (i pour insert insérer du texte où se trouve le curseur)
- (a pour append insertion du texte à partir de la position juste après le curseur)
- (R pour replace remplacement du texte déjà présent à aprtir de l'endroit où se trouve le curseur. La saisir peut-être plus longue que le texte actuel )
pour sortir d'un mode : ESC

    ---
- (I majuscule : insertion du texte au bébut de la ligne sur laquelle se trouve le curseur)
- (A majuscule : insertion du texte à la fin de la ligne où se trouve le curseur)
- (r minuscule : remplacement du caractère sous le curseur par le prochain caractère qu'on va saisir. Attention, vous n'entrez pas en mode insertion, après la saisie du caractère de remplacement, on reviens en mode commande)

    ---
- pour se déplacer : flèches ou alors : (h:left  k:top j:bottom l:right)
-  w (word)déplace un mot vers l'avant
- b (backward) deplace un mot vers l'arrière
- $ se déplace jusqu'à la fin de la ligne courante
- 0 se déplace que début de la ligne courante
- G se déplacer à la dernière ligne (si nombre avant G : 213G, se déplace à ce numéro de ligne)
    
    ---
- :set (no)number numéros de ligne
#### commandes de sauvegarde/exit Vi
- :x quitter et sauvegarder
- :q quitter sans sauvegarder(si le fichier n'a pas été modifié)
- :q! quitter sans sauvegarder ds tt les cas
- ZZ(maj) commande directe, quitter en sauvegardant
- :w  sauvegarde/renommage (Write)(:wq quitte en sauvegardant)(:w toto) 
- :!w toto (écrase le fichier toto existant)

---




# Jokers
## * Séquence quelconque de caractères 
doc* : cible tous les fichiers/dossiers commençant par doc   
\*doc* : cible tous les fichiers/dossiers avec doc suivi & précédé de x caractères

*txt : cible tous les fichiers/dossiers finissant par txt

La description des noms d'objets avec des jokers s'appelle un motif 

---
## ? Un et un seul caractère quelconque
doc?.txt : cible tous les fichiers avec un caractère à la place de ? ; ne peut pas être rien

On peut en mettre x ? à la suite pour définir x caractères

---
Les Jokers peuvent se combiner : *.???
On supprime les fichiers/dossier avec x caractères avant le . et 3 caractères après

---

## [...] caractère parmis liste

remplace un seul caractère parmis les caractères dans les crochets

[Dd]* : un D ou d puis nom a x caractères

## [...-...] caractère parmis intervalle 

\*[0-9]* Un nom avec x caractères ; un chiffre entre 0 et 9 puis x caractères

\*[a-z] Un nom qui se finit par un caractère entre a et z (une lettre minuscule)

[0-9] : chiffre

[a-z] : lettre minuscule

[A-Z] : lettre majuscule

[a-Z] : ne signifie pas maj ou min : le Z est avant a en ASCII

[A-z] : ne signifie pas maj ou min : il y a des caractères entre les 
min et les maj en ASCII

[ab0-9yz] : [ab0123456789yz]

# Redirection 
<commande> <numéroCanal>> <fichier> : stocke dans un fichier les résultats des commandes, rien ou 1 pour STDOUT ; 2 pour STDERR (ls documents 2> erreur)
mettre >> empêche l'ancien fichier d'être écrasé
rediriger le canal 0 : STDIN

# Tubes "|"
Pour séparer les commandes : faire un lien entre les deux comme pour : seq 1 17 1000 | wc -l

# Expressions rationnelles "egrep"
change des jocker en console, utilisable dans les fichiers

- egrep `[option]` motif :
  - -i (ignore case): ne fait pas la différence entre min et maj
  - -l : affiche le nom des fichiers ou à été trouvé au minimum un motif
  - -v (invert): affiche les lignes qui ne correspondent pas
  - -c (count): affiche le nombre de lign qui correspond au motif