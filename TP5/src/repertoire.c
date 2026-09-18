/*
 * TP5 - Exercices 5.1, 5.2 et 5.3 : lecture d'un repertoire
 *
 * opendir()  ouvre un repertoire et renvoie un DIR *.
 * readdir()  renvoie l'entree suivante (struct dirent *), ou NULL a la
 *            fin du repertoire.
 * closedir() referme le repertoire.
 *
 * Les entrees "." (le repertoire courant) et ".." (le repertoire parent)
 * sont ignorees lors des parcours recursif et iteratif, sans quoi le
 * parcours ne se terminerait jamais.
 *
 * Compilation : gcc -Wall -Wextra -o repertoire repertoire.c
 * Utilisation : ./repertoire <nom_du_repertoire> [simple|recursif|iteratif]
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "repertoire.h"

#define TAILLE_CHEMIN 4096
#define TAILLE_PILE 1024

/* Construit le chemin "<repertoire>/<nom>" dans `destination`.
 * Renvoie 0 en cas de succes, -1 si le chemin est trop long. */
static int construit_chemin(char *destination, size_t taille,
                            const char *repertoire, const char *nom)
{
  int ecrit = snprintf(destination, taille, "%s/%s", repertoire, nom);

  if (ecrit < 0 || (size_t)ecrit >= taille)
  {
    fprintf(stderr, "Avertissement : chemin trop long (%s/%s)\n", repertoire, nom);
    return -1;
  }

  return 0;
}

/* Renvoie 1 si `chemin` designe un repertoire, 0 sinon. */
static int est_repertoire(const char *chemin)
{
  struct stat informations;

  /* lstat (et non stat) pour ne pas suivre les liens symboliques :
   * cela evite les boucles infinies lors du parcours recursif */
  if (lstat(chemin, &informations) != 0)
  {
    return 0;
  }

  return S_ISDIR(informations.st_mode);
}

/* Renvoie 1 pour les entrees "." et "..", qu'il faut ignorer. */
static int est_point_ou_pointpoint(const char *nom)
{
  return (strcmp(nom, ".") == 0 || strcmp(nom, "..") == 0);
}

/*
 * Exercice 5.1 - Liste des fichiers et repertoires d'un dossier.
 */
int lire_dossier(const char *nom_repertoire)
{
  DIR *repertoire;
  struct dirent *entree;

  if (nom_repertoire == NULL)
  {
    return -1;
  }

  /* ouverture du repertoire */
  repertoire = opendir(nom_repertoire);
  if (repertoire == NULL)
  {
    perror(nom_repertoire);
    return -1;
  }

  printf("Contenu du repertoire %s :\n", nom_repertoire);

  /* readdir renvoie NULL quand il n'y a plus d'entree */
  while ((entree = readdir(repertoire)) != NULL)
  {
    char chemin[TAILLE_CHEMIN];

    if (construit_chemin(chemin, sizeof(chemin), nom_repertoire, entree->d_name) != 0)
    {
      continue;
    }

    if (est_repertoire(chemin))
    {
      printf("  [repertoire] %s\n", entree->d_name);
    }
    else
    {
      printf("  [fichier]    %s\n", entree->d_name);
    }
  }

  closedir(repertoire);

  return 0;
}

/*
 * Exercice 5.2 - Liste recursive.
 *
 * La fonction s'appelle elle-meme sur chaque sous-repertoire rencontre.
 * La recursion s'arrete naturellement lorsqu'un repertoire ne contient
 * plus de sous-repertoire.
 */
