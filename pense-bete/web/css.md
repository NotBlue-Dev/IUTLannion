# Les pseudos-éléments
s'utilisent après la balise 
:: first-letter {} : cible la première lettre
::first-line : cible la première ligne
# Les pseudo-classes
```<balise>```:link cible les liens insiérés avec la balise demandée
:visited : cible les liens visités
:hover liens survolés par la souris
:active : liens lors du clic de la souris
# Typographie
## font = police
- font-style : style de la police
(normal | italic | oblique ...)
- font-variant : variation de la police
(normal | small-caps ...)
- font-weight : graisse de la police
- font-size : taille de la police
- line-height : interligne 
(normal ...)
- font-family : polices applicables
### Syntaxe raccourcie

font: font-style | font-variant | font-weight | font-size/line-height | font-family;

--- 

## texte
- color : couleur du texte
- text-align : alignement du texte
(left|center|right|justify)
- text-align-last : alignement de la dernière ligne
- text-indent : retrait de première ligne
(indentation)
- text-transform : apparence du texte
(none|capitalize|uppercase|lowercase)
- letter-spacing : approche des lettres (espace entre les lettres)
- word-spacing : espace entre les mots
- tab-size : valeur du caractère tabulation (en nombre d'espaces)
- quote : definition des guillemets (paire) lors de l'usage de < q >
('<<' '>>'|'"' '"'| none)

# Dimensionnement
(margin->border->padding)
## Bloc
- box-sizing : précise ce qui est inclus dans les dimensions width et height
(content-box|border-box)(la marge interne (padding) et la bordure (border) sont inclues aux dimensions du bloc)
- rezise : redimensionnement du bloc par l'utilisateur
(none|both|horizontal|vertical)*
- width : largeur de l'élement
(vw ; Viewport Width unité relative à la hauteur de l'écran)
- height : hauteur de l'élement
(vh ; Viewport Height, unité relative à la hauteur de l'écran)
- min-wigth | max-wigth : largeur min/max de l'élement
- min-height | max-height : hauteur min/max de l'élement

---
## marges
- margin : marge externe
(margin-top->margin-right->margin-bottom->margin-left top & bottom reliés, comme right et left)

---
## padding
- padding : marge interne | espace d'encart
(padding-top->padding-right->padding-bottom->padding-left top & bottom reliés, comme right et left)

---
## Bordure
- border-width : épaisseur de la bordure
- border-style : style de la bordure
(dotted|dashed|solid|inset|double|groove|ridge|outset)
- border-color : couleur de la bordure

### Syntaxe raccourcie
border : border-width | border-style | border-color;

---
- border-radius : arrondi des angles

(on commence par le supérieur gauche puis sens horaire)
[modèle](/img_markdown/bordercss.png "schéma")
border-radius : 5px/15px -> donne un arrondi asymétrique, largeur puis hauteur

---
# Arrière Plan
- background-color : couleur de fond
- background-image : image(s) de fond
(none|url(dossier/fichier))
- background-repeat : répetition de l'image
(repeat|no-repeat|repeat-x|repeat-y)
- background-attachment : lien du fond avec la page
(scroll|fixed ...)
- background-position : position de l'image
(x% y% |xpos ypos)

### Syntaxe raccourcie
background : background-color background-image background-repeat background-attachment background-position

---
- background-clip : zone d'occupation d'une couleur de fond
(border-box|padding-box|content-box)
- background-origin : position de référence de l'image de fond
(padding-box|border-box|content-box)
- background-size : taille de l'image de fond
(contain : max. sans déformation | cover : max avec débordement | % % | 200px 100px)
[modèle](/img_markdown/backgroundcss.png "fonctionnement")

# Listes

- list-style-type : aspect de la puce
(disc|circle|square|decimal|lower-roman|upper-roman|lower-latin|upper-latin ...)
- list-style-position : emplacement de la puce
(inside | outside)
- list-style-image : image affichée comme puce
(none|url(dossier/image))

### Syntaxe raccourcie
list-style : list-style-type list-style-position list-style-image

# Tableau
- border-collapse : apparence des cellules, fusionnées ou non
(collapse | separate)
- border-spacing : espace entre les bordures (si elles sont séparées)
- empty-cells : choix de l'affichage des cellules vides
(show|hide)
- vertical-align : alignement vertical du texte dans une cellule
(baseline|top|bottom|sub|super|middle)
(s'utilise aussi pour aligner verticalement une image par rapport au texte)
# Ombrage
- box-shadow : ombrage d'une boîte
   - décalage horizontal
   - décalage vertical
   - étendu de flou
   - taille de l'ombre
   - couleur de l'ombre
   - position de l'ombre
   - box-shadow: 5px 5px 5px 10px red inset;
- text-shadow : ombrage du texte
  - décalage horizontal
   - décalage vertical
   - flou
   - couleur de l'ombre
   - text-shadow: 3px 5px 2px #000;