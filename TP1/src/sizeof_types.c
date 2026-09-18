/*
 * Exercice 1.3 - Tailles des types de base (en octets)
 *
 * L'operateur sizeof renvoie une valeur de type size_t : on l'affiche
 * avec le code de conversion %zu.
 *
 * Attention : les types float, double et long double n'ont pas de
 * version signed / unsigned.
 *
 * Compilation : gcc -Wall -Wextra -o sizeof_types sizeof_types.c
 */

#include <stdio.h>

int main(void)
{
  printf("Tailles des types de base (en octets)\n");
  printf("-------------------------------------\n");

  /* i. char */
  printf("char                   : %zu\n", sizeof(char));
  printf("signed char            : %zu\n", sizeof(signed char));
  printf("unsigned char          : %zu\n", sizeof(unsigned char));

  /* ii. short */
  printf("short                  : %zu\n", sizeof(short));
  printf("signed short           : %zu\n", sizeof(signed short));
  printf("unsigned short         : %zu\n", sizeof(unsigned short));

  /* iii. int */
  printf("int                    : %zu\n", sizeof(int));
  printf("signed int             : %zu\n", sizeof(signed int));
  printf("unsigned int           : %zu\n", sizeof(unsigned int));

  /* iv. long int */
  printf("long int               : %zu\n", sizeof(long int));
  printf("signed long int        : %zu\n", sizeof(signed long int));
  printf("unsigned long int      : %zu\n", sizeof(unsigned long int));

  /* v. long long int */
  printf("long long int          : %zu\n", sizeof(long long int));
  printf("signed long long int   : %zu\n", sizeof(signed long long int));
  printf("unsigned long long int : %zu\n", sizeof(unsigned long long int));

  /* vi. float (pas de version signed / unsigned) */
  printf("float                  : %zu\n", sizeof(float));

  /* vii. double (pas de version signed / unsigned) */
  printf("double                 : %zu\n", sizeof(double));

  /* viii. long double (pas de version signed / unsigned) */
  printf("long double            : %zu\n", sizeof(long double));

  return 0;
}
