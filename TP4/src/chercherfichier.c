/*
 * Exercice 4.6 - Recherche de phrases dans un fichier
 *
 * Le programme lit un fichier ligne par ligne et compte, pour chaque
 * ligne, le nombre d'occurrences de la phrase recherchee. Les lignes
 * contenant la phrase sont affichees avec leur numero et le nombre
 * d'occurrences.
 *
 * Compilation : gcc -Wall -Wextra -o chercherfichier chercherfichier.c
 *
 * Utilisation :
 *   $ ./chercherfichier fichier.txt
 *   Entrez la phrase que vous souhaitez rechercher : exemple de phrase
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_LIGNE 4096

/* Retire le retour a la ligne laisse par fgets. */
static void enleve_retour_ligne(char *chaine)
{
  size_t longueur = strlen(chaine);

  if (longueur > 0 && chaine[longueur - 1] == '\n')
  {
    chaine[longueur - 1] = '\0';
  }
}

/* Compare `motif` au debut de `texte`.
 * Renvoie 1 si `texte` commence par `motif`, 0 sinon. */
static int commence_par(const char *texte, const char *motif)
{
  size_t i = 0;

  while (motif[i] != '\0')
  {
    if (texte[i] != motif[i])
    {
      return 0;
    }
    i++;
  }

  return 1;
}

/* Compte le nombre d'occurrences (eventuellement superposees exclues)
 * de `motif` dans `ligne`. */
static int compte_occurrences(const char *ligne, const char *motif)
{
  size_t longueur_motif = strlen(motif);
  size_t i = 0;
  int compte = 0;

  if (longueur_motif == 0)
  {
    return 0;
  }

  while (ligne[i] != '\0')
  {
    if (commence_par(&ligne[i], motif))
    {
      compte++;
      i += longueur_motif; /* on reprend apres l'occurrence trouvee */
    }
    else
    {
      i++;
    }
  }

  return compte;
}

int main(int argc, char *argv[])
{
  FILE *fichier;
  char nom_de_fichier[256];
  char phrase[TAILLE_LIGNE];
  char ligne[TAILLE_LIGNE];
  int numero_ligne = 0;
  int total = 0;

  /* le nom du fichier peut etre donne en argument, sinon on le demande */
  if (argc >= 2)
  {
    snprintf(nom_de_fichier, sizeof(nom_de_fichier), "%s", argv[1]);
  }
  else
  {
    printf("Entrez le nom du fichier : ");
    if (fgets(nom_de_fichier, sizeof(nom_de_fichier), stdin) == NULL)
    {
      fprintf(stderr, "Erreur de saisie.\n");
      return EXIT_FAILURE;
    }
    enleve_retour_ligne(nom_de_fichier);
  }

  printf("Entrez la phrase que vous souhaitez rechercher : ");
  if (fgets(phrase, sizeof(phrase), stdin) == NULL)
  {
    fprintf(stderr, "Erreur de saisie.\n");
    return EXIT_FAILURE;
  }
  enleve_retour_ligne(phrase);

  fichier = fopen(nom_de_fichier, "r");
  if (fichier == NULL)
  {
    perror(nom_de_fichier);
    return EXIT_FAILURE;
  }

  printf("\nResultats de la recherche :\n");

  /* parcours du fichier ligne par ligne */
  while (fgets(ligne, sizeof(ligne), fichier) != NULL)
  {
    int occurrences;

    numero_ligne++;
    enleve_retour_ligne(ligne);

    occurrences = compte_occurrences(ligne, phrase);
    if (occurrences > 0)
    {
      printf("Ligne %d, %d fois\n", numero_ligne, occurrences);
      total += occurrences;
    }
  }

  fclose(fichier);

  if (total == 0)
  {
    printf("Aucune occurrence trouvee dans %s.\n", nom_de_fichier);
  }
  else
  {
    printf("\nTotal : %d occurrence(s) dans %d ligne(s) lue(s).\n",
           total, numero_ligne);
  }

  return EXIT_SUCCESS;
}
