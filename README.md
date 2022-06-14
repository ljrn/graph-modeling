# projet-sd-graphes

## Contenu de l'archive

L'archive contient l'ensemble des fichiers .c (main.c, sommet.c, liste_arete.c) et des .h (liste_arete.h, sommet.h).
Elle contient aussi l'ensemble des exemples présents sur Moodle et un fichier Makefile.

## Compiler le projet

Pour compiler le projet, placez-vous dans le dossier de l'archive décompressée et executez la commande:
    make

Pour supprimer les fichiers .o et l'executable, executez la commande:
    make clean

## Executer le projet

Pour executer le projet lancez la commande:
    ./livraison <fichier_exemple>

Puis vous n'avez plus qu'à rentrer le numéro du client par lequel vous voulez commencer le Tour Geant (compris entre 1 et le nombre de clients de l'exemple).

Le programme affichera le coût minimal de la livraison (en fonction du premier client choisi).
