/*
 * Exercice 4.2 - Gestion de fichiers (implementation)
 *
 * Deux fonctions :
 *   - lire_fichier          : affiche le contenu d'un fichier ;
 *   - ecrire_dans_fichier   : ajoute un message dans un fichier.
 *
 * Compilation : gcc -Wall -Wextra -c fichier.c
 */

#include <stdio.h>
#include <string.h>

#include "fichier.h"

#define TAILLE_LIGNE 1024

/*
 * Affiche le contenu du fichier ligne par ligne.
 */
int lire_fichier(const char *nom_de_fichier)
{
  FILE *fichier;
  char ligne[TAILLE_LIGNE];

  if (nom_de_fichier == NULL)
  {
    fprintf(stderr, "Erreur : nom de fichier invalide.\n");
    return -1;
  }

  /* ouverture en lecture seule */
  fichier = fopen(nom_de_fichier, "r");
  if (fichier == NULL)
  {
    /* le fichier n'existe pas ou n'est pas lisible */
    perror(nom_de_fichier);
    return -1;
  }

  printf("Contenu du fichier %s :\n", nom_de_fichier);

  /* fgets renvoie NULL a la fin du fichier */
  while (fgets(ligne, sizeof(ligne), fichier) != NULL)
  {
    printf("%s", ligne);
  }
  printf("\n");

  fclose(fichier);

  return 0;
}

/*
 * Ajoute un message a la fin du fichier (mode "a" : append).
 * Le fichier est cree s'il n'existe pas.
 */
int ecrire_dans_fichier(const char *nom_de_fichier, const char *message)
{
  FILE *fichier;
  size_t longueur;

  if (nom_de_fichier == NULL || message == NULL)
  {
    fprintf(stderr, "Erreur : parametre invalide.\n");
    return -1;
  }

  fichier = fopen(nom_de_fichier, "a");
  if (fichier == NULL)
  {
    perror(nom_de_fichier);
    return -1;
  }

  if (fputs(message, fichier) == EOF)
  {
    perror("ecriture");
    fclose(fichier);
    return -1;
  }

  /* on termine la ligne si le message ne le fait pas deja */
  longueur = strlen(message);
  if (longueur == 0 || message[longueur - 1] != '\n')
  {
    fputc('\n', fichier);
  }

  fclose(fichier);

  printf("Le message a ete ecrit dans le fichier %s.\n", nom_de_fichier);

  return 0;
}

/* Retire le retour a la ligne laisse par fgets. */
static void enleve_retour_ligne(char *chaine)
{
  size_t longueur = strlen(chaine);

  if (longueur > 0 && chaine[longueur - 1] == '\n')
  {
    chaine[longueur - 1] = '\0';
  }
}

/*
 * Fonction d'entree de l'exercice 4.2 : propose a l'utilisateur de lire
 * un fichier ou d'y ecrire.
 */
int exercice_fichier(void)
{
  int choix;
  char nom_de_fichier[256];
  char message[TAILLE_LIGNE];

  printf("Que souhaitez-vous faire ?\n");
  printf("1. Lire un fichier\n");
  printf("2. Ecrire dans un fichier\n");
  printf("Votre choix : ");

  if (scanf("%d", &choix) != 1)
  {
    fprintf(stderr, "Erreur de saisie.\n");
    return -1;
  }

  /* on vide la fin de la ligne laissee par scanf */
  {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF)
    {
      /* rien */
    }
  }

  printf("\nEntrez le nom du fichier : ");
  if (fgets(nom_de_fichier, sizeof(nom_de_fichier), stdin) == NULL)
  {
    fprintf(stderr, "Erreur de saisie.\n");
    return -1;
  }
  enleve_retour_ligne(nom_de_fichier);

  switch (choix)
  {
  case 1:
    return lire_fichier(nom_de_fichier);

  case 2:
    printf("Entrez le message a ecrire : ");
    if (fgets(message, sizeof(message), stdin) == NULL)
    {
      fprintf(stderr, "Erreur de saisie.\n");
      return -1;
    }
    enleve_retour_ligne(message);
    return ecrire_dans_fichier(nom_de_fichier, message);

  default:
    fprintf(stderr, "Choix invalide.\n");
    return -1;
  }
}
