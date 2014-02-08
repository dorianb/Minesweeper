#ifndef MENU
#define MENU

/** PROTOTYPES DE FONCTIONS **/

//fonction affichant une question ouverte et retournant la r�ponse
char* question_ouverte(char question[200],char* reponse);
//fonction affichant une question ferm�e et retournant la r�ponse
char question_ferme(char question[200],char intitule[500]);
//proc�dure affichant le volet du menu
void afficher_volet(BITMAP* buffer,char ch);
//proc�dure affichant le but du jeu
void afficher_butdujeu(int lig,int col);
//proc�dure affichant les commandes du jeu
void afficher_commandes(int lig,int col);
//proc�dure affichant une animation
void animation_bombe(int lig,int col);
//proc�dure affichant le menu du jeu
void menu(int* l,int* c,int* m,char* key);
//pro�dure affichant les instructions
void instruction();
//proc�dure permettant de choisir le niveau de difficult�
void difficulte(int* l,int* c,int* m);
//proc�dure affichant le "menu" de fin de jeu
void fin();

#endif // menu
