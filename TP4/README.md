# TP4 — Fonctions, récursivité, fichiers et listes chaînées

Tous les fichiers se trouvent dans [src/](src/) et compilent sans erreur ni
avertissement avec `gcc -Wall -Wextra -Werror`.

## Exercices

| Ex. | Fichiers                        | Sujet                                          |
|-----|---------------------------------|------------------------------------------------|
| 4.0 | [`../gdb/erreurs.c`](../gdb/erreurs.c) | Débogage avec `gdb`                     |
| 4.1 | `operator.h`, `operator.c`      | Fonctions de calcul + `switch`                  |
| 4.2 | `fichier.h`, `fichier.c`        | `lire_fichier`, `ecrire_dans_fichier`           |
| 4.3 | `etudiant_bd.c`                 | Base de données étudiante → `etudiant.txt`      |
| 4.4 | `calcule.c`                     | Calculatrice en ligne de commande               |
| 4.5 | `factorielle.c`                 | Factorielle récursive                           |
| 4.6 | `chercherfichier.c`             | Recherche d'une phrase dans un fichier          |
| 4.7 | `liste.h`, `liste.c`            | Liste simplement chaînée de couleurs RGB        |
|  —  | `main.c`                        | Menu commun aux exercices 4.1, 4.2 et 4.7       |

## Compilation

```bash
cd src
make          # construit main, calcule, etudiant_bd, factorielle, chercherfichier
make clean
```

## Exécution

```bash
# Exercices 4.1, 4.2 et 4.7 : une seule fonction main() avec un menu
./main

# Exercice 4.3 : saisie des 5 étudiant.e.s, écriture dans etudiant.txt
./etudiant_bd

# Exercice 4.4 : calculatrice en ligne de commande
./calcule + 15 8        # Resultat : 23
./calcule '*' 7 8       # Resultat : 56
./calcule '|' 5 3       # Resultat : 7
./calcule '~' 16        # Resultat : -17   (opérateur unaire)

# Exercice 4.5
./factorielle

# Exercice 4.6
./chercherfichier etudiant.txt
```

> Les caractères `*`, `|`, `&` et `~` sont interprétés par le shell : il faut
> les protéger par des apostrophes.

## Exercice 4.0 — gdb

Le fichier [`../gdb/erreurs.c`](../gdb/erreurs.c) contient l'erreur décrite dans
[`../gdb/README.md`](../gdb/README.md) : la boucle compare `compteur` à
`sizeof(tableau)` (400 octets) au lieu du nombre d'éléments (100), ce qui écrit
au-delà du tableau (`stack smashing detected`).

```bash
cd ../gdb
gcc -ggdb3 -o erreurs erreurs.c
gdb ./erreurs
(gdb) r                    # SIGABRT
(gdb) bt                   # #8 ... in main () at erreurs.c:43
(gdb) break erreurs.c:35
(gdb) r
(gdb) p compteur
(gdb) p tableau[0]@5
(gdb) n
(gdb) continue
(gdb) quit
```

La correction (`sizeof(tableau) / sizeof(tableau[0])`) figure en commentaire à la
fin du fichier.

## Remarques

- **`main.c`** : une seule fonction `main()` affiche un menu et appelle la
  fonction d'entrée de l'exercice choisi (`exercice_operateur()`,
  `exercice_fichier()`, `exercice_liste()`), comme demandé par le sujet.
- **4.2** : `ecrire_dans_fichier` ouvre le fichier en mode `"a"` (ajout), ce qui
  permet à l'exercice 4.3 d'écrire un.e étudiant.e par ligne.
- **4.3** : le nom et le prénom sont lus avec `scanf("%63s")` ; l'adresse
  contenant des espaces, elle est lue avec `fgets`.
- **4.7** : `insertion()` ajoute à la fin de la liste pour conserver l'ordre
  d'ajout, et `libere_liste()` restitue toute la mémoire allouée.
