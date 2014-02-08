//bibliothèque
#include "main.h"

//lire un caractère ou une chaine de caractère
char* lireChaine(char* nomfichier,int lig,int col,int R,int V,int B)
{
    //ressources
    int touche=0;
    int i=0;
    char C[500];
    //lire les caractères saisis
    while((i<499)&&(touche!=KEY_ENTER)&&(touche!=KEY_ENTER_PAD))
    {
        touche=readkey()>>8;
        switch(touche)
        {
            case KEY_BACKSPACE:
            if(i>0)
            {
                i--;
                textprintf_ex(screen,font,col+10*i,lig,getpixel(screen,col+10*i,lig+8),-1,"%c",C[i]);
            }
            break;
            case KEY_SPACE:
            C[i]=touche-43;
            textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
            i++;
            break;
            case KEY_A:
            C[i]='q';
            textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
            i++;
            break;
            case KEY_Q:
            C[i]='a';
            textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
            i++;
            break;
            case KEY_Z:
            C[i]='w';
            textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
            i++;
            break;
            case KEY_W:
            C[i]='z';
            textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
            i++;
            break;
            case KEY_M:
            C[i]='m';
            textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
            i++;
            break;
            default:
            if((touche>=1)&&(touche<=26))
            {
                C[i]=touche+96;
                textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
                i++;
            }
            if((touche>=27)&&(touche<=36))
            {
                C[i]=touche+21;
                textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
                i++;
            }
            if((touche>=37)&&(touche<=46))
            {
                C[i]=touche+11;
                textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%c",C[i]);
                i++;
            }
            break;
        }
    }
    C[i]='\0';
    //allocation dynamique
    nomfichier=(char*)malloc((i+2)*sizeof(char));
    //copier la chaine c dans nomfichier
    nomfichier=strcpy(nomfichier,C);
    //retour de nomfichier
    return nomfichier;
}
//lire un entier entre 0 et 9999
int lireEntier(int lig,int col,int R,int V,int B)
{
    //ressources
    int a=0;
    int i;
    int j=1;
    int touche=0;
    int tab[4];
    //lire les valeurs saisies
    i=0;
    while((i<4)&&(touche!=KEY_ENTER)&&(touche!=KEY_ENTER_PAD))
    {
        touche=readkey()>>8;
        switch(touche)
        {
        case KEY_BACKSPACE:
            if(i>0)
            {
                i--;
                textprintf_ex(screen,font,col+10*i,lig,getpixel(screen,col+10*i,lig+8),-1,"%d",tab[i]);
                j=j/10;
            }
            break;
        default:
            if((touche>=27)&&(touche<=36))
            {
                tab[i]=touche-27;
                textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%d",tab[i]);
                i++;
                j=j*10;
            }
            if((touche>=37)&&(touche<=46))
            {
                tab[i]=touche-37;
                textprintf_ex(screen,font,col+10*i,lig,makecol(R,V,B),-1,"%d",tab[i]);
                i++;
                j=j*10;
            }
            break;
        }
    }
    //affectation de a
    touche=i;
    for(i=0; i<touche; i++)
    {
        j=j/10;
        a=(tab[i]*j)+a;
    }
    return a;
}
// Procédure d'ouverture du mode graphique Allegro
void initAllegro()
{
    set_uformat(U_ASCII);
    allegro_init();
    // Souris allegro
    install_mouse();
    install_keyboard();
    install_timer();
    set_color_depth(32);
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,550,0,0)!=0)
    {
        set_color_depth(24);
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,550,0,0)!=0)
        {
            allegro_message("probleme ouverture mode graphique");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    // Souris allegro
    show_mouse(screen);
    //initialisation du temps de prise de saisie
    set_keyboard_rate(300,100);
}
