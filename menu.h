#ifndef MENU
#define MENU

/** PROTOTYPES DE FONCTIONS **/

//fonction affichant une question ouverte et retournant la réponse
char* question_ouverte(char question[200],char* reponse);
//fonction affichant une question fermée et retournant la réponse
char question_ferme(char question[200],char intitule[500]);
//procédure affichant le volet du menu
void afficher_volet(BITMAP* buffer,char ch);
//procédure affichant le but du jeu
void afficher_butdujeu(int lig,int col);
//procédure affichant les commandes du jeu
void afficher_commandes(int lig,int col);
//procédure affichant une animation
void animation_bombe(int lig,int col);
//procédure affichant le menu du jeu
void menu(int* l,int* c,int* m,char* key);
//proédure affichant les instructions
void instruction();
//procédure permettant de choisir le niveau de difficulté
void difficulte(int* l,int* c,int* m);
//procédure affichant le "menu" de fin de jeu
void fin();

#endif // menu
