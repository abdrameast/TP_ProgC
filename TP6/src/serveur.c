/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * TP6 - Exercices 6.1, 6.2 et 6.3 : serveur
 *
 * Le serveur recoit du client des messages au format JSON :
 *
 *   { "code" : "message",  "valeurs" : [ "bonjour" ] }
 *   { "code" : "couleurs", "nombre" : 10,
 *     "valeurs" : [ "#ef7812", "#2cc864", ... ] }
 *
 * Pour un message "couleurs", il genere un diagramme circulaire au
 * format SVG (une part par couleur recue, exercice 6.2 : le nombre de
 * parts depend du nombre de couleurs envoyees) puis lance un navigateur
 * pour l'afficher (exercice 6.1).
 *
 * Compilation : make
 * Utilisation : ./serveur
 */

#include <math.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cJSON.h"
#include "serveur.h"

int socketfd;

/* Chemin du fichier SVG genere. */
const char *svg_file_path = "pie_chart.svg";

/*
 * Exercice 6.1 - Affichage du graphique en lancant une commande
 * existante sur la machine.
 *
 * On essaie firefox, puis xdg-open (le navigateur par defaut). Si aucun
 * des deux n'est installe (cas d'un Codespace sans interface
 * graphique), on se contente d'indiquer le chemin du fichier genere.
 */
int visualize_plot(void)
{
  /* les commandes essayees, dans l'ordre */
  const char *navigateurs[] = {"firefox", "xdg-open"};
  const int nb_navigateurs = (int)(sizeof(navigateurs) / sizeof(navigateurs[0]));
  char command[256];
  int i;

  for (i = 0; i < nb_navigateurs; i++)
  {
    /* "command -v" verifie que la commande existe sans l'executer */
    snprintf(command, sizeof(command), "command -v %s > /dev/null 2>&1",
             navigateurs[i]);

    if (system(command) == 0)
    {
      snprintf(command, sizeof(command), "%s %s", navigateurs[i], svg_file_path);

      if (system(command) == 0)
      {
        printf("SVG file opened in %s.\n", navigateurs[i]);
        return 0;
      }

      printf("Failed to open the SVG file with %s.\n", navigateurs[i]);
    }
  }

  printf("Aucun navigateur disponible sur cette machine.\n");
  printf("Le graphique a ete genere dans le fichier : %s\n", svg_file_path);

  return 0;
}

double degreesToRadians(double degrees)
{
  return degrees * M_PI / 180.0;
}

/*
 * Genere un diagramme circulaire au format SVG a partir des couleurs
 * recues. Chaque couleur occupe une part egale du disque : l'angle de
 * chaque part vaut 360 / nombre_de_couleurs (exercice 6.2).
 *
 * @param couleurs      le tableau des couleurs ("#rrggbb") ;
 * @param nb_couleurs   le nombre de couleurs.
 * @return 0 en cas de succes, 1 en cas d'erreur.
 */
