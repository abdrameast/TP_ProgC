/*
 * Exercice 1.10 - Generation d'une pyramide de nombres
 *
 * Exemple pour n = 5 :
 *       1
 *      121
 *     12321
 *    1234321
 *   123454321
 *
 * Chaque ligne i contient (n - i) espaces, puis les nombres croissants
 * de 1 a i, puis les nombres decroissants de i-1 a 1.
 *
 * Compilation : gcc -Wall -Wextra -o pyramide pyramide.c
 */

#include <stdio.h>

int main(void)
{
  int n = 5; /* hauteur de la pyramide */
  int i;
  int j;

  printf("Pyramide de hauteur %d :\n\n", n);

  /* une iteration par niveau de la pyramide */
  for (i = 1; i <= n; i++)
  {
    /* les espaces qui centrent la ligne */
    for (j = 1; j <= n - i; j++)
    {
      printf(" ");
    }

    /* les nombres croissants : 1, 2, ..., i */
    for (j = 1; j <= i; j++)
    {
      printf("%d", j);
    }

    /* les nombres decroissants : i-1, ..., 2, 1 */
    for (j = i - 1; j >= 1; j--)
    {
      printf("%d", j);
    }

    /* fin du niveau : passage a la ligne suivante */
    printf("\n");
  }

  printf("\nGeneration de la pyramide terminee.\n");

  return 0;
}
