# TP1 — Bases de la programmation en C

Tous les fichiers se trouvent dans [src/](src/) et compilent sans erreur ni
avertissement avec `gcc -Wall -Wextra -Werror`.

## Exercices

| Ex.  | Fichier            | Sujet                                                    |
|------|--------------------|----------------------------------------------------------|
| 1.1  | `bonjour.c`        | Affichage de « Bonjour le Monde! »                        |
| 1.2  | `cercle.c`         | Aire et périmètre d'un cercle (`M_PI`, `-lm`)             |
| 1.3  | `sizeof_types.c`   | Taille en octets des types de base (`signed`/`unsigned`)  |
| 1.4  | `variables.c`      | Affectation et affichage des types de base                |
| 1.5  | `opérateurs.c`     | Opérateurs arithmétiques, modulo et comparaisons          |
| 1.5b | `opérateurs2.c`    | Affectations composées, `++`/`--`, décalages, `&&`/`\|\|` |
| 1.6  | `boucles.c`        | Triangle rectangle : version `for` **et** version `while` |
| 1.7  | `conditions.c`     | Divisibilité par 5, 7 et 11 avec `continue` et `break`    |
| 1.8  | `calculs.c`        | Calculatrice à base de `switch` (`+ - * / % & \| ~`)      |
| 1.9  | `binaire.c`        | Conversion en binaire (masquage **et** divisions par 2)   |
| 1.10 | `pyramide.c`       | Pyramide de nombres avec boucles imbriquées               |

## Compilation et exécution

```bash
cd src
gcc -Wall -Wextra -o bonjour bonjour.c && ./bonjour
gcc -Wall -Wextra -o cercle cercle.c -lm && ./cercle   # -lm pour <math.h>
gcc -Wall -Wextra -o boucles boucles.c && ./boucles
# ... même principe pour les autres fichiers
```

## Remarques

- **1.6** : `boucles.c` contient les deux versions demandées. `triangle_for()`
  utilise deux boucles `for` imbriquées, `triangle_while()` obtient le même
  affichage avec des boucles `while`, un `if` et un `continue`. La variable
  `compteur` est vérifiée : elle doit rester strictement inférieure à 10.
- **1.9** : `printf` n'a pas de code de conversion pour le binaire. Les deux
  méthodes demandées sont implémentées : décalage `>>` avec masque `& 1`, et
  divisions successives par 2 avec le reste `%`.
- **1.5b** : `opérateurs2.c` n'apparaît pas dans le sujet mais est attendu par
  `evaluation/evaluation.sh` ; il prolonge l'exercice 1.5.
