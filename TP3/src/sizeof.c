/*
 * Exercice 3.1 - Comprendre la taille des types de donnees
 *
 * Sur une machine 64 bits, tous les pointeurs occupent la meme taille
 * (8 octets), quel que soit le type pointe et le niveau d'indirection :
 * un pointeur ne contient qu'une adresse memoire.
 *
 * Compilation : gcc -Wall -Wextra -o sizeof sizeof.c
 */

#include <stdio.h>

int main(void)
{
  /* types de base */
  printf("La taille de char est : %zu octets\n", sizeof(char));
  printf("La taille de short est : %zu octets\n", sizeof(short));
  printf("La taille de int est : %zu octets\n", sizeof(int));
  printf("La taille de long int est : %zu octets\n", sizeof(long int));
  printf("La taille de long long int est : %zu octets\n", sizeof(long long int));
  printf("La taille de float est : %zu octets\n", sizeof(float));
  printf("La taille de double est : %zu octets\n", sizeof(double));
  printf("La taille de long double est : %zu octets\n", sizeof(long double));
  printf("\n");

  /* pointeurs sur int */
  printf("La taille de int* est : %zu octets\n", sizeof(int *));
  printf("La taille de int** est : %zu octets\n", sizeof(int **));
  printf("La taille de int*** est : %zu octets\n", sizeof(int ***));
  printf("\n");

  /* pointeurs sur char */
  printf("La taille de char* est : %zu octets\n", sizeof(char *));
  printf("La taille de char** est : %zu octets\n", sizeof(char **));
  printf("La taille de char*** est : %zu octets\n", sizeof(char ***));
  printf("\n");

  /* pointeurs sur float */
  printf("La taille de float* est : %zu octets\n", sizeof(float *));
  printf("La taille de float** est : %zu octets\n", sizeof(float **));
  printf("La taille de float*** est : %zu octets\n", sizeof(float ***));
  printf("\n");

  /* pointeurs sur double et sur void */
  printf("La taille de double* est : %zu octets\n", sizeof(double *));
  printf("La taille de void* est : %zu octets\n", sizeof(void *));

  return 0;
}
