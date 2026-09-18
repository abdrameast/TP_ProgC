/*
 * Exercice 1.5 - Utilisation des operateurs arithmetiques et logiques
 *
 * a = 16 et b = 3
 *
 * Compilation : gcc -Wall -Wextra -o operateurs opérateurs.c
 */

#include <stdio.h>

int main(void)
{
  int a = 16;
  int b = 3;

  printf("a = %d, b = %d\n", a, b);
  printf("-----------------\n");

  /* 1. addition */
  printf("a + b  = %d\n", a + b);

  /* 2. soustraction */
  printf("a - b  = %d\n", a - b);

  /* 3. multiplication */
  printf("a * b  = %d\n", a * b);

  /* 4. division : entre deux entiers, la division est entiere (16 / 3 = 5).
   * On affiche aussi la division reelle grace a une conversion (cast). */
  printf("a / b  = %d (division entiere)\n", a / b);
  printf("a / b  = %f (division reelle)\n", (double)a / (double)b);

  /* 5. modulo : reste de la division entiere */
  printf("a %% b  = %d\n", a % b);

  /* 6. egalite : l'operateur == renvoie 1 (vrai) ou 0 (faux) */
  printf("a == b : %d\n", a == b);

  /* 7. superiorite */
  printf("a > b  : %d\n", a > b);

  return 0;
}
