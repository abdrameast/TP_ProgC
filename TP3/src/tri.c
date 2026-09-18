/*
 * Exercice 3.3 - Tri croissant d'un tableau
 *
 * Le tableau de 100 entiers est trie par ordre croissant avec le
 * tri a bulles (bubble sort) : a chaque passage, les elements voisins
 * mal ordonnes sont echanges, et le plus grand element "remonte" a la
 * fin du tableau.
 *
 * Compilation : gcc -Wall -Wextra -o tri tri.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

/* Affiche un tableau, 10 valeurs par ligne. */
static void affiche(const char *titre, const int *tableau, int taille)
{
  int i;

  printf("%s\n", titre);
  for (i = 0; i < taille; i++)
  {
    printf("%5d", tableau[i]);
    if ((i + 1) % 10 == 0)
    {
      printf("\n");
    }
  }
  printf("\n");
}

/* Tri a bulles : trie `tableau` par ordre croissant. */
static void tri_a_bulles(int *tableau, int taille)
{
  int i;
  int j;
  int echange; /* permet d'arreter des que le tableau est trie */

  for (i = 0; i < taille - 1; i++)
  {
    echange = 0;

    /* les i derniers elements sont deja a leur place */
    for (j = 0; j < taille - 1 - i; j++)
    {
      if (tableau[j] > tableau[j + 1])
      {
        int temporaire = tableau[j];
        tableau[j] = tableau[j + 1];
        tableau[j + 1] = temporaire;
        echange = 1;
      }
    }

    /* aucun echange : le tableau est deja trie */
    if (echange == 0)
    {
      break;
    }
  }
}

int main(void)
{
  int tableau[TAILLE];
  int i;

  srand((unsigned int)time(NULL));

  /* des valeurs entre -50 et 949 pour avoir aussi des nombres negatifs */
  for (i = 0; i < TAILLE; i++)
  {
    tableau[i] = (rand() % 1000) - 50;
  }

  affiche("Tableau non trie :", tableau, TAILLE);

  tri_a_bulles(tableau, TAILLE);

  affiche("Tableau trie par ordre croissant :", tableau, TAILLE);

  return 0;
}
