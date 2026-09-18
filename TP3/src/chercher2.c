/*
 * Exercice 3.8 - Rechercher une phrase dans un tableau de phrases
 *
 * Le tableau contient 10 phrases (un tableau de pointeurs de
 * caracteres). La recherche est faite *sans* fonction de bibliotheque
 * (pas de strcmp ni de strlen) : les phrases sont comparees caractere
 * par caractere.
 *
 * Compilation : gcc -Wall -Wextra -o chercher2 chercher2.c
 */

#include <stdio.h>

#define NB_PHRASES 10
#define TAILLE_SAISIE 256

/* Compare deux chaines caractere par caractere.
 * Renvoie 1 si elles sont identiques, 0 sinon. */
static int chaines_identiques(const char *chaine1, const char *chaine2)
{
  int i = 0;

  /* on avance tant que les deux caracteres sont egaux */
  while (chaine1[i] != '\0' && chaine2[i] != '\0')
  {
    if (chaine1[i] != chaine2[i])
    {
      return 0; /* difference trouvee */
    }
    i++;
  }

  /* les deux chaines doivent se terminer au meme endroit */
  return (chaine1[i] == '\0' && chaine2[i] == '\0');
}

/* Cherche `phrase` dans le tableau. Renvoie l'indice trouve, ou -1. */
static int cherche_phrase(const char *tableau[], int taille, const char *phrase)
{
  int i;

  for (i = 0; i < taille; i++)
  {
    if (chaines_identiques(tableau[i], phrase))
    {
      return i;
    }
  }

  return -1;
}

/* Retire le caractere de fin de ligne laisse par fgets. */
static void enleve_retour_ligne(char *chaine)
{
  int i = 0;

  while (chaine[i] != '\0')
  {
    if (chaine[i] == '\n')
    {
      chaine[i] = '\0';
      return;
    }
    i++;
  }
}

int main(void)
{
  const char *phrases[NB_PHRASES] = {
      "Bonjour, comment ca va ?",
      "Le temps est magnifique aujourd'hui.",
      "C'est une belle journee.",
      "La programmation en C est amusante.",
      "Les tableaux en C sont puissants.",
      "Les pointeurs en C peuvent etre deroutants.",
      "Il fait beau dehors.",
      "La recherche dans un tableau est interessante.",
      "Les structures de donnees sont importantes.",
      "Programmer en C, c'est genial."};

  char saisie[TAILLE_SAISIE];
  int position;
  int i;

  printf("Phrases disponibles :\n");
  for (i = 0; i < NB_PHRASES; i++)
  {
    printf("  %2d. %s\n", i + 1, phrases[i]);
  }

  printf("\nEntrez la phrase a rechercher : ");
  if (fgets(saisie, sizeof(saisie), stdin) == NULL)
  {
    printf("\nEntree invalide.\n");
    return 1;
  }
  enleve_retour_ligne(saisie);

  position = cherche_phrase(phrases, NB_PHRASES, saisie);

  if (position >= 0)
  {
    printf("Phrase trouvee (phrase numero %d)\n", position + 1);
  }
  else
  {
    printf("Phrase non trouvee\n");
  }

  return 0;
}
