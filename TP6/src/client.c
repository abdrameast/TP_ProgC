/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * TP6 - Exercices 6.1, 6.2 et 6.3 : client
 *
 * Le client :
 *   - analyse une image BMP (bmp.c) et compte ses couleurs (couleur.c) ;
 *   - demande a l'utilisateur combien de couleurs traiter (<= 30) ;
 *   - envoie ces couleurs au serveur au format JSON ;
 *   - affiche la reponse du serveur.
 *
 * Compilation : make
 * Utilisation :
 *   ./client ../images/drapeau24.bmp        -> le nombre de couleurs est demande
 *   ./client ../images/drapeau24.bmp 15     -> 15 couleurs, sans saisie
 *   ./client                                -> envoi d'un simple message
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#include "cJSON.h"
#include "client.h"
#include "bmp.h"

/* Retire le retour a la ligne laisse par fgets. */
static void enleve_retour_ligne(char *chaine)
{
  size_t longueur = strlen(chaine);

  while (longueur > 0 && (chaine[longueur - 1] == '\n' || chaine[longueur - 1] == '\r'))
  {
    chaine[longueur - 1] = '\0';
    longueur--;
  }
}

/*
 * Envoie `data` au serveur puis lit et affiche sa reponse.
 * Renvoie 0 en cas de succes, -1 en cas d'erreur.
 */
static int envoie_et_recois(int socketfd, const char *data)
{
  char reponse[TAILLE_MESSAGE];
  cJSON *json;
  int write_status;
  int read_status;

  printf("Envoi au serveur : %s\n", data);

  write_status = (int)write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    return -1;
  }

  memset(reponse, 0, sizeof(reponse));
  read_status = (int)read(socketfd, reponse, sizeof(reponse) - 1);
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }
  if (read_status == 0)
  {
    fprintf(stderr, "Le serveur a ferme la connexion.\n");
    return -1;
  }

  printf("Message recu: %s\n", reponse);

  /* la reponse est elle aussi au format JSON : on l'analyse pour
   * afficher proprement les valeurs renvoyees */
  json = cJSON_Parse(reponse);
  if (json != NULL)
  {
    const cJSON *code = cJSON_GetObjectItemCaseSensitive(json, "code");
    const cJSON *valeurs = cJSON_GetObjectItemCaseSensitive(json, "valeurs");
    const cJSON *valeur = NULL;

    if (cJSON_IsString(code))
    {
      printf("  code    : %s\n", code->valuestring);
    }

    cJSON_ArrayForEach(valeur, valeurs)
    {
      if (cJSON_IsString(valeur))
      {
        printf("  valeur  : %s\n", valeur->valuestring);
      }
    }

    cJSON_Delete(json);
  }

  return 0;
}

/*
 * Exercice 6.3 - Envoi d'un simple message au format JSON :
 *   { "code" : "message", "valeurs" : [ "bonjour" ] }
 */
int envoie_recois_message(int socketfd)
{
  char message[TAILLE_MESSAGE / 2];
  char *data;
  cJSON *json;
  cJSON *valeurs;
  int resultat;

  printf("Votre message (max 1000 caracteres): ");
  fflush(stdout);

  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    return -1;
  }
  enleve_retour_ligne(message);

  if (message[0] == '\0')
  {
    return 0;
  }

  /* construction du message JSON */
  json = cJSON_CreateObject();
  if (json == NULL)
  {
    fprintf(stderr, "Erreur : creation du message JSON impossible.\n");
    return -1;
  }

  if (cJSON_AddStringToObject(json, "code", "message") == NULL)
  {
    cJSON_Delete(json);
    return -1;
  }

  valeurs = cJSON_AddArrayToObject(json, "valeurs");
  if (valeurs == NULL)
  {
    cJSON_Delete(json);
    return -1;
  }
  cJSON_AddItemToArray(valeurs, cJSON_CreateString(message));

  /* cJSON_PrintUnformatted alloue la chaine : il faut la liberer */
  data = cJSON_PrintUnformatted(json);
  cJSON_Delete(json);

  if (data == NULL)
  {
    fprintf(stderr, "Erreur : serialisation JSON impossible.\n");
    return -1;
  }

  resultat = envoie_et_recois(socketfd, data);

  free(data);

  return resultat;
}

/*
 * Exercices 6.1, 6.2 et 6.3 - Analyse d'une image BMP et envoi des
 * couleurs les plus frequentes au serveur, au format JSON.
 *
 * Les couleurs sont triees par ordre croissant d'occurrences par
 * trier_couleur_compteur() : les plus frequentes se trouvent donc a la
 * fin du tableau, que l'on parcourt a l'envers.
 */
