/*
 * Exercice 2.7 - Gestion des couleurs au format RGBA avec des structures
 *
 * Chaque composante (rouge, vert, bleu, alpha) tient sur un octet :
 * on utilise donc le type uint8_t de <stdint.h>.
 *
 * Compilation : gcc -Wall -Wextra -o couleurs couleurs.c
 */

#include <stdint.h>
#include <stdio.h>

#define NB_COULEURS 10

/* Une couleur au format RGBA : 4 octets. */
struct couleur_rgba
{
  uint8_t rouge;
  uint8_t vert;
  uint8_t bleu;
  uint8_t alpha;
};

int main(void)
{
  /* initialisation des 10 couleurs en notation hexadecimale */
  struct couleur_rgba couleurs[NB_COULEURS] = {
      {0xef, 0x78, 0x12, 0xff},
      {0x2c, 0xc8, 0x64, 0xff},
      {0xff, 0x00, 0x00, 0xff}, /* rouge pur */
      {0x00, 0xff, 0x00, 0xff}, /* vert pur */
      {0x00, 0x00, 0xff, 0xff}, /* bleu pur */
      {0xff, 0xff, 0x00, 0x80}, /* jaune semi-transparent */
      {0x00, 0xff, 0xff, 0xff}, /* cyan */
      {0xff, 0x00, 0xff, 0xff}, /* magenta */
      {0x80, 0x80, 0x80, 0xff}, /* gris */
      {0x00, 0x00, 0x00, 0x00}  /* noir totalement transparent */
  };

  int i;

  for (i = 0; i < NB_COULEURS; i++)
  {
    printf("Couleur %d :\n", i + 1);
    printf("Rouge : %u\n", couleurs[i].rouge);
    printf("Vert : %u\n", couleurs[i].vert);
    printf("Bleu : %u\n", couleurs[i].bleu);
    printf("Alpha : %u\n", couleurs[i].alpha);
    /* la meme couleur en notation hexadecimale */
    printf("Hexadecimal : #%02x%02x%02x%02x\n",
           couleurs[i].rouge, couleurs[i].vert,
           couleurs[i].bleu, couleurs[i].alpha);
    printf("\n");
  }

  return 0;
}
