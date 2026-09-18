/*
 * Exercice 2.4 - Manipulation de chaines de caracteres
 *
 * Trois operations sont reimplementees "a la main", sans utiliser
 * <string.h> ni aucune autre bibliotheque :
 *   - ma_longueur      : compte les caracteres jusqu'au caractere nul '\0'
 *   - ma_copie         : copie une chaine source dans une chaine destination
 *   - ma_concatenation : ajoute une chaine a la fin d'une autre
 *
 * (printf n'est utilise que pour l'affichage du resultat.)
 *
 * Compilation : gcc -Wall -Wextra -o chaine chaine.c
 */

#include <stdio.h>

/* Renvoie le nombre de caracteres d'une chaine, sans compter le '\0'. */
static int ma_longueur(const char *chaine)
{
  int longueur = 0;

  /* on avance tant que l'on n'a pas atteint la fin de la chaine */
  while (chaine[longueur] != '\0')
  {
    longueur++;
  }

  return longueur;
}

/* Copie la chaine `source` (y compris le '\0') dans `destination`.
 * Renvoie `destination`. */
static char *ma_copie(char *destination, const char *source)
{
  int i = 0;

  while (source[i] != '\0')
  {
    destination[i] = source[i];
    i++;
  }

  /* ne pas oublier de terminer la chaine copiee */
  destination[i] = '\0';

  return destination;
}

/* Ajoute la chaine `source` a la fin de la chaine `destination`.
 * Renvoie `destination`. */
static char *ma_concatenation(char *destination, const char *source)
{
  int fin = 0;
  int i = 0;

  /* on cherche d'abord la fin de la premiere chaine */
  while (destination[fin] != '\0')
  {
    fin++;
  }

  /* puis on recopie la deuxieme chaine a partir de cet emplacement */
  while (source[i] != '\0')
  {
    destination[fin + i] = source[i];
    i++;
  }

  destination[fin + i] = '\0';

  return destination;
}

int main(void)
{
  const char chaine1[] = "Hello";
  const char chaine2[] = " World!";

  char copie[100];
  char concatenation[100];

  /* 1. longueur des chaines */
  printf("chaine1 = \"%s\" (longueur : %d)\n", chaine1, ma_longueur(chaine1));
  printf("chaine2 = \"%s\" (longueur : %d)\n", chaine2, ma_longueur(chaine2));
  printf("longueur totale : %d\n\n", ma_longueur(chaine1) + ma_longueur(chaine2));

  /* 2. copie de chaine1 dans copie */
  ma_copie(copie, chaine1);
  printf("copie de chaine1     : \"%s\" (longueur : %d)\n", copie, ma_longueur(copie));

  /* 3. concatenation de chaine1 et chaine2 */
  ma_copie(concatenation, chaine1);
  ma_concatenation(concatenation, chaine2);
  printf("concatenation        : \"%s\" (longueur : %d)\n",
         concatenation, ma_longueur(concatenation));

  return 0;
}
