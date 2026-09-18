# TP6 — Analyse d'images BMP, SVG et messages JSON

Les sources se trouvent dans [src/](src/), les images de test dans
[images/](images/). Tout compile sans erreur ni avertissement avec
`gcc -Wall -Wextra -Werror`.

## Exercices

| Ex. | Fichiers                   | Sujet                                              |
|-----|----------------------------|-----------------------------------------------------|
| 6.1 | `client.c`, `serveur.c`    | Extraction des couleurs d'un BMP → camembert SVG    |
| 6.2 | `client.c`, `serveur.c`    | Nombre de couleurs saisi par l'utilisateur (≤ 30)   |
| 6.3 | `client.c`, `serveur.c`    | Messages au format JSON (cJSON)                     |
|  —  | `bmp.c`, `bmp.h`           | Lecture de l'en-tête et des pixels d'une image BMP  |
|  —  | `couleur.c`, `couleur.h`   | Comptage et tri des couleurs distinctes             |
|  —  | `cJSON.c`, `cJSON.h`       | Bibliothèque JSON (voir « Dépendance » plus bas)    |

## Compilation

```bash
cd src
make          # construit serveur et client
make clean
```

## Exécution

Deux terminaux sont nécessaires.

```bash
# Terminal 1
./serveur

# Terminal 2 : le nombre de couleurs est demandé
./client ../images/drapeau24.bmp

# ou directement en argument
./client ../images/cercles32.bmp 20
```

Le serveur écrit le camembert dans `pie_chart.svg`, puis tente de l'ouvrir avec
`firefox`, puis avec `xdg-open`. Si aucun navigateur n'est installé (cas d'un
Codespace sans interface graphique), il affiche simplement le chemin du fichier
généré — le SVG est produit dans tous les cas.

## Images de test

Le dossier `images` du sujet n'étant pas fourni avec le dépôt, quatre images ont
été générées pour les tests :

| Image             | Format  | Couleurs distinctes | Motif                        |
|-------------------|---------|---------------------|------------------------------|
| `drapeau24.bmp`   | 24 bits | 12                  | bandes verticales de largeurs décroissantes |
| `degrade24.bmp`   | 24 bits | 16                  | dégradé horizontal           |
| `damier32.bmp`    | 32 bits | 4                   | damier RGBA (dont 2 semi-transparentes) |
| `cercles32.bmp`   | 32 bits | 20                  | disques concentriques        |

Toutes ont une largeur multiple de 4 pixels : les lignes du BMP n'ont donc aucun
octet de remplissage, et `analyse_bmp_image()` lit les pixels sans décalage.

## Format des messages (exercice 6.3)

Du client vers le serveur :

```json
{ "code": "message", "valeurs": ["bonjour"] }

{ "code": "couleurs", "nombre": 10,
  "valeurs": ["#ef7812", "#2cc864", "#ff0000", "..."] }
```

Du serveur vers le client :

```json
{ "code": "message",  "valeurs": ["bonjour"] }
{ "code": "reponse",  "valeurs": ["pie_chart.svg (10 couleurs)"] }
{ "code": "erreur",   "valeurs": ["nombre de couleurs invalide"] }
```

Le champ `nombre` correspond à l'exercice 6.2 : le serveur le lit **avant** les
couleurs et ne traite que les `nombre` premières valeurs.

## Dépendance

[cJSON](https://github.com/DaveGamble/cJSON) v1.7.18, sous licence MIT, est
inclus directement dans `src/` (`cJSON.c`, `cJSON.h`) afin que `make` fonctionne
sans installation préalable. La notice de licence figure en tête des deux
fichiers.

## Remarques

- Les couleurs sont triées par ordre croissant d'occurrences par
  `trier_couleur_compteur()` : les plus fréquentes sont donc à la **fin** du
  tableau, que le client parcourt à l'envers.
- Le client ajuste le nombre de couleurs si l'image en contient moins que
  demandé.
- Le serveur dessine un cercle complet lorsqu'une seule couleur est envoyée : un
  arc SVG de 360° a le même point de départ et d'arrivée et ne serait pas tracé.
