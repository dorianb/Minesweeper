//bibliothèque
#include "main.h"

//fonction comptant le nombre de mines autour d'une case
int nb_mines(t_case** T,int lig,int col,int l,int c)
{
    int h,i,j;
    h=0;
    for(i=lig-1; i<=lig+1; i++)
    {
        for(j=col-1; j<=col+1; j++)
        {
            if((check(i,j,l,c))&&(T[i][j].mine=='M'))
            {
                h++;
            }
        }
    }
    return h;
}
//procédure initialisant l'affichage du tableau: placement des mines aléatoirement
//et initialisation des données de structure
void init(t_case** T,int m,int l,int c)
{
    int i,j,cpt;
    cpt=0;
    while(m>0)
    {
        i=0;
        j=0;
        for(i=0; i<l; i++)
        {
            for(j=0; j<c; j++)
            {
                if(cpt==0)
                {
                    T[i][j].mine='a';
                    T[i][j].cache=1;
                    T[i][j].drapeau=0;
                    T[i][j].nombre=9;
                    T[i][j].curseur=0;
                }
                if((rand()%(l*c/7)==0)&&(m>0)&&(T[i][j].mine!='M'))
                {
                    T[i][j].mine='M';
                    m=m-1;
                }
            }
        }
        cpt++;
    }
}
//procédure révélant les cases en cascade lorsqu'elles sont vides
void cascada(t_case** T,int a,int b,int l,int c,int D)
{
    if((a>0)&&(T[a-1][b].cache==1))
    {
        T[a-1][b].cache=0;
        if(T[a-1][b].nombre==0)
        {
            cascada(T,a-1,b,l,c,D);
        }
    }
    if((a<(l-1))&&(T[a+1][b].cache==1))
    {
        T[a+1][b].cache=0;
        if(T[a+1][b].nombre==0)
        {
            cascada(T,a+1,b,l,c,D);
        }
    }
    if((b>0)&&(T[a][b-1].cache==1))
    {
        T[a][b-1].cache=0;
        if(T[a][b-1].nombre==0)
        {
            cascada(T,a,b-1,l,c,D);
        }
    }
    if((b<(c-1))&&(T[a][b+1].cache==1))
    {
        T[a][b+1].cache=0;
        if(T[a][b+1].nombre==0)
        {
            cascada(T,a,b+1,l,c,D);
        }
    }
    if((a>0)&(b>0)&&(T[a-1][b-1].cache==1))
    {
        T[a-1][b-1].cache=0;
        if(T[a-1][b-1].nombre==0)
        {
            cascada(T,a-1,b-1,l,c,D);
        }
    }
    if((a<(l-1))&&(b<(c-1))&&(T[a+1][b+1].cache==1))
    {
        T[a+1][b+1].cache=0;
        if(T[a+1][b+1].nombre==0)
        {
            cascada(T,a+1,b+1,l,c,D);
        }
    }
    if((a>0)&&(b<(c-1))&&(T[a-1][b+1].cache==1))
    {
        T[a-1][b+1].cache=0;
        if(T[a-1][b+1].nombre==0)
        {
            cascada(T,a-1,b+1,l,c,D);
        }
    }
    if((a<(l-1))&&(b>0)&&(T[a+1][b-1].cache==1))
    {
        T[a+1][b-1].cache=0;
        if(T[a+1][b-1].nombre==0)
        {
            cascada(T,a+1,b-1,l,c,D);
        }
    }
}
//procédure plaçant le curseur sur une case vide au départ du jeu
void start_cursor(t_case** T,int l,int c)
{
    int g,h,cpt;
    int i=0,j=0;
    cpt=0;
    for(g=0; g<l; g++)
    {
        for(h=0; h<c; h++)
        {
            if((T[g][h].nombre==0)&&(cpt<c/2))
            {
                i=g;
                j=h;
                cpt++;
            }
        }
    }
    T[i][j].curseur=1;
}
//procédure permettant de déplacer le curseur à l'écran, de placer un drapeau et de révéler une case
char* event(t_case** T,int* d,char* key,int l,int c,int m,int* x,int* y,char* ch,BITMAP* img,BITMAP* img1,BITMAP* img2,char* nomfichier)
{
    //déclaration des ressources
    int g,k,S,i,j,H,W;
    int touche=0;
    int done=0;
    //initialisation du compteur
    S=(l*c)-m;
    while(!done)
    {
        //récupérer l'action de l'utilisateur
        if(keypressed())
        {
            touche=readkey()>>8;
            //traitement
            switch(touche)
            {
            case KEY_4:
            case KEY_4_PAD:
            case KEY_LEFT :
                curseur(T,&i,&j,l,c);
                T[i][j].curseur=0;
                if(j!=0)
                {
                    j=j-1;
                }
                else
                {
                    j=c-1;
                }
                T[i][j].curseur=1;
                break;
            case KEY_6:
            case KEY_6_PAD:
            case KEY_RIGHT :
                curseur(T,&i,&j,l,c);
                T[i][j].curseur=0;
                j=j+1;
                if(j>(c-1))
                {
                    j=0;
                }
                T[i][j].curseur=1;
                break;
            case KEY_2:
            case KEY_2_PAD:
            case KEY_DOWN :
                curseur(T,&i,&j,l,c);
                T[i][j].curseur=0;
                i=i+1;
                if(i>(l-1))
                {
                    i=0;
                }
                T[i][j].curseur=1;
                break;
            case KEY_8:
            case KEY_8_PAD:
            case KEY_UP :
                curseur(T,&i,&j,l,c);
                T[i][j].curseur=0;
                if(i!=0)
                {
                    i=i-1;
                }
                else
                {
                    i=l-1;
                }
                T[i][j].curseur=1;
                break;
            case KEY_ENTER_PAD:
            case KEY_ENTER :
                curseur(T,&i,&j,l,c);
                if(T[i][j].drapeau==0)
                {
                    T[i][j].cache=0;
                    if(T[i][j].nombre==0)
                    {
                        cascada(T,i,j,l,c,*d);
                    }
                    if(T[i][j].mine=='M')
                    {
                        //affichage de l'image
                        clear_bitmap(screen);
                        blit(img1,screen,0,0,SCREEN_W/4,SCREEN_H/4,SCREEN_W,SCREEN_H);
                        textprintf_ex(screen,font,20,SCREEN_H-20,makecol(255,255,255),-1,"APPUYEZ SUR ECHAP");
                        while(!done)
                        {
                            touche=readkey()>>8;
                            if(touche==KEY_ESC)
                            {
                                done=1;
                            }
                        }
                        done=0;
                        //affichage du tableau
                        affiche_tableau(T,*d,l,c,*ch,img);
                        textprintf_ex(screen,font,20,SCREEN_H-20,makecol(255,255,255),-1,"APPUYEZ SUR ECHAP POUR REVENIR AU MENU");
                        while(!done)
                        {
                            touche=readkey()>>8;
                            if(touche==KEY_ESC)
                            {
                                done=1;
                                *key='M';
                            }
                        }
                    }
                    for(g=0; g<l; g++)
                    {
                        for(k=0; k<c; k++)
                        {
                            if(T[g][k].cache==0)
                            {
                                S=S-1;
                            }
                        }
                    }
                    if((S==0)&&(*key!='M'))
                    {
                        //affichage de l'image
                        clear_bitmap(screen);
                        blit(img2,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                        textprintf_ex(screen,font,20,SCREEN_H-20,makecol(255,255,255),-1,"APPUYEZ SUR ECHAP");
                        while(!done)
                        {
                            touche=readkey()>>8;
                            if(touche==KEY_ESC)
                            {
                                done=1;
                            }
                        }
                        done=0;
                        //affichage du tableau
                        affiche_tableau(T,*d,l,c,*ch,img);
                        textprintf_ex(screen,font,20,SCREEN_H-20,makecol(255,255,255),-1,"APPUYEZ SUR ECHAP POUR REVENIR AU MENU");
                        while(!done)
                        {
                            touche=readkey()>>8;
                            if(touche==KEY_ESC)
                            {
                                done=1;
                                *key='M';
                            }
                        }
                    }
                }
                break;
            case KEY_SPACE :
                curseur(T,&i,&j,l,c);
                if(T[i][j].cache==1)
                {
                    if(T[i][j].drapeau==1)
                    {
                        T[i][j].drapeau=0;
                        *d=*d+1;
                    }
                    else
                    {
                        if(*d!=0)
                        {
                            T[i][j].drapeau=1;
                            *d=*d-1;
                        }
                    }
                }
                break;
            }
            done=1;
        }
        else
        {
            //si la souris est dans la matrice de jeu
            if((mouse_x<(c*20+40))&&(mouse_x>40)&&(mouse_y<(l*20+40))&&(mouse_y>40))
            {
                //si clique gauche
                if((mouse_b&1)==1)
                {
                    rest(200);
                    i=((mouse_y-40)/20);
                    j=((mouse_x-40)/20);
                    if(T[i][j].drapeau==0)
                    {
                        T[i][j].cache=0;
                        if(T[i][j].nombre==0)
                        {
                            cascada(T,i,j,l,c,*d);
                        }
                        if(T[i][j].mine=='M')
                        {
                            //affichage de l'image
                            clear_bitmap(screen);
                            blit(img1,screen,0,0,SCREEN_W/4,SCREEN_H/4,SCREEN_W,SCREEN_H);
                            textprintf_ex(screen,font,20,SCREEN_H-20,makecol(255,255,255),-1,"APPUYEZ SUR ECHAP");
                            while(!done)
                            {
                                touche=readkey()>>8;
                                if(touche==KEY_ESC)
                                {
                                    done=1;
                                }
                            }
                            done=0;
                            //affichage du tableau
                            affiche_tableau(T,*d,l,c,*ch,img);
                            textprintf_ex(screen,font,20,SCREEN_H-20,makecol(255,255,255),-1,"APPUYEZ SUR ECHAP POUR REVENIR AU MENU");
                            while(!done)
                            {
                                touche=readkey()>>8;
                                if(touche==KEY_ESC)
                                {
                                    done=1;
                                    *key='M';
                                }
                            }
                        }
                        for(g=0; g<l; g++)
                        {
                            for(k=0; k<c; k++)
                            {
                                if(T[g][k].cache==0)
                                {
                                    S=S-1;
                                }
                            }
                        }
                        if((S==0)&&(*key!='M'))
                        {
                            //affichage de l'image
                            clear_bitmap(screen);
                            blit(img2,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                            textprintf_ex(screen,font,20,SCREEN_H-20,makecol(255,255,255),-1,"APPUYEZ SUR ECHAP");
                            while(!done)
                            {
                                touche=readkey()>>8;
                                if(touche==KEY_ESC)
                                {
                                    done=1;
                                }
                            }
                            done=0;
                            //affichage du tableau
                            affiche_tableau(T,*d,l,c,*ch,img);
                            textprintf_ex(screen,font,20,SCREEN_H-20,makecol(255,255,255),-1,"APPUYEZ SUR ECHAP POUR REVENIR AU MENU");
                            while(!done)
                            {
                                touche=readkey()>>8;
                                if(touche==KEY_ESC)
                                {
                                    done=1;
                                    *key='M';
                                }
                            }
                        }
                    }
                    done=1;
                }
                //si clique droit
                if((mouse_b&2)==2)
                {
                    rest(200);
                    i=((mouse_y-40)/20);
                    j=((mouse_x-40)/20);
                    if(T[i][j].cache==1)
                    {
                        if(T[i][j].drapeau==1)
                        {
                            T[i][j].drapeau=0;
                            *d=*d+1;
                            done=1;
                        }
                        else
                        {
                            if(*d!=0)
                            {
                                T[i][j].drapeau=1;
                                *d=*d-1;
                                done=1;
                            }
                        }
                    }
                }
                //si la souris bouge, le curseur bouge
                if((mouse_x!=*x)||(mouse_y!=*y))
                {
                    curseur(T,&i,&j,l,c);
                    T[i][j].curseur=0;
                    i=((mouse_y-40)/20);
                    j=((mouse_x-40)/20);
                    T[i][j].curseur=1;
                    *x=mouse_x;
                    *y=mouse_y;
                    done=1;
                }
            }
            //si la souris est sur le menu
            H=text_height(font);
            W=text_length(font,"BUT DU JEU");
            if((mouse_x>=(SCREEN_W-W-40))&&(mouse_x<=(SCREEN_W-20))&&(mouse_y>=30)&&(mouse_y<=(30+3*H)))
            {
                if(*ch!=0xFE)
                {
                    *ch=0xFE;
                    done=1;
                }
                if(mouse_b&1)
                {
                    afficher_butdujeu(25,20);
                    done=1;
                }
            }
            else
            {
                W=text_length(font,"COMMANDES DU JEU");
                if((mouse_x>=(SCREEN_W-W-40))&&(mouse_x<=(SCREEN_W-20))&&(mouse_y>=70)&&(mouse_y<=(70+3*H)))
                {
                    if(*ch!=0xFD)
                    {
                        *ch=0xFD;
                        done=1;
                    }
                    if(mouse_b&1)
                    {
                        afficher_commandes(20,SCREEN_W-20);
                        done=1;
                    }
                }
                else
                {
                    W=text_length(font,"SAUVEGARDER LA PARTIE");
                    if((mouse_x>=(SCREEN_W-W-40))&&(mouse_x<=(SCREEN_W-20))&&(mouse_y>=110)&&(mouse_y<=(110+3*H)))
                    {
                        if(*ch!=0xFB)
                        {
                            *ch=0xFB;
                            done=1;
                        }
                        if(mouse_b&1)
                        {
                            nomfichier=sauvegarde(T,l,c,m,*d,nomfichier);
                            textprintf_right_ex(screen,font,SCREEN_W-40,SCREEN_H-40,makecol(255,255,255),-1,"Sauvegarde en cours");
                            rest(2000);
                        }
                    }
                    else
                    {
                        W=text_length(font,"QUITTER");
                        if((mouse_x>=(SCREEN_W-W-40))&&(mouse_x<=(SCREEN_W-20))&&(mouse_y>=150)&&(mouse_y<=(150+3*H)))
                        {
                            if(mouse_b&1)
                            {
                                *key=question_ferme("SOUHAITEZ-VOUS VRAIMENT QUITTER LE JEU","\0");
                                if(*key=='O')
                                {
                                    *key='M';
                                    done=1;
                                }
                                if(*key=='N')
                                {
                                    done=1;
                                }
                            }
                            if(*ch!=0xF7)
                            {
                                *ch=0xF7;
                                done=1;
                            }
                        }
                        else
                        {
                            if(*ch!=0xFF)
                            {
                                done=1;
                                *ch=0xFF;
                            }
                        }
                    }
                }
            }
        }
    }
    return nomfichier;
}