int lire_dossier_recursif(const char *nom_repertoire)
{
  DIR *repertoire;
  struct dirent *entree;

  if (nom_repertoire == NULL)
  {
    return -1;
  }

  repertoire = opendir(nom_repertoire);
  if (repertoire == NULL)
  {
    perror(nom_repertoire);
    return -1;
  }

  printf("%s :\n", nom_repertoire);

  while ((entree = readdir(repertoire)) != NULL)
  {
    char chemin[TAILLE_CHEMIN];

    /* on ignore "." et ".." pour ne pas boucler indefiniment */
    if (est_point_ou_pointpoint(entree->d_name))
    {
      continue;
    }

    if (construit_chemin(chemin, sizeof(chemin), nom_repertoire, entree->d_name) != 0)
    {
      continue;
    }

    if (est_repertoire(chemin))
    {
      printf("  [repertoire] %s\n", entree->d_name);
    }
    else
    {
      printf("  [fichier]    %s\n", entree->d_name);
    }
  }

  /* on referme le repertoire avant de descendre d'un niveau : cela
   * limite le nombre de descripteurs ouverts simultanement */
  rewinddir(repertoire);

  while ((entree = readdir(repertoire)) != NULL)
  {
    char chemin[TAILLE_CHEMIN];

    if (est_point_ou_pointpoint(entree->d_name))
    {
      continue;
    }

    if (construit_chemin(chemin, sizeof(chemin), nom_repertoire, entree->d_name) != 0)
    {
      continue;
    }

    if (est_repertoire(chemin))
    {
      /* appel recursif sur le sous-repertoire */
      lire_dossier_recursif(chemin);
    }
  }

  closedir(repertoire);

  return 0;
}

/*
 * Exercice 5.3 - Liste iterative.
 *
 * On remplace la recursion par une pile explicite : les
 * sous-repertoires rencontres sont empiles, et la boucle continue tant
 * que la pile n'est pas vide.
 */
int lire_dossier_iteratif(const char *nom_repertoire)
{
  /* la pile des repertoires restant a traiter */
  char pile[TAILLE_PILE][TAILLE_CHEMIN];
  int sommet = 0;

  if (nom_repertoire == NULL)
  {
    return -1;
  }

  /* on empile le repertoire de depart */
  snprintf(pile[sommet], TAILLE_CHEMIN, "%s", nom_repertoire);
  sommet++;

  while (sommet > 0)
  {
    char courant[TAILLE_CHEMIN];
    DIR *repertoire;
    struct dirent *entree;

    /* on depile le repertoire a traiter */
    sommet--;
    snprintf(courant, sizeof(courant), "%s", pile[sommet]);

    repertoire = opendir(courant);
    if (repertoire == NULL)
    {
      perror(courant);
      continue; /* on passe au repertoire suivant */
    }

    printf("%s :\n", courant);

    while ((entree = readdir(repertoire)) != NULL)
    {
      char chemin[TAILLE_CHEMIN];

      if (est_point_ou_pointpoint(entree->d_name))
      {
        continue;
      }

      if (construit_chemin(chemin, sizeof(chemin), courant, entree->d_name) != 0)
      {
        continue;
      }

      if (est_repertoire(chemin))
      {
        printf("  [repertoire] %s\n", entree->d_name);

        /* le sous-repertoire est empile pour etre traite plus tard */
        if (sommet < TAILLE_PILE)
        {
          snprintf(pile[sommet], TAILLE_CHEMIN, "%s", chemin);
          sommet++;
        }
        else
        {
          fprintf(stderr, "Avertissement : pile pleine, %s ignore.\n", chemin);
        }
      }
      else
      {
        printf("  [fichier]    %s\n", entree->d_name);
      }
    }

    closedir(repertoire);
  }

  return 0;
}

/*
 * Programme principal : le repertoire est donne sur la ligne de
 * commande, ainsi que le mode de parcours (simple par defaut).
 */
int main(int argc, char *argv[])
{
  const char *nom_repertoire;
  const char *mode = "simple";

  if (argc < 2)
  {
    printf("Utilisation : %s <nom_du_repertoire> [simple|recursif|iteratif]\n",
           argv[0]);
    return EXIT_FAILURE;
  }

  nom_repertoire = argv[1];

  if (argc >= 3)
  {
    mode = argv[2];
  }

  if (strcmp(mode, "simple") == 0)
  {
    /* exercice 5.1 */
    return (lire_dossier(nom_repertoire) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  else if (strcmp(mode, "recursif") == 0)
  {
    /* exercice 5.2 */
    return (lire_dossier_recursif(nom_repertoire) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  else if (strcmp(mode, "iteratif") == 0)
  {
    /* exercice 5.3 */
    return (lire_dossier_iteratif(nom_repertoire) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  }

  fprintf(stderr, "Mode inconnu : %s (simple, recursif ou iteratif)\n", mode);
  return EXIT_FAILURE;
}
