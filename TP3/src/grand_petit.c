/*
 * Exercice 3.2 - Trouver le numero le plus grand et le plus petit dans
 *                un tableau
 *
 * Le tableau contient 100 entiers aleatoires compris entre 1 et 1000.
 *
 * Compilation : gcc -Wall -Wextra -o grand_petit grand_petit.c
 */

#include <stdio.h>
#include <stdlib.h> /* rand, srand */
#include <time.h>   /* time */

#define TAILLE 100

int main(void)
{
  int tableau[TAILLE];
  int i;
  int plus_grand;
  int plus_petit;

  /* initialisation du generateur de nombres aleatoires */
  srand((unsigned int)time(NULL));

  /* remplissage du tableau avec des valeurs entre 1 et 1000 (inclus) */
  for (i = 0; i < TAILLE; i++)
  {
    tableau[i] = (rand() % 1000) + 1;
  }

  printf("Tableau :\n");
  for (i = 0; i < TAILLE; i++)
  {
    printf("%4d ", tableau[i]);
    if ((i + 1) % 10 == 0)
    {
      printf("\n");
    }
  }
  printf("\n");

  /* on part du premier element et on compare avec tous les autres */
  plus_grand = tableau[0];
  plus_petit = tableau[0];

  for (i = 1; i < TAILLE; i++)
  {
    if (tableau[i] > plus_grand)
    {
      plus_grand = tableau[i];
    }
    if (tableau[i] < plus_petit)
    {
      plus_petit = tableau[i];
    }
  }

  printf("Le numero le plus grand est : %d\n", plus_grand);
  printf("Le numero le plus petit est : %d\n", plus_petit);

  return 0;
}
