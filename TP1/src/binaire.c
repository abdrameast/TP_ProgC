/*
 * Exercice 1.9 - Affichage d'un nombre en format binaire
 *
 * printf() ne dispose pas de code de conversion pour le binaire
 * (contrairement a %x pour l'hexadecimal ou %o pour l'octal).
 * On ecrit donc notre propre conversion.
 *
 * Deux methodes sont montrees :
 *   1. avec les operateurs de manipulation de bits (decalage >> et
 *      masque & 1) : on parcourt les bits du plus fort au plus faible ;
 *   2. avec la division par 2 et le reste de la division (%).
 *
 * Compilation : gcc -Wall -Wextra -o binaire binaire.c
 */

#include <stdio.h>

/* Nombre de bits d'un int (8 bits par octet). */
#define NB_BITS ((int)(sizeof(int) * 8))

/* Methode 1 : decalage et masquage. */
static void affiche_binaire_bits(int nombre)
{
  /* On travaille sur une copie non signee : le decalage a droite d'une
   * valeur negative n'est pas portable. */
  unsigned int valeur = (unsigned int)nombre;
  int i;

  for (i = NB_BITS - 1; i >= 0; i--)
  {
    /* on ramene le bit numero i en position 0, puis on le masque */
    printf("%u", (valeur >> i) & 1U);

    /* un espace tous les 8 bits pour la lisibilite */
    if (i % 8 == 0 && i != 0)
    {
      printf(" ");
    }
  }
}

/* Methode 2 : divisions successives par 2 et restes. */
static void affiche_binaire_division(int nombre)
{
  unsigned int valeur = (unsigned int)nombre;
  int bits[NB_BITS];
  int i;

  /* les restes sont obtenus du bit de poids faible vers le poids fort,
   * on les stocke donc avant de les afficher a l'envers */
  for (i = 0; i < NB_BITS; i++)
  {
    bits[i] = (int)(valeur % 2);
    valeur = valeur / 2;
  }

  for (i = NB_BITS - 1; i >= 0; i--)
  {
    printf("%d", bits[i]);
  }
}

int main(void)
{
  /* les cinq nombres a tester */
  int nombres[] = {0, 4096, 65536, 65535, 1024};
  int nb = (int)(sizeof(nombres) / sizeof(nombres[0]));
  int i;

  printf("Representation binaire sur %d bits\n", NB_BITS);
  printf("---------------------------------\n");

  for (i = 0; i < nb; i++)
  {
    printf("%6d : ", nombres[i]);
    affiche_binaire_bits(nombres[i]);
    printf("\n");

    printf("         (divisions par 2) ");
    affiche_binaire_division(nombres[i]);
    printf("\n");
  }

  return 0;
}
