/*
 * Exercice 1.8 - Utilisation de l'operateur switch pour des operations
 *                mathematiques
 *
 * op contient l'un des operateurs : '+', '-', '*', '/', '%', '&', '|', '~'
 * L'operateur '~' est unaire : il est applique a num1.
 *
 * Compilation : gcc -Wall -Wextra -o calculs calculs.c
 */

#include <stdio.h>

/* Effectue l'operation `op` sur num1 et num2 et affiche le resultat. */
static void calcule(int num1, int num2, char op)
{
  switch (op)
  {
  case '+': /* addition */
    printf("%d %c %d = %d\n", num1, op, num2, num1 + num2);
    break;

  case '-': /* soustraction */
    printf("%d %c %d = %d\n", num1, op, num2, num1 - num2);
    break;

  case '*': /* multiplication */
    printf("%d %c %d = %d\n", num1, op, num2, num1 * num2);
    break;

  case '/': /* division entiere */
    if (num2 == 0)
    {
      printf("%d %c %d = erreur : division par zero\n", num1, op, num2);
    }
    else
    {
      printf("%d %c %d = %d\n", num1, op, num2, num1 / num2);
    }
    break;

  case '%': /* reste de la division entiere */
    if (num2 == 0)
    {
      printf("%d %c %d = erreur : modulo par zero\n", num1, op, num2);
    }
    else
    {
      printf("%d %c %d = %d\n", num1, op, num2, num1 % num2);
    }
    break;

  case '&': /* ET bit a bit */
    printf("%d %c %d = %d\n", num1, op, num2, num1 & num2);
    break;

  case '|': /* OU bit a bit */
    printf("%d %c %d = %d\n", num1, op, num2, num1 | num2);
    break;

  case '~': /* NON bit a bit : operateur unaire applique a num1 */
    printf("%c%d = %d\n", op, num1, ~num1);
    break;

  default:
    printf("Operateur inconnu : '%c'\n", op);
    break;
  }
}

int main(void)
{
  int num1 = 16;
  int num2 = 3;
  char op;

  /* on teste successivement tous les operateurs demandes */
  char operateurs[] = {'+', '-', '*', '/', '%', '&', '|', '~'};
  int nb_operateurs = (int)(sizeof(operateurs) / sizeof(operateurs[0]));
  int i;

  printf("num1 = %d, num2 = %d\n", num1, num2);
  printf("--------------------\n");

  for (i = 0; i < nb_operateurs; i++)
  {
    op = operateurs[i];
    calcule(num1, num2, op);
  }

  /* un deuxieme jeu de valeurs, dont une division par zero */
  num1 = -25;
  num2 = 0;
  printf("\nnum1 = %d, num2 = %d\n", num1, num2);
  printf("--------------------\n");
  for (i = 0; i < nb_operateurs; i++)
  {
    calcule(num1, num2, operateurs[i]);
  }

  /* un operateur non pris en charge */
  printf("\n");
  calcule(4, 5, '^');

  return 0;
}
