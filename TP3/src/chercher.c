/*
 * Exercice 3.4 - Recherche d'un entier dans un tableau
 *
 * Recherche sequentielle (lineaire) : on parcourt le tableau du debut a
 * la fin en comparant chaque element a la valeur recherchee.
 *
 * Compilation : gcc -Wall -Wextra -o chercher chercher.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

/* Recherche sequentielle : renvoie l'indice de `valeur` dans le
 * tableau, ou -1 si elle est absente. */
static int recherche_sequentielle(const int *tableau, int taille, int valeur)
{
  int i;

  for (i = 0; i < taille; i++)
  {
    if (tableau[i] == valeur)
    {
      return i; /* trouve : on renvoie la position */
    }
  }

  return -1; /* absent */
}

int main(void)
{
  int tableau[TAILLE];
  int i;
  int recherche;
  int position;

  srand((unsigned int)time(NULL));

  /* des valeurs entre 1 et 200 : on a de bonnes chances d'en trouver */
  for (i = 0; i < TAILLE; i++)
  {
    tableau[i] = (rand() % 200) + 1;
  }

  printf("Tableau :\n");
  for (i = 0; i < TAILLE; i++)
  {
    printf("%4d", tableau[i]);
    if ((i + 1) % 10 == 0)
    {
      printf("\n");
    }
  }

  printf("\nEntrez l'entier que vous souhaitez chercher : ");
  if (scanf("%d", &recherche) != 1)
  {
    printf("\nEntree invalide.\n");
    return 1;
  }

  position = recherche_sequentielle(tableau, TAILLE, recherche);

  if (position >= 0)
  {
    printf("\nResultat : entier present (a la position %d)\n", position);
  }
  else
  {
    printf("\nResultat : entier absent\n");
  }

  return 0;
}
