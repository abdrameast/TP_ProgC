/*
 * Exercice 4.3 - Gestion d'une base de donnees etudiante
 *
 * Les details de 5 etudiant.e.s sont saisis au clavier, stockes dans un
 * tableau de structures (comme dans etudiant2.c du TP2), puis ecrits
 * dans le fichier etudiant.txt a l'aide de la fonction
 * ecrire_dans_fichier() de fichier.c. Chaque etudiant.e occupe une
 * ligne distincte du fichier.
 *
 * Compilation : gcc -Wall -Wextra -o etudiant_bd etudiant_bd.c fichier.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fichier.h"

#define NB_ETUDIANTS 5
#define TAILLE_TEXTE 64
#define TAILLE_LIGNE 512
#define NOM_FICHIER "etudiant.txt"

/* La structure d'un.e etudiant.e (reprise de etudiant2.c). */
struct etudiant
{
  char nom[TAILLE_TEXTE];
  char prenom[TAILLE_TEXTE];
  char adresse[TAILLE_TEXTE];
  float note1; /* Programmation en C */
  float note2; /* Systeme d'exploitation */
};

/* Vide ce qui reste de la ligne courante sur l'entree standard. */
static void vide_ligne(void)
{
  int caractere;

  while ((caractere = getchar()) != '\n' && caractere != EOF)
  {
    /* rien */
  }
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

int main(void)
{
  struct etudiant etudiants[NB_ETUDIANTS];
  char ligne[TAILLE_LIGNE];
  int i;

  for (i = 0; i < NB_ETUDIANTS; i++)
  {
    printf("Entrez les details de l'etudiant.e %d :\n", i + 1);

    /* nom et prenom : un seul mot, lus avec scanf */
    printf("Nom : ");
    if (scanf("%63s", etudiants[i].nom) != 1)
    {
      fprintf(stderr, "Erreur de saisie du nom.\n");
      return EXIT_FAILURE;
    }

    printf("Prenom : ");
    if (scanf("%63s", etudiants[i].prenom) != 1)
    {
      fprintf(stderr, "Erreur de saisie du prenom.\n");
      return EXIT_FAILURE;
    }

    /* l'adresse contient des espaces : scanf("%s") s'arreterait au
     * premier espace, on utilise donc fgets */
    vide_ligne();
    printf("Adresse : ");
    if (fgets(etudiants[i].adresse, TAILLE_TEXTE, stdin) == NULL)
    {
      fprintf(stderr, "Erreur de saisie de l'adresse.\n");
      return EXIT_FAILURE;
    }
    enleve_retour_ligne(etudiants[i].adresse);

    printf("Note 1 : ");
    if (scanf("%f", &etudiants[i].note1) != 1)
    {
      fprintf(stderr, "Erreur de saisie de la note 1.\n");
      return EXIT_FAILURE;
    }

    printf("Note 2 : ");
    if (scanf("%f", &etudiants[i].note2) != 1)
    {
      fprintf(stderr, "Erreur de saisie de la note 2.\n");
      return EXIT_FAILURE;
    }

    printf("\n");
  }

  /* ecriture des donnees : une ligne par etudiant.e */
  for (i = 0; i < NB_ETUDIANTS; i++)
  {
    snprintf(ligne, sizeof(ligne), "%s;%s;%s;%.2f;%.2f",
             etudiants[i].nom,
             etudiants[i].prenom,
             etudiants[i].adresse,
             etudiants[i].note1,
             etudiants[i].note2);

    if (ecrire_dans_fichier(NOM_FICHIER, ligne) != 0)
    {
      fprintf(stderr, "Erreur lors de l'ecriture dans %s.\n", NOM_FICHIER);
      return EXIT_FAILURE;
    }
  }

  printf("\nLes details des etudiants ont ete enregistres dans le fichier %s.\n",
         NOM_FICHIER);

  /* relecture du fichier pour verification */
  printf("\n");
  lire_fichier(NOM_FICHIER);

  return EXIT_SUCCESS;
}
