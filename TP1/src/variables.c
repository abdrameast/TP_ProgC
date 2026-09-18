/*
 * Exercice 1.4 - Affectation et affichage des variables de types de base
 *
 * Chaque type possede son propre code de conversion pour printf :
 *   char       -> %c (et %d pour la valeur numerique)
 *   short      -> %hd / %hu
 *   int        -> %d  / %u
 *   long       -> %ld / %lu
 *   long long  -> %lld / %llu
 *   float      -> %f
 *   double     -> %lf
 *   long double-> %Lf
 *
 * Compilation : gcc -Wall -Wextra -o variables variables.c
 */

#include <stdio.h>

int main(void)
{
  /* i. char */
  char c = 'A';
  signed char sc = -128;
  unsigned char uc = 255;

  /* ii. short */
  short s = -32768;
  signed short ss = -1234;
  unsigned short us = 65535;

  /* iii. int */
  int i = -2147483647;
  signed int si = -42;
  unsigned int ui = 4294967295U;

  /* iv. long int */
  long int li = -1234567890L;
  signed long int sli = 1234567890L;
  unsigned long int uli = 4294967295UL;

  /* v. long long int */
  long long int lli = -123456789012345LL;
  signed long long int slli = 123456789012345LL;
  unsigned long long int ulli = 18446744073709551615ULL;

  /* vi. float (pas de version signed / unsigned) */
  float f = 3.14159f;

  /* vii. double (pas de version signed / unsigned) */
  double d = 2.718281828459045;

  /* viii. long double (pas de version signed / unsigned) */
  long double ld = 1.6180339887498948482L;

  printf("Valeurs des variables de types de base\n");
  printf("--------------------------------------\n");

  printf("char                   : %c (valeur numerique : %d)\n", c, c);
  printf("signed char            : %d\n", sc);
  printf("unsigned char          : %u\n", uc);

  printf("short                  : %hd\n", s);
  printf("signed short           : %hd\n", ss);
  printf("unsigned short         : %hu\n", us);

  printf("int                    : %d\n", i);
  printf("signed int             : %d\n", si);
  printf("unsigned int           : %u\n", ui);

  printf("long int               : %ld\n", li);
  printf("signed long int        : %ld\n", sli);
  printf("unsigned long int      : %lu\n", uli);

  printf("long long int          : %lld\n", lli);
  printf("signed long long int   : %lld\n", slli);
  printf("unsigned long long int : %llu\n", ulli);

  printf("float                  : %f\n", f);
  printf("double                 : %lf\n", d);
  printf("long double            : %Lf\n", ld);

  return 0;
}