int plot(char couleurs[MAX_COULEURS][16], int nb_couleurs)
{
  FILE *svg_file;
  const double center_x = 200.0;
  const double center_y = 200.0;
  const double radius = 150.0;
  double start_angle = -90.0;
  double angle_par_couleur;
  int i;

  if (nb_couleurs <= 0)
  {
    fprintf(stderr, "Aucune couleur a afficher.\n");
    return 1;
  }

  svg_file = fopen(svg_file_path, "w");
  if (svg_file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");

  /* l'angle depend du nombre de couleurs recues */
  angle_par_couleur = 360.0 / (double)nb_couleurs;

  /* cas particulier : une seule couleur occupe tout le disque. Un arc
   * de 360 degres a le meme point de depart et d'arrivee et ne serait
   * pas dessine : on trace donc un cercle complet. */
  if (nb_couleurs == 1)
  {
    fprintf(svg_file, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" fill=\"%s\" />\n",
            center_x, center_y, radius, couleurs[0]);
    fprintf(svg_file, "</svg>\n");
    fclose(svg_file);
    printf("Graphique genere avec 1 couleur dans %s\n", svg_file_path);
    visualize_plot();
    return 0;
  }

  for (i = 0; i < nb_couleurs; i++)
  {
    double end_angle = start_angle + angle_par_couleur;

    double start_angle_rad = degreesToRadians(start_angle);
    double end_angle_rad = degreesToRadians(end_angle);

    double x1 = center_x + radius * cos(start_angle_rad);
    double y1 = center_y + radius * sin(start_angle_rad);
    double x2 = center_x + radius * cos(end_angle_rad);
    double y2 = center_y + radius * sin(end_angle_rad);

    /* le drapeau "large-arc" vaut 1 si la part depasse un demi-cercle */
    int large_arc = (angle_par_couleur > 180.0) ? 1 : 0;

    fprintf(svg_file,
            "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 %d,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
            x1, y1, radius, radius, large_arc, x2, y2, center_x, center_y,
            couleurs[i]);

    start_angle = end_angle;
  }

  fprintf(svg_file, "</svg>\n");

  fclose(svg_file);

  printf("Graphique genere avec %d couleur(s) dans %s\n", nb_couleurs, svg_file_path);

  visualize_plot();

  return 0;
}

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = (int)write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("erreur ecriture");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

/*
 * Construit une reponse JSON { "code" : <code>, "valeurs" : [ <valeur> ] }
 * et l'envoie au client.
 */
static int renvoie_json(int client_socket_fd, const char *code, const char *valeur)
{
  cJSON *json = cJSON_CreateObject();
  cJSON *valeurs;
  char *texte;
  int resultat;

  if (json == NULL)
  {
    return EXIT_FAILURE;
  }

  if (cJSON_AddStringToObject(json, "code", code) == NULL)
  {
    cJSON_Delete(json);
    return EXIT_FAILURE;
  }

  valeurs = cJSON_AddArrayToObject(json, "valeurs");
  if (valeurs == NULL)
  {
    cJSON_Delete(json);
    return EXIT_FAILURE;
  }
  cJSON_AddItemToArray(valeurs, cJSON_CreateString(valeur));

  texte = cJSON_PrintUnformatted(json);
  cJSON_Delete(json);

  if (texte == NULL)
  {
    return EXIT_FAILURE;
  }

  resultat = renvoie_message(client_socket_fd, texte);

  free(texte);

  return resultat;
}

/*
 * Exercices 6.2 et 6.3 - Traitement d'un message "couleurs".
 *
 * Le serveur lit d'abord le nombre de couleurs annonce par le client
 * ("nombre"), puis les couleurs elles-memes ("valeurs"), et ne traite
 * que les `nombre` premieres.
 */
static int traite_couleurs(int client_socket_fd, const cJSON *json)
{
  char couleurs[MAX_COULEURS][16];
  const cJSON *nombre = cJSON_GetObjectItemCaseSensitive(json, "nombre");
  const cJSON *valeurs = cJSON_GetObjectItemCaseSensitive(json, "valeurs");
  const cJSON *valeur = NULL;
  int nb_annonce;
  int nb_recues = 0;
  char reponse[256];

  if (!cJSON_IsArray(valeurs))
  {
    return renvoie_json(client_socket_fd, "erreur", "liste de couleurs absente");
  }

  /* le nombre de couleurs saisi par l'utilisateur ; s'il est absent,
   * on prend la taille du tableau recu */
  if (cJSON_IsNumber(nombre))
  {
    nb_annonce = nombre->valueint;
  }
  else
  {
    nb_annonce = cJSON_GetArraySize(valeurs);
  }

  if (nb_annonce < 1)
  {
    return renvoie_json(client_socket_fd, "erreur", "nombre de couleurs invalide");
  }
  if (nb_annonce > MAX_COULEURS)
  {
    printf("Nombre de couleurs annonce (%d) superieur au maximum : limite a %d.\n",
           nb_annonce, MAX_COULEURS);
    nb_annonce = MAX_COULEURS;
  }

  printf("Nombre de couleurs annonce par le client : %d\n", nb_annonce);

  /* lecture des couleurs, dans la limite du nombre annonce */
  cJSON_ArrayForEach(valeur, valeurs)
  {
    if (nb_recues >= nb_annonce)
    {
      break;
    }

    if (cJSON_IsString(valeur) && valeur->valuestring != NULL)
    {
      snprintf(couleurs[nb_recues], sizeof(couleurs[nb_recues]), "%s",
               valeur->valuestring);
      printf("  couleur %2d : %s\n", nb_recues + 1, couleurs[nb_recues]);
      nb_recues++;
    }
  }

  if (nb_recues == 0)
  {
    return renvoie_json(client_socket_fd, "erreur", "aucune couleur exploitable");
  }

  /* generation du graphique */
  if (plot(couleurs, nb_recues) != 0)
  {
    return renvoie_json(client_socket_fd, "erreur", "generation du graphique impossible");
  }

  snprintf(reponse, sizeof(reponse), "%s (%d couleurs)", svg_file_path, nb_recues);

  return renvoie_json(client_socket_fd, "reponse", reponse);
}

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour.
 *
 * Exercice 6.3 : le message recu est analyse au format JSON. Le champ
 * "code" indique l'operation demandee ("message" ou "couleurs").
 */
int recois_envoie_message(int client_socket_fd, char data[TAILLE_MESSAGE])
{
  cJSON *json;
  const cJSON *code;
  int resultat;

  printf("Message recu: %s\n", data);

  json = cJSON_Parse(data);
  if (json == NULL)
  {
    const char *erreur = cJSON_GetErrorPtr();

    fprintf(stderr, "Erreur : message JSON invalide");
    if (erreur != NULL)
    {
      fprintf(stderr, " (avant : %s)", erreur);
    }
    fprintf(stderr, "\n");

    return renvoie_json(client_socket_fd, "erreur", "message JSON invalide");
  }

  code = cJSON_GetObjectItemCaseSensitive(json, "code");
  if (!cJSON_IsString(code) || code->valuestring == NULL)
  {
    cJSON_Delete(json);
    return renvoie_json(client_socket_fd, "erreur", "code absent");
  }

  if (strcmp(code->valuestring, "message") == 0)
  {
    /* un simple message : on renvoie la premiere valeur recue */
    const cJSON *valeurs = cJSON_GetObjectItemCaseSensitive(json, "valeurs");
    const cJSON *premiere = cJSON_GetArrayItem(valeurs, 0);

    if (cJSON_IsString(premiere) && premiere->valuestring != NULL)
    {
      resultat = renvoie_json(client_socket_fd, "message", premiere->valuestring);
    }
    else
    {
      resultat = renvoie_json(client_socket_fd, "erreur", "message vide");
    }
  }
  else if (strcmp(code->valuestring, "couleurs") == 0)
  {
    /* exercices 6.1 et 6.2 : generation du graphique */
    resultat = traite_couleurs(client_socket_fd, json);
  }
  else
  {
    printf("Code inconnu : %s\n", code->valuestring);
    resultat = renvoie_json(client_socket_fd, "erreur", "code inconnu");
  }

  cJSON_Delete(json);

  return resultat;
}

// Fonction de gestion du signal Ctrl+C
void gestionnaire_ctrl_c(int signal)
{
  (void)signal;

  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");
  // fermer le socket
  close(socketfd);
  exit(0); // Quitter proprement le programme.
}

int main(void)
{
  int bind_status;
  struct sockaddr_in server_addr;
  int option = 1;

  /* affichage ligne par ligne, y compris lorsque la sortie est
   * redirigee vers un fichier */
  setvbuf(stdout, NULL, _IOLBF, 0);

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("Unable to open a socket");
    return -1;
  }

  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Relier l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Enregistrez la fonction de gestion du signal Ctrl+C
  signal(SIGINT, gestionnaire_ctrl_c);

  // Écouter les messages envoyés par le client
  listen(socketfd, 10);

  printf("Serveur en attente de connexions...\n");

  // Écouter les messages envoyés par le client en boucle infinie
  while (1)
  {
    // Lire et répondre au client
    struct sockaddr_in client_addr;
    char data[TAILLE_MESSAGE];
    int data_size;
    int client_socket_fd;

    unsigned int client_addr_len = sizeof(client_addr);

    // nouvelle connection de client
    client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr,
                              &client_addr_len);
    if (client_socket_fd < 0)
    {
      perror("accept");
      continue;
    }

    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // lecture de données envoyées par un client
    data_size = (int)read(client_socket_fd, (void *)data, sizeof(data) - 1);

    if (data_size < 0)
    {
      perror("erreur lecture");
      close(client_socket_fd);
      continue;
    }

    if (data_size > 0)
    {
      recois_envoie_message(client_socket_fd, data);
    }

    close(client_socket_fd);
  }

  return 0;
}
