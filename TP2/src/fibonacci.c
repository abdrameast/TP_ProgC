/*
 * Exercice 2.3 - Generation de la suite de Fibonacci
 *
 *   U0 = 0
 *   U1 = 1
 *   Un = U(n-1) + U(n-2)
 *
 * Le programme affiche les termes U0, U1, ..., Un en indiquant l'indice
 * de chaque terme (l'enonce donne l'exemple "0, 1, 1, 2, 3, 5, 8" pour
 * n = 7 : ce sont les 7 premiers termes, soit U0 a U6).
 *
 * Compilation : gcc -Wall -Wextra -o fibonacci fibonacci.c
 */

#include <stdio.h>

int main(void)
{
  int n = 7; /* on genere la suite jusqu'a Un */
  int i;

  /* les deux termes precedents : U(n-2) et U(n-1) */
  long long precedent = 0; /* U0 */
  long long courant = 1;   /* U1 */
  long long terme;

  printf("Suite de Fibonacci de U0 a U%d :\n\n", n);

  for (i = 0; i <= n; i++)
  {
    if (i == 0)
    {
      terme = precedent; /* U0 = 0 */
    }
    else if (i == 1)
    {
      terme = courant; /* U1 = 1 */
    }
    else
    {
      /* Un = U(n-1) + U(n-2) */
      terme = courant + precedent;
      precedent = courant;
      courant = terme;
    }

    printf("U%-2d = %lld\n", i, terme);
  }

  /* la meme suite affichee sur une seule ligne */
  precedent = 0;
  courant = 1;
  printf("\nSuite : ");
  for (i = 0; i <= n; i++)
  {
    if (i == 0)
    {
      terme = precedent;
    }
    else if (i == 1)
    {
      terme = courant;
    }
    else
    {
      terme = courant + precedent;
      precedent = courant;
      courant = terme;
    }

    printf("%lld", terme);
    if (i < n)
    {
      printf(", ");
    }
  }
  printf("\n");

  return 0;
}
