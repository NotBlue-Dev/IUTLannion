# Création des matrices numpy

np.array([[..,..,..],[..,..,..]]) : matrice de 2 lignes 3 colonnes (2 x 3) taille variable et valeurs à donner

np.zeros((NBLIG,NOCOL)) : remplis une matrice de 0 "NBLIG" "NOCOL" => taille de la matrice

np.ones((NBLIG,NOCOL)) : remplis une matrice de 1 "NBLIG" "NOCOL" => taille de la matrice

np.eye(X) : on crée la matrice identité carrée taille X

np.diag([]) : créer une matrice carré pleine de 0 et les valeurs rentrées définissent les valeurs de la diagonale centrale

# Commandes pratiques

A.shape : donne la taille d'une matrice : NBLIG puis NBCOL dans un tuple 

A.reshape((3,2)) : transforme une matrice sans modifier ses termes (La matrice A : (2,3) deviens (3,2))

np.concatenate((A,B), axis = 0) : sert à créer des matrices par blocs => ici on créer une matrice composée de A et B l'un sur l'autre
- (A,B) tuple des matrices à concatener
- axis : sur quel axe elles vont êtres collées: 
  - axis = 0 : on les joint l'une sur l'autre
  - axis = 1 : on les joint l'une après l'autre à la suite

# Accès à un/des terme(s) de la matrice

A[X,Y] : terme de la Xè+1 ligne, Yè+1 colonne

A[X, :] : Xè+1 ligne sous forme de tableau 

A[X, :].shape : donne la taille de la ligne séléctionnée (uniquement la longueur, dans un tuple)

A[:, X] : Xè+1 colonne sous forme de tableau en ligne

A[W:X, Y :Z] : Wè+1 jusqu'à X lignes ; Xè+1 jusqu'à Y lignes sous forme de matrice taille (X-1 * Y-1)(voir TP1 page 3 sinon)

# Opérations entre matrices

`+` et `*`(par un scalaire) fonctionnent très bien : A + 3*B 

(fonction dot :) np.dot(A,B) : produit matriciel de A et B 

(méthode dot :) A.dot(B).dot(np.ones((3,2)))