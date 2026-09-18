/*
 * Exercice 1.2 - Calcul de l'aire et du perimetre d'un cercle
 *
 * Compilation : gcc -Wall -Wextra -o cercle cercle.c -lm
 * Execution   : ./cercle
 */

#include <math.h> /* pour la constante M_PI */
#include <stdio.h>

int main(void)
{
  /* rayon du cercle */
  double rayon = 6.0;

  /* aire = pi * rayon * rayon */
  double aire = M_PI * rayon * rayon;

  /* perimetre = 2 * pi * rayon */
  double perimetre = 2.0 * M_PI * rayon;

  printf("Rayon du cercle    : %f\n", rayon);
  printf("Aire du cercle     : %f\n", aire);
  printf("Perimetre du cercle: %f\n", perimetre);

  return 0;
}