int envoie_couleurs(int socketfd, char *pathname, int nb_couleurs)
{
  couleur_compteur *cc;
  cJSON *json;
  cJSON *valeurs;
  char *data;
  int compte;
  int resultat;

  /* verification du nombre de couleurs demande (exercice 6.2) */
  if (nb_couleurs < 1 || nb_couleurs > MAX_COULEURS)
  {
    fprintf(stderr, "Erreur : le nombre de couleurs doit etre compris entre 1 et %d.\n",
            MAX_COULEURS);
    return -1;
  }

  /* analyse de l'image : comptage et tri des couleurs */
  cc = analyse_bmp_image(pathname);
  if (cc == NULL)
  {
    fprintf(stderr, "Erreur : impossible d'analyser l'image %s.\n", pathname);
    return -1;
  }

  printf("Image %s : %d couleurs distinctes.\n", pathname, cc->size);

  /* on ne peut pas envoyer plus de couleurs que l'image n'en contient */
  if (nb_couleurs > cc->size)
  {
    printf("L'image ne contient que %d couleurs : le nombre demande est ajuste.\n",
           cc->size);
    nb_couleurs = cc->size;
  }

  json = cJSON_CreateObject();
  if (json == NULL)
  {
    fprintf(stderr, "Erreur : creation du message JSON impossible.\n");
    return -1;
  }

  if (cJSON_AddStringToObject(json, "code", "couleurs") == NULL ||
      cJSON_AddNumberToObject(json, "nombre", nb_couleurs) == NULL)
  {
    cJSON_Delete(json);
    return -1;
  }

  valeurs = cJSON_AddArrayToObject(json, "valeurs");
  if (valeurs == NULL)
  {
    cJSON_Delete(json);
    return -1;
  }

  /* les `nb_couleurs` couleurs les plus frequentes */
  for (compte = 1; compte <= nb_couleurs; compte++)
  {
    char couleur_hex[16];
    int indice = cc->size - compte;

    if (indice < 0)
    {
      break;
    }

    if (cc->compte_bit == BITS32)
    {
      snprintf(couleur_hex, sizeof(couleur_hex), "#%02x%02x%02x",
               cc->cc.cc32[indice].c.rouge,
               cc->cc.cc32[indice].c.vert,
               cc->cc.cc32[indice].c.bleu);
      printf("  %2d. %s (%d pixels)\n", compte, couleur_hex,
             cc->cc.cc32[indice].compte);
    }
    else
    {
      snprintf(couleur_hex, sizeof(couleur_hex), "#%02x%02x%02x",
               cc->cc.cc24[indice].c.rouge,
               cc->cc.cc24[indice].c.vert,
               cc->cc.cc24[indice].c.bleu);
      printf("  %2d. %s (%d pixels)\n", compte, couleur_hex,
             cc->cc.cc24[indice].compte);
    }

    cJSON_AddItemToArray(valeurs, cJSON_CreateString(couleur_hex));
  }

  data = cJSON_PrintUnformatted(json);
  cJSON_Delete(json);

  if (data == NULL)
  {
    fprintf(stderr, "Erreur : serialisation JSON impossible.\n");
    return -1;
  }

  resultat = envoie_et_recois(socketfd, data);

  free(data);

  return resultat;
}

/*
 * Exercice 6.2 - Demande a l'utilisateur le nombre de couleurs a
 * traiter (toujours inferieur ou egal a MAX_COULEURS).
 */
static int demande_nombre_couleurs(void)
{
  char ligne[64];
  int nombre = 0;

  while (1)
  {
    printf("Combien de couleurs voulez-vous traiter (1 a %d) ? ", MAX_COULEURS);
    fflush(stdout);

    if (fgets(ligne, sizeof(ligne), stdin) == NULL)
    {
      /* pas de saisie possible : on prend la valeur par defaut */
      printf("\nValeur par defaut : 10\n");
      return 10;
    }

    if (sscanf(ligne, "%d", &nombre) == 1 &&
        nombre >= 1 && nombre <= MAX_COULEURS)
    {
      return nombre;
    }

    printf("Valeur invalide : entrez un nombre entre 1 et %d.\n", MAX_COULEURS);
  }
}

int main(int argc, char **argv)
{
  int socketfd;
  struct sockaddr_in server_addr;
  int connect_status;

  /* affichage ligne par ligne, y compris lorsque la sortie est
   * redirigee vers un fichier */
  setvbuf(stdout, NULL, _IOLBF, 0);

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // demande de connection au serveur
  connect_status = connect(socketfd, (struct sockaddr *)&server_addr,
                           sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  if (argc < 2)
  {
    /* aucune image : on envoie un simple message */
    printf("usage: ./client chemin_bmp_image [nombre_de_couleurs]\n");
    printf("Aucune image indiquee : envoi d'un simple message.\n\n");
    envoie_recois_message(socketfd);
  }
  else
  {
    /* exercice 6.2 : le nombre de couleurs peut etre donne en argument
     * ou saisi par l'utilisateur */
    int nb_couleurs;

    if (argc >= 3)
    {
      nb_couleurs = atoi(argv[2]);
      if (nb_couleurs < 1 || nb_couleurs > MAX_COULEURS)
      {
        fprintf(stderr, "Nombre de couleurs invalide : %s\n", argv[2]);
        close(socketfd);
        return EXIT_FAILURE;
      }
    }
    else
    {
      nb_couleurs = demande_nombre_couleurs();
    }

    // envoyer les couleurs predominantes d'une image au format BMP
    envoie_couleurs(socketfd, argv[1], nb_couleurs);
  }

  close(socketfd);

  return EXIT_SUCCESS;
}
