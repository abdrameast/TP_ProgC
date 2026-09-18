/*
 * Exercice 4.1 - Calcul avec operateurs (declarations)
 *
 * Les prototypes des fonctions de calcul. Chaque fonction prend deux
 * entiers (num1 et num2) et renvoie un entier.
 */

#ifndef __OPERATOR_H__
#define __OPERATOR_H__

/* somme       : num1 + num2 */
int somme(int num1, int num2);

/* difference  : num1 - num2 */
int difference(int num1, int num2);

/* produit     : num1 * num2 */
int produit(int num1, int num2);

/* quotient    : num1 / num2 (division entiere) */
int quotient(int num1, int num2);

/* modulo      : num1 % num2 (reste de la division entiere) */
int modulo(int num1, int num2);

/* et          : num1 & num2 (ET bit a bit) */
int et(int num1, int num2);

/* ou          : num1 | num2 (OU bit a bit) */
int ou(int num1, int num2);

/* negation    : ~num1 (NON bit a bit, operateur unaire :
 *               num2 est ignore) */
int negation(int num1, int num2);

/* Selectionne et appelle la bonne fonction en fonction de `op`
 * (+, -, *, /, %, &, |, ~) a l'aide d'une structure switch.
 * `resultat` recoit le resultat du calcul.
 * Renvoie 0 en cas de succes, -1 si l'operateur est inconnu ou si
 * l'operation est impossible (division ou modulo par zero). */
int calcule(int num1, int num2, char op, int *resultat);

/* Fonction d'entree de l'exercice 4.1, appelee depuis main.c. */
int exercice_operateur(void);

#endif
