# TP3 — Tableaux, recherche, tri et représentation mémoire

Tous les fichiers se trouvent dans [src/](src/) et compilent sans erreur ni
avertissement avec `gcc -Wall -Wextra -Werror`.

## Exercices

| Ex. | Fichier                     | Sujet                                              |
|-----|-----------------------------|-----------------------------------------------------|
| 3.1 | `sizeof.c`                  | Taille des types et des pointeurs (machine 64 bits)  |
| 3.2 | `grand_petit.c`             | Plus grand et plus petit entier d'un tableau de 100  |
| 3.3 | `tri.c`                     | Tri croissant (tri à bulles) de 100 entiers          |
| 3.4 | `chercher.c`                | Recherche séquentielle d'un entier                   |
| 3.5 | `recherche_dichotomique.c`  | Recherche dichotomique dans un tableau trié          |
| 3.6 | `octets.c`                  | Octets en mémoire des différents types (boutisme)    |
| 3.7 | `couleur_compteur.c`        | Couleurs distinctes et nombre d'occurrences          |
| 3.8 | `chercher2.c`               | Recherche d'une phrase, **sans** `strcmp`            |
|  —  | `couleurs.c`                | Structure RGBA réutilisée depuis le TP2              |

## Compilation et exécution

```bash
cd src
gcc -Wall -Wextra -o sizeof sizeof.c && ./sizeof
gcc -Wall -Wextra -o tri tri.c && ./tri
gcc -Wall -Wextra -o chercher chercher.c && ./chercher        # demande un entier
gcc -Wall -Wextra -o chercher2 chercher2.c && ./chercher2     # demande une phrase
```

## Remarques

- **3.1** : tous les pointeurs font 8 octets quel que soit le type pointé et le
  niveau d'indirection : un pointeur ne contient qu'une adresse.
- **3.5** : le tableau est construit **déjà trié** (incréments aléatoires
  positifs), condition indispensable à la recherche dichotomique. L'indice du
  milieu est calculé par `debut + (fin - debut) / 2` pour éviter tout
  débordement.
- **3.6** : les octets sont lus via un `unsigned char *`, seul type avec lequel
  il est légal de relire la représentation mémoire d'une variable. Le programme
  indique aussi si la machine est petit- ou gros-boutiste.
- **3.8** : la comparaison est faite caractère par caractère, sans aucune
  fonction de bibliothèque.
