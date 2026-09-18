# TP5 — Répertoires et programmation client-serveur

Les sources se trouvent dans [src/](src/), les notes des étudiants dans
[etudiant/](etudiant/). Tout compile sans erreur ni avertissement avec
`gcc -Wall -Wextra -Werror`.

## Exercices

| Ex. | Fichiers                        | Sujet                                          |
|-----|---------------------------------|------------------------------------------------|
| 5.1 | `repertoire.h`, `repertoire.c`  | `lire_dossier` (`opendir` / `readdir`)          |
| 5.2 | `repertoire.h`, `repertoire.c`  | `lire_dossier_recursif`                         |
| 5.3 | `repertoire.h`, `repertoire.c`  | `lire_dossier_iteratif` (pile explicite)        |
| 5.4 | `serveur.c`, `client.c`         | Le serveur saisit la réponse envoyée au client  |
| 5.5 | `client.c`, `serveur.c`         | `envoie_operateur_numeros`, `recois_numeros_calcule` |
| 5.6 | `client.c`, `serveur.c`         | Somme et moyennes des notes, calculées par le serveur |

## Compilation

```bash
cd src
make          # construit serveur, client et repertoire
make clean
```

## Exercices 5.1 à 5.3 — répertoires

```bash
./repertoire ../etudiant              # 5.1 : le répertoire seul
./repertoire ../etudiant recursif     # 5.2 : version récursive
./repertoire ../etudiant iteratif     # 5.3 : version itérative
```

## Exercices 5.4 et 5.5 — messages et calculs

Deux terminaux sont nécessaires.

```bash
# Terminal 1
./serveur
Serveur en attente de connexions...
Message reçu: message: Bonjour, le monde!!
Votre reponse : Bonjour du serveur !

# Terminal 2
./client
Votre message (max 1000 caracteres): Bonjour, le monde!!
Message recu: message: Bonjour du serveur !
Votre message (max 1000 caracteres): calcule : + 23 45
Envoi au serveur : calcule: + 23 45
Message recu: calcule: 68
```

## Exercice 5.6 — calculs sur les notes

```bash
# Terminal 1
./serveur

# Terminal 2
./client --notes ../etudiant
```

Résultats obtenus : moyennes 14.8, 16.4, 14, 15.8 et 15.8, et une moyenne de
classe de **15.36**.

## Protocole

| Message                              | Sens              | Signification              |
|--------------------------------------|-------------------|----------------------------|
| `message: <texte>`                   | client → serveur  | un simple message          |
| `message: <texte>`                   | serveur → client  | la réponse saisie (5.4)    |
| `calcule: <op> <n1> [<n2>]`          | client → serveur  | une demande de calcul      |
| `calcule: <résultat>`                | serveur → client  | le résultat                |
| `erreur: <raison>`                   | serveur → client  | division par zéro, etc.    |

## Remarques

- **5.2 / 5.3** : les entrées `.` et `..` sont ignorées, sans quoi le parcours
  ne se terminerait jamais. `lstat` est utilisé plutôt que `stat` pour ne pas
  suivre les liens symboliques et éviter les boucles.
- **5.4** : si l'entrée standard du serveur n'est pas disponible (sortie
  redirigée, fin de fichier), le message reçu est renvoyé tel quel — le
  comportement d'origine.
- **5.6** : **le serveur ne lit aucun fichier**. Le client lit les notes et
  n'envoie que des opérations arithmétiques sur deux nombres à la fois, comme
  l'exige le sujet. Le serveur traite les demandes successives d'un même client
  dans une boucle infinie.
