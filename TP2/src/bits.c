/*
 * Exercice 2.2 - Verification des bits
 *
 * On verifie si le 4eme et le 20eme bit *en partant de la gauche*
 * d'un entier `d` valent 1.
 *
 * Un int occupe 32 bits. En partant de la gauche, le bit numero n
 * correspond au decalage (32 - n) :
 *   - 4eme bit de gauche  -> bit de poids 32 - 4  = 28
 *   - 20eme bit de gauche -> bit de poids 32 - 20 = 12
 *
 * On extrait chaque bit avec un decalage (>>) suivi d'un masque (& 1).
 *
 * Compilation : gcc -Wall -Wextra -o bits bits.c
 */

#include <stdio.h>

int main(void)
{
  /* NB_BITS vaut 32 sur une machine ou un int occupe 4 octets */
  const int nb_bits = (int)(sizeof(int) * 8);
  const int position4 = 4;   /* 4eme bit en partant de la gauche */
  const int position20 = 20; /* 20eme bit en partant de la gauche */

  /* bits 28 et 12 a 1 : 0x10001000 = 268439552 */
  unsigned int d = 0x10001000;

  /* decalages correspondants */
  int decalage4 = nb_bits - position4;   /* 28 */
  int decalage20 = nb_bits - position20; /* 12 */

  /* extraction des deux bits par decalage puis masquage */
  unsigned int bit4 = (d >> decalage4) & 1U;
  unsigned int bit20 = (d >> decalage20) & 1U;

  /* affichage de la representation binaire pour verification */
  int i;
  printf("d = 0x%08x = ", d);
  for (i = nb_bits - 1; i >= 0; i--)
  {
    printf("%u", (d >> i) & 1U);
  }
  printf("\n");

  printf("4eme bit de gauche (poids %d)  : %u\n", decalage4, bit4);
  printf("20eme bit de gauche (poids %d) : %u\n", decalage20, bit20);

  /* les deux bits valent-ils 1 ? */
  if (bit4 == 1U && bit20 == 1U)
  {
    printf("1\n");
  }
  else
  {
    printf("0\n");
  }

  return 0;
}
