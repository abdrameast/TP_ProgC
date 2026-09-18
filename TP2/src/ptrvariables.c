/*
 * Exercice 2.8 - Manipulation des variables de types de base avec des
 *                pointeurs
 *
 * Reprise de variables.c (TP1, exercice 1.4) : chaque variable est
 * manipulee *via son adresse*, et l'on affiche l'adresse ainsi que la
 * representation hexadecimale de la valeur avant et apres modification.
 *
 * Pour afficher un nombre a virgule flottante en hexadecimal, on affiche
 * la representation binaire (IEEE 754) de la variable : une union permet
 * de relire les memes octets sous la forme d'un entier.
 *
 * Compilation : gcc -Wall -Wextra -o ptrvariables ptrvariables.c
 */

#include <stdint.h>
#include <stdio.h>

/* unions utilisees pour relire les octets d'un flottant sous forme
 * d'entier non signe (representation IEEE 754) */
union conv_float
{
  float f;
  uint32_t u;
};

union conv_double
{
  double d;
  uint64_t u;
};

/* Affiche les octets d'un long double (10 octets utiles sur x86). */
static void affiche_long_double_hex(const long double *pld)
{
  const unsigned char *octets = (const unsigned char *)pld;
  int i;

  /* affichage du poids fort vers le poids faible */
  for (i = (int)sizeof(long double) - 1; i >= 0; i--)
  {
    printf("%02x", octets[i]);
  }
}

/* Affiche l'adresse et la valeur (en hexadecimal) de chaque variable. */
static void affiche(const char *titre,
                    const char *pc, const short *ps, const int *pi,
                    const long int *pli, const long long int *plli,
                    const float *pf, const double *pd, const long double *pld,
                    const unsigned char *puc, const unsigned int *pui)
{
  union conv_float cf;
  union conv_double cd;

  cf.f = *pf;
  cd.d = *pd;

  printf("%s\n", titre);
  printf("Adresse de c   : %p, Valeur de c   : %x\n", (const void *)pc, (unsigned char)*pc);
  printf("Adresse de uc  : %p, Valeur de uc  : %x\n", (const void *)puc, *puc);
  printf("Adresse de s   : %p, Valeur de s   : %x\n", (const void *)ps, (unsigned short)*ps);
  printf("Adresse de i   : %p, Valeur de i   : %x\n", (const void *)pi, (unsigned int)*pi);
  printf("Adresse de ui  : %p, Valeur de ui  : %x\n", (const void *)pui, *pui);
  printf("Adresse de li  : %p, Valeur de li  : %lx\n", (const void *)pli, (unsigned long)*pli);
  printf("Adresse de lli : %p, Valeur de lli : %llx\n", (const void *)plli, (unsigned long long)*plli);
  printf("Adresse de f   : %p, Valeur de f   : %x\n", (const void *)pf, cf.u);
  printf("Adresse de d   : %p, Valeur de d   : %lx\n", (const void *)pd, (unsigned long)cd.u);
  printf("Adresse de ld  : %p, Valeur de ld  : ", (const void *)pld);
  affiche_long_double_hex(pld);
  printf("\n\n");
}

int main(void)
{
  /* les variables de types de base (comme dans variables.c) */
  char c = 'A';
  unsigned char uc = 255;
  short s = -1234;
  int i = -42;
  unsigned int ui = 4294967295U;
  long int li = 1234567890L;
  long long int lli = 123456789012345LL;
  float f = 2.0f;
  double d = 1.0;
  long double ld = 1.0L;

  /* un pointeur sur chaque variable */
  char *pc = &c;
  unsigned char *puc = &uc;
  short *ps = &s;
  int *pi = &i;
  unsigned int *pui = &ui;
  long int *pli = &li;
  long long int *plli = &lli;
  float *pf = &f;
  double *pd = &d;
  long double *pld = &ld;

  affiche("Avant la manipulation :", pc, ps, pi, pli, plli, pf, pd, pld, puc, pui);

  /* manipulation des variables *uniquement* par leurs pointeurs */
  *pc = 'Z';
  *puc = *puc - 1;
  *ps = *ps + 1000;
  *pi = *pi - 1;
  *pui = *pui / 2;
  *pli = *pli * 2;
  *plli = *plli + 1;
  *pf = 1.0f;
  *pd = *pd + 0.5;
  *pld = *pld * 2.0L;

  affiche("Apres la manipulation :", pc, ps, pi, pli, plli, pf, pd, pld, puc, pui);

  return 0;
}
