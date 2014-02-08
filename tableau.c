//bibliothèque
#include "main.h"

//fonction allouant un tableau dynamiquement
t_case** allocationTab(t_case** T,int l,int c)
{
    int i;
    T=(t_case**)malloc(l*sizeof(t_case*));
    if(T==0)
    {
        allegro_message("pas assez de mémoire !");
        exit(1);
    }
    else
    {
        for(i=0; i<c; i++)
        {
            T[i]=(t_case*)malloc(c*sizeof(t_case));
            if(T[i]==0)
            {
                allegro_message("\npas assez de mémoire i=%d!\n",i);
                exit(1);
            }
        }
    }
    return T;
}
//fonction vérifiant la validité des coordonnées des cases à proximité de la case
int check(int lig,int col,int l,int c)
{
    if((lig>=0)&&(lig<l)&&(col>=0)&&(col<c))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//procédure affichant une case du tableau
void affiche_case(t_case** T,int i,int j,int l,int D,BITMAP* buffer)
{
    //ressources
    char C1;
    C1=33;
    //dessin du drapeau
    if(T[i][j].drapeau==1)
    {
        rectfill(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(255,255,255));
        rect(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(251,242,183));
        triangle(buffer,20*j+42,20*i+58,20*j+58,20*i+58,20*j+50,20*i+42,makecol(255,0,0));
        textprintf_centre_ex(buffer,font,10*(2*j+1)+40,10*(2*i+1)+40,makecol(255,255,255),-1,"%c",C1);
    }
    else
    {
        if(T[i][j].cache==1)
        {
            //dessin de la case cahée
            rectfill(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(208,192,122));
            rect(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(251,242,183));
        }
        else
        {
            if(T[i][j].mine!='M')
            {
                if(T[i][j].nombre==0)
                {
                    rectfill(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(255,255,255));
                    rect(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(251,242,183));
                }
                else
                {
                    rectfill(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(255,255,255));
                    rect(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(251,242,183));
                    textprintf_centre_ex(buffer,font,10*(2*j+1)+40,10*(2*i+1)+40,makecol(0,255,0),-1,"%d",T[i][j].nombre);
                }
            }
            else
            {
                rectfill(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(255,0,0));
                rect(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(251,242,183));
            }
        }
    }
    textprintf_ex(buffer,font,40,20*l+60,makecol(255,255,255),-1,"nombre de mines restantes : %d ",D);
}
//procédure affichant le tableau
void affiche_tableau(t_case** T,int D,int l,int c,char ch,BITMAP* img)
{
    //ressources
    int i,j;
    BITMAP* buffer;
    //création d'une BITMAP
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);
    //fond d'écran
//    draw_sprite(buffer,img,0,0);
    //afficher le volet du menu
    afficher_volet(buffer,ch);
    //parcourir les cases du tableau
    for(i=0; i<l; i++)
    {
        for(j=0; j<c; j++)
        {
            affiche_case(T,i,j,l,D,buffer);
        }
    }
    //dessin du curseur
    curseur(T,&i,&j,l,c);
    rect(buffer,20*j+40,20*i+40,20*(j+1)+40,20*(i+1)+40,makecol(0,0,0));
    //copie buffer vers écran
    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    //libérer la mémoire
    destroy_bitmap(buffer);
}
