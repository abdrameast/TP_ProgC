# TP2 — Chaînes, bits, structures et pointeurs

Tous les fichiers se trouvent dans [src/](src/) et compilent sans erreur ni
avertissement avec `gcc -Wall -Wextra -Werror`.

## Exercices

| Ex. | Fichier          | Sujet                                                        |
|-----|------------------|---------------------------------------------------------------|
| 2.1 | `puissance.c`    | Calcul de a^b sans `pow()`                                    |
| 2.2 | `bits.c`         | Vérification des 4ᵉ et 20ᵉ bits **de gauche** d'un entier     |
| 2.3 | `fibonacci.c`    | Suite de Fibonacci (U0 = 0, U1 = 1, Un = Un-1 + Un-2)         |
| 2.4 | `chaine.c`       | `longueur`, `copie` et `concaténation` réécrites à la main    |
| 2.5 | `etudiant.c`     | Données de 5 étudiant.e.s dans des tableaux parallèles        |
| 2.6 | `etudiant2.c`    | Les mêmes données dans une `struct`, initialisées par `strcpy`|
| 2.7 | `couleurs.c`     | 10 couleurs RGBA (`struct`, notation hexadécimale)            |
| 2.8 | `ptrvariables.c` | Variables manipulées par leurs adresses (avant / après)       |
| 2.9 | `tableauptr.c`   | Tableaux parcourus **sans** notation indicielle               |

## Compilation et exécution

```bash
cd src
gcc -Wall -Wextra -o puissance puissance.c && ./puissance
gcc -Wall -Wextra -o tableauptr tableauptr.c && ./tableauptr
# ... même principe pour les autres fichiers
```

## Remarques

- **2.2** : un `int` occupant 32 bits, le n-ième bit *en partant de la gauche*
  correspond au décalage `32 - n` : le 4ᵉ bit de gauche est le bit de poids 28,
  le 20ᵉ celui de poids 12.
- **2.4** : aucune fonction de `<string.h>` n'est utilisée ; `printf` ne sert
  qu'à l'affichage du résultat.
- **2.5** : les notes sont lues avec la notation pointeur `*(p + i)`, comme le
  suggère l'astuce du sujet.
- **2.8** : pour afficher un flottant en hexadécimal, une `union` permet de
  relire les mêmes octets sous la forme d'un entier (représentation IEEE 754).
  Les 6 derniers octets d'un `long double` sur x86-64 sont du remplissage.
- **2.9** : les tableaux sont parcourus uniquement avec des pointeurs
  (`for (p = tableau; p < tableau + TAILLE; p++)`), jamais avec `tableau[i]`.
