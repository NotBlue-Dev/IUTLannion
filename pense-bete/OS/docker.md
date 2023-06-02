# utiliser des commandes docker : 
- docker image pull <nom_comm> 

- docker run container <nom_comm> <param> : on se place dans le docker et on lance la commande
- - t : attaché au terminal
- - i : interractif

## qrcode

- docker image pull qrcode : on récupère l'image qrcode pour l'utiliser

- docker container run qrcode -ti --rm : on est dans le docker, et on run qrcode, en mode temporaire avec --rm

- docker container cp ID:/word/code.png Documents


