# commandes de base GIT

`Peuvent s'executer à n'importe quel endroit du (sous-) projet`


- git init `<chemin>` : créer un dossier qui sera la racine de tout le projet à l'endroit défini
  - `<chemin>` = "." : créer le .git à l'endroit où on est

- git status : affiche l'état des fichiers du projet

---
- git clone : cloner le dossier sur le web avec github/git

- git push : synchroniser le local vers le dsitant

- git pull : pour synchroniser le distant vers le local

- git remote add origin https://... : rattacher le dépôt local à un dépot distant

- git push origin master : pour le premier push

### uniquement ce qui est commité
---

## Commandes de config

- git config --global user.name "Votre nom"
- git config --global user.email "votre@email"
- git config --global core.editor nano

- git rm --cached fichier : supprimer un fichier de l'index

### 