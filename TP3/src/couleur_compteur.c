/*
 * Exercice 3.7 - Compter les couleurs distinctes dans un tableau
 *
 * Un tableau de 100 couleurs RGBA est genere, puis le programme affiche
 * chaque couleur distincte accompagnee de son nombre d'occurrences.
 *
 * Deux structures sont utilisees :
 *   - `couleur`          : les quatre composantes R, G, B, A ;
 *   - `couleur_compteur` : une couleur distincte et son compteur.
 *
 * Compilation : gcc -Wall -Wextra -o couleur_compteur couleur_compteur.c
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_COULEURS 100

/* Une couleur : R, G, B et A, chacun sur un octet. */
struct couleur
{
  uint8_t rouge;
  uint8_t vert;
  uint8_t bleu;
  uint8_t alpha;
};

/* Une couleur distincte et son nombre d'occurrences. */
struct couleur_compteur
{
  struct couleur c;
  int compte;
};

/* Renvoie 1 si les deux couleurs sont identiques, 0 sinon. */
static int couleurs_egales(const struct couleur *c1, const struct couleur *c2)
{
  return (c1->rouge == c2->rouge &&
          c1->vert == c2->vert &&
          c1->bleu == c2->bleu &&
          c1->alpha == c2->alpha);
}

int main(void)
{
  struct couleur couleurs[NB_COULEURS];

  /* au pire, les 100 couleurs sont toutes differentes */
  struct couleur_compteur distinctes[NB_COULEURS];
  int nb_distinctes = 0;

  int i;
  int j;

  srand((unsigned int)time(NULL));

  /* Generation de 100 couleurs. On tire les composantes parmi un petit
   * ensemble de valeurs pour que des couleurs se repetent. */
  {
    const uint8_t valeurs[] = {0x00, 0x23, 0x45};
    const int nb_valeurs = (int)(sizeof(valeurs) / sizeof(valeurs[0]));

    for (i = 0; i < NB_COULEURS; i++)
    {
      couleurs[i].rouge = 0xff;
      couleurs[i].vert = valeurs[rand() % nb_valeurs];
      couleurs[i].bleu = valeurs[rand() % nb_valeurs];
      couleurs[i].alpha = valeurs[rand() % nb_valeurs];
    }
  }

  printf("Tableau des %d couleurs :\n", NB_COULEURS);
  for (i = 0; i < NB_COULEURS; i++)
  {
    printf("0x%02x 0x%02x 0x%02x 0x%02x\n",
           couleurs[i].rouge, couleurs[i].vert,
           couleurs[i].bleu, couleurs[i].alpha);
  }

  /* Comptage : pour chaque couleur du tableau, on cherche si elle est
   * deja connue. Si oui on incremente son compteur, sinon on l'ajoute
   * a la liste des couleurs distinctes. */
  for (i = 0; i < NB_COULEURS; i++)
  {
    int trouvee = 0;

    for (j = 0; j < nb_distinctes; j++)
    {
      if (couleurs_egales(&couleurs[i], &distinctes[j].c))
      {
        distinctes[j].compte++;
        trouvee = 1;
        break;
      }
    }

    if (!trouvee)
    {
      distinctes[nb_distinctes].c = couleurs[i];
      distinctes[nb_distinctes].compte = 1;
      nb_distinctes++;
    }
  }

  printf("\nCouleurs distinctes (%d) et nombre d'occurrences :\n", nb_distinctes);
  for (j = 0; j < nb_distinctes; j++)
  {
    printf("0x%02x 0x%02x 0x%02x 0x%02x : %d\n",
           distinctes[j].c.rouge, distinctes[j].c.vert,
           distinctes[j].c.bleu, distinctes[j].c.alpha,
           distinctes[j].compte);
  }

  return 0;
}
