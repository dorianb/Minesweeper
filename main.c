//bibliothèque perso
#include "main.h"

//programme principal
int main()
{
    //déclaration d'un pointeur sur tableau de structure
    t_case** T;
    //déclaration des ressources
    int m,D,l,c,g,k,x,y;
    char touche;
    char ch=0xFF;
    char* nomfichier;
    m=0;
    D=0;
    l=0;
    c=0;
    touche='0';
    BITMAP* img;
    BITMAP* img1;
    BITMAP* img2;
    //initialisation des variables
    nomfichier="%%%%";
    //initialisation d'allegro
    initAllegro();
    //création de BITMAP
    img2=create_bitmap(SCREEN_W,SCREEN_H);
    img2=load_bitmap("image/win1.bmp",NULL);
    img1=create_bitmap(SCREEN_W,SCREEN_H);
    img1=load_bitmap("image/gameover1.bmp",NULL);
    img=create_bitmap(SCREEN_W,SCREEN_H);
    img=load_bitmap("image/démineur9.bmp",NULL);
    //initialisation du générateur aléatoire
    srand(time(NULL));
    //affichage du menu du jeu
    menu(&l,&c,&m,&touche);
    //boucle permettant de faire plusieurs cycles de jeux
    while(touche!='Q')
    {
        x=0;
        y=0;
        if(touche=='C')
        {
            T=charge(T,&l,&c,&m,&D,&nomfichier);
        }
        else
        {
            D=m;
            //allocation dynamique du tableau de jeu
            T=allocationTab(T,l,c);
            //initialisation du tableau: placement des mines
            init(T,m,l,c);
            //initialisation du tableau: placement des chiffres
            for(g=0; g<l; g++)
            {
                for(k=0; k<c; k++)
                {
                    if(T[g][k].mine!='M')
                    {
                        T[g][k].nombre=nb_mines(T,g,k,l,c);
                    }
                }
            }
            //positionnement du curseur sur une case vide
            start_cursor(T,l,c);
        }
        if((strcmp(nomfichier,"%%%%")!=0)||(touche!='C'))
        {
            //boucle permettant d'obtenir les actions de l'utilisateur indéfiniment
            while(touche!='M')
            {
                //affichage du tableau
                affiche_tableau(T,D,l,c,ch,img);
                nomfichier=event(T,&D,&touche,l,c,m,&x,&y,&ch,img,img1,img2,nomfichier);
            }
            clear_bitmap(screen);
            rectfill(screen,0,0,SCREEN_W,SCREEN_H,makecol(102,0,0));
            animation_bombe(100,100);
            clear_bitmap(screen);
            //libération de la mémoire
            free(T);
            T=NULL;
        }
        //affichage du menu
        touche='0';
        nomfichier="%%%%";
        menu(&l,&c,&m,&touche);
    }
    //fin du jeu
    destroy_bitmap(img);
    destroy_bitmap(img1);
    destroy_bitmap(img2);
    fin();
    return 0;
}
END_OF_MAIN();
