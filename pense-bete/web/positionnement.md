TD3 
# Positionnement en (flux courant)
souple et stable
- position : static ; (éléments de la page en flux courant)

# Positionnement relatif(flux courant)
utile pour superposer des éléments
- position : relative;

- left|right|bottom|top : 10em;

## Profondeur
- z-index : 2;
(plus le z-index est grand plus l'élement sera devant les autres ; défaut = 0)

# Positionnement absolu (indépendant flux courant)
- position : absolute ;

- left|right|bottom|top : 10em;

l'élement est placé par rapport au dernier parent/ancêtre positionné (body par défaut) qui devient son conteneur.

Tout sauf static convient

## Positionnement fixe
cas particulier du positionnement absolu

ici il reste figé : il ne se déplace pas selon l'ascenseur

placé dans body
- position : fixed ;

- left|right|bottom|top : 10em;

# Positionnement adhérent

hybride entre relatif et fixe

- position : sticky ;

- left|right|bottom|top : 10em;

l'élement se fige dans son conteneur (donc pas forcément body comparé au fixed)

# Positionnement flottant (indépendant flux courant)

- float : left|right
utile pour placer des éléments côtes à côtes

# Habillage 

- clear: none|left|right|both; (permet d'indiquer comment placer un nouvel élément par rapport au dernier bloc en float)

# Mode d'affichage

- display : changement de mode de positionnement/affichage
(inline|block|inline-block|flex|inline-flex|none)

block : l'un en dessous de l'autre; on peut le dimensionner (width, height, margin, padding)



inline : les blocs perdent certaines caractéristiques et l'alignent

inline-block : l'un à coté de l'autre et on peut donner des dimensions (width, height, margin, padding comme les blocs)