/*
 * Exercice 3.6 - Affichage des octets de differents types de donnees
 *
 * Pour lire les octets d'une variable, on prend son adresse et on la
 * convertit en `unsigned char *` : un unsigned char occupe exactement
 * un octet, et ce type est le seul avec lequel il est legal de relire
 * la representation memoire de n'importe quelle variable.
 *
 * Les octets sont affiches dans l'ordre ou ils se trouvent en memoire.
 * Sur une machine petit-boutiste (little-endian, cas des processeurs
 * x86), l'octet de poids faible apparait en premier.
 *
 * Remarque : sur x86-64, un long double occupe 16 octets alors que le
 * format x87 n'en utilise que 10 ; les 6 derniers octets affiches sont
 * du remplissage (padding) non initialise.
 *
 * Compilation : gcc -Wall -Wextra -o octets octets.c
 */

#include <stdio.h>

/* Affiche les `taille` octets situes a l'adresse `adresse`. */
static void affiche_octets(const char *nom, const void *adresse, size_t taille)
{
  const unsigned char *octets = (const unsigned char *)adresse;
  size_t i;

  printf("Octets de %s :\n", nom);
  for (i = 0; i < taille; i++)
  {
    printf(" %02x", octets[i]);
  }
  printf("\n\n");
}

int main(void)
{
  short s = 0x0302;
  int i = 0x04030201;
  long int li = 0x0807060504030201L;
  float f = 5.0f;
  double d = 1.0;
  long double ld = 1.0L;

  /* test de boutisme : on regarde le premier octet d'un int connu */
  unsigned int test = 1;
  const unsigned char *premier = (const unsigned char *)&test;

  printf("Architecture : %s\n\n",
         (*premier == 1) ? "petit-boutiste (little-endian)"
                         : "gros-boutiste (big-endian)");

  affiche_octets("short", &s, sizeof(s));
  affiche_octets("int", &i, sizeof(i));
  affiche_octets("long int", &li, sizeof(li));
  affiche_octets("float", &f, sizeof(f));
  affiche_octets("double", &d, sizeof(d));
  affiche_octets("long double", &ld, sizeof(ld));

  return 0;
}
