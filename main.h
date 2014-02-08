#ifndef MAIN
#define MAIN

//bibliothèques
#include <allegro.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//bibliothèques modulaires
#include "menu.h"

//structure de donnée stockant les informations de chaque case
typedef struct box
{
   //'M' si la case contient une mine, 'a' sinon
   char mine;
   //un chiffre entre 0 et 8 si la case ne contient pas de mines, le chiffre 9 sinon
   int nombre;
   //booléen 1 si la case est cachée, 0 si la case est révélée
   int cache;
   //booléen 1 si la case est marquée par un drapeau, 0 sinon
   int drapeau;
   //booléen: 1 si la case est marquée par le curseur, 0 sinon
   int curseur;
}t_case;

/** PROTOTYPES DE FONCTIONS DU MODULE TABLEAU **/

//fonction allouant un tableau dynamiquement
t_case** allocationTab(t_case** T,int l,int c);
//procédure affichant une case du tableau
void affiche_case(t_case** T,int i,int j,int l,int D,BITMAP* buffer);
//procédure affichant le tableau
void affiche_tableau(t_case** T,int D,int l,int c,char ch,BITMAP* img);
//fonction vérifiant la validité des coordonnées des cases à proximité de la case
int check(int lig,int col,int l,int c);

/** PROTOTYPES DE FONCTIONS DU MODULE DEMINEUR **/

//fonction comptant le nombre de mines autour d'une case
int nb_mines(t_case** T,int lig,int col,int l,int c);
//procédure initialisant l'affichage du tableau: placement des mines aléatoirement
//et initialisation des données de structure
void init(t_case** T,int m,int l,int c);
//procédure révélant les cases en cascade lorsqu'elles sont vides
void cascada(t_case** T,int a,int b,int l,int c,int D);
//procédure plaçant le curseur sur une case vide au départ du jeu
void start_cursor(t_case** T,int l,int c);
//procédure permettant de déplacer le curseur à l'écran, de placer un drapeau et de révéler une case
char* event(t_case** T,int* d,char* key,int l,int c,int m,int* x,int* y,char* ch,BITMAP* img,BITMAP* img1,BITMAP* img2,char* nomfichier);

/** PROTOTYPES DE FONCTIONS DU MODULE ALLEGRO **/

//lire un caractère ou une chaine de caractère
char* lireChaine(char* nomfichier,int lig,int col,int R,int V,int B);
//lire un entier entre 0 et 9999
int lireEntier(int lig,int col,int R,int V,int B);
// Procédure d'ouverture du mode graphique Allegro
void initAllegro();

/** PROTOTYPE DE LA FONCTION DU MODULE CURSEUR **/

void curseur(t_case** T,int* i,int* j,int l,int c);

/** PROTOTYPE DES SOUS-PROGRAMMES DU MODULE FICHIER **/

//fonction permettant de lire le nom du fichier saisi par l'utilisateur
char* lireNomFichier(char* nomfichier,char* format);
//fonction chargeant une partie
t_case** charge(t_case** T,int* l,int* c,int* m,int* D,char** nomfichier);
//procédure sauvegardant la partie
char* sauvegarde(t_case** T,int l,int c,int m,int D,char* nomfichier);


#endif
