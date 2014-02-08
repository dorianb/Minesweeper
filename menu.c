//bibliothèque
#include "main.h"

//fonction affichant une question ouverte et retournant la réponse
char* question_ouverte(char question[200],char* reponse)
{
    //ressources
    int L=150;
    int l=150;
    int H,W;
    //affichage
    H=text_height(font);
    rectfill(screen,L,l,SCREEN_W-L,SCREEN_H-l,makecol(102,129,162));
    rect(screen,L,l,SCREEN_W-L,SCREEN_H-l,makecol(54,64,75));
    //affichage de la question
    W=text_length(font,question);
    rectfill(screen,(SCREEN_W/2)-(W/2)-10,(SCREEN_H/2)-H,(SCREEN_W/2)+(W/2)+10,(SCREEN_H/2)+2*H,makecol(251,242,183));
    rect(screen,(SCREEN_W/2)-(W/2)-10,(SCREEN_H/2)-H,(SCREEN_W/2)+(W/2)+10,(SCREEN_H/2)+2*H,makecol(219,23,2));
    textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2, makecol(58,2,13), -1,"%s",question);
    //lecture et retour de la réponse
    return lireChaine(reponse,(SCREEN_W/2)-(W/2)-10,(SCREEN_H/2)-H+5*H,0,0,0);
}
//fonction affichant une question fermée et retournant la réponse
char question_ferme(char question[200],char intitule[500])
{
    //ressources
    int W,H;
    char touche='1';
    char ch=0xFF;
    BITMAP* buffer;
    //initialisation du buffer
    buffer=create_bitmap(SCREEN_W-160,SCREEN_H-160);
    //affichage
    while((touche!='O')&&(touche!='N'))
    {
        H=text_height(font);
        rectfill(buffer,0,0,SCREEN_W-300,SCREEN_H-300,makecol(102,129,162));
        rect(buffer,0,0,SCREEN_W-300,SCREEN_H-300,makecol(54,64,75));
        //affichage de la question
        W=text_length(font,question);
        W=W+2*(text_length(font,intitule))+40;
        rectfill(buffer,(SCREEN_W-300)/2-(W/2)-10,(SCREEN_H-300)/2-H,(SCREEN_W-300)/2+(W/2)+10,(SCREEN_H-300)/2+2*H,makecol(251,242,183));
        rect(buffer,(SCREEN_W-300)/2-(W/2)-10,(SCREEN_H-300)/2-H,(SCREEN_W-300)/2+(W/2)+10,(SCREEN_H-300)/2+2*H,makecol(219,23,2));
        textprintf_centre_ex(buffer,font,(SCREEN_W-300)/2,(SCREEN_H-300)/2, makecol(58,2,13), -1,"%s",question);
        W=text_length(font,question);
        textprintf_ex(buffer,font,(SCREEN_W-300)/2+W/2,(SCREEN_H-300)/2, makecol(58,2,13), -1," %s ?",intitule);
        //affichage de la réponse
        W=text_length(font,"OUI");
        if(ch&0x01)
        {
            rectfill(buffer,(SCREEN_W-300)/2-(W/2)-10-50,(SCREEN_H-300)/2-H+5*H,(SCREEN_W-300)/2+(W/2)+10-50,(SCREEN_H-300)/2+2*H+5*H,makecol(251,242,183));
        }
        else
        {
            rectfill(buffer,(SCREEN_W-300)/2-(W/2)-10-50,(SCREEN_H-300)/2-H+5*H,(SCREEN_W-300)/2+(W/2)+10-50,(SCREEN_H-300)/2+2*H+5*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W-300)/2-(W/2)-10-50,(SCREEN_H-300)/2-H+5*H,(SCREEN_W-300)/2+(W/2)+10-50,(SCREEN_H-300)/2+2*H+5*H,makecol(219,23,2));
        textprintf_centre_ex(buffer,font,(SCREEN_W-300)/2-50,(SCREEN_H-300)/2+5*H, makecol(58,2,13), -1,"OUI");
        W=text_length(font,"NON");
        if(ch&0x02)
        {
            rectfill(buffer,(SCREEN_W-300)/2-(W/2)-10+50,(SCREEN_H-300)/2-H+5*H,(SCREEN_W-300)/2+(W/2)+10+50,(SCREEN_H-300)/2+2*H+5*H,makecol(251,242,183));
        }
        else
        {
            rectfill(buffer,(SCREEN_W-300)/2-(W/2)-10+50,(SCREEN_H-300)/2-H+5*H,(SCREEN_W-300)/2+(W/2)+10+50,(SCREEN_H-300)/2+2*H+5*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W-300)/2-(W/2)-10+50,(SCREEN_H-300)/2-H+5*H,(SCREEN_W-300)/2+(W/2)+10+50,(SCREEN_H-300)/2+2*H+5*H,makecol(219,23,2));
        textprintf_centre_ex(buffer,font,(SCREEN_W-300)/2+50,(SCREEN_H-300)/2+5*H, makecol(58,2,13), -1,"NON");
        //affichage à l'écran
        blit(buffer,screen,0,0,150,150,SCREEN_W-300,SCREEN_H-300);
        //lecture
        W=text_length(font,"NON");
        if((mouse_x>=((SCREEN_W-300)/2-(W/2)-10+50+150))&&(mouse_x<=((SCREEN_W-300)/2+(W/2)+10+50+150))&&(mouse_y>=((SCREEN_H-300)/2-H+5*H+150))&&(mouse_y<=((SCREEN_H-300)/2+2*H+5*H+150)))
        {
            ch=0xFD;
            if(mouse_b&1)
            {
                rest(200);
                touche='N';
            }
        }
        else
        {
            W=text_length(font,"OUI");
            if((mouse_x>=((SCREEN_W-300)/2-(W/2)-10-50+150))&&(mouse_x<=((SCREEN_W-300)/2+(W/2)+10-50+150))&&(mouse_y>=((SCREEN_H-300)/2-H+5*H+150))&&(mouse_y<=((SCREEN_H-300)/2+2*H+5*H+150)))
            {
                ch=0xFE;
                if(mouse_b&1)
                {
                    rest(200);
                    touche='O';
                }
            }
            else
            {
                ch=0xFF;
            }
        }

    }
    destroy_bitmap(buffer);
    return touche;
}
//procédure affichant le volet du menu
void afficher_volet(BITMAP* buffer,char ch)
{
    //ressources
    int W,H;
    //affichage
    H=text_height(font);
    W=text_length(font,"BUT DU JEU");
    if(ch&0x01)
    {
        rectfill(buffer,SCREEN_W-W-40,30,SCREEN_W-20,30+3*H,makecol(208,192,122));
    }
    else
    {
        rectfill(buffer,SCREEN_W-W-40,30,SCREEN_W-20,30+3*H,makecol(255,255,255));
    }
    rect(buffer,SCREEN_W-W-40,30,SCREEN_W-20,30+3*H,makecol(150,0,24));
    textprintf_right_ex(buffer,font, SCREEN_W-30, 30+H, makecol(58,2,13),-1,"BUT DU JEU");
    W=text_length(font,"COMMANDES DU JEU");
    if(ch&0x02)
    {
        rectfill(buffer,SCREEN_W-W-40,30+40,SCREEN_W-20,30+40+3*H,makecol(208,192,122));
    }
    else
    {
        rectfill(buffer,SCREEN_W-W-40,30+40,SCREEN_W-20,30+40+3*H,makecol(255,255,255));
    }
    rect(buffer,SCREEN_W-W-40,30+40,SCREEN_W-20,30+40+3*H,makecol(150,0,24));
    textprintf_right_ex(buffer,font, SCREEN_W-30, 30+40+H, makecol(58,2,13),-1,"COMMANDES DU JEU");
    W=text_length(font,"SAUVEGARDER LA PARTIE");
    if(ch&0x04)
    {
        rectfill(buffer,SCREEN_W-W-40,70+40,SCREEN_W-20,70+40+3*H,makecol(208,192,122));
    }
    else
    {
        rectfill(buffer,SCREEN_W-W-40,70+40,SCREEN_W-20,70+40+3*H,makecol(255,255,255));
    }
    rect(buffer,SCREEN_W-W-40,70+40,SCREEN_W-20,70+40+3*H,makecol(150,0,24));
    textprintf_right_ex(buffer,font, SCREEN_W-30, 70+40+H, makecol(58,2,13),-1,"SAUVEGARDER LA PARTIE");
    W=text_length(font,"QUITTER");
    if(ch&0x08)
    {
        rectfill(buffer,SCREEN_W-W-40,110+40,SCREEN_W-20,110+40+3*H,makecol(208,192,122));
    }
    else
    {
        rectfill(buffer,SCREEN_W-W-40,110+40,SCREEN_W-20,110+40+3*H,makecol(255,255,255));
    }
    rect(buffer,SCREEN_W-W-40,110+40,SCREEN_W-20,110+40+3*H,makecol(150,0,24));
    textprintf_right_ex(buffer,font, SCREEN_W-30, 110+40+H, makecol(58,2,13),-1,"QUITTER");
}
//procédure affichant le but du jeu
void afficher_butdujeu(int lig,int col)
{
    //ressources
    int done=0;
    int touche;
    BITMAP* img;
    //chargement de l'image
    img=create_bitmap(SCREEN_W,SCREEN_H);
    img=load_bitmap("image/démineur5.bmp",NULL);
    //affichage
    clear_bitmap(screen);
    draw_sprite(screen,img,0,0);
    textprintf_ex(screen, font, col, lig, makecol(0,0,0),-1,"VOUS DISPOSEZ D'UNE GRILLE CONTENANT DES MINES CACHEES.");
    col=col-5;
    lig=lig+20;
    textprintf_ex(screen, font, col, lig, makecol(0,0,0),-1,"LORSQUE VOUS REVELEZ UNE CASE NE CONTENANT PAS DE MINES, VOUS CONNAISSEZ LE NOMBRE DE MINES QUI L'ENTOURE.");
    lig=lig+20;
    textprintf_ex(screen, font, col, lig, makecol(0,0,0),-1,"LE BUT DU JEU EST DE DETECTER TOUTES LES MINES SANS REVELER LES CASES QUI LES CONTIENNENT.");
    lig=lig+20;
    textprintf_ex(screen, font, col, lig, makecol(0,0,0),-1,"VOUS POUVEZ MARQUER UNE CASE PAR UN DRAPEAU SI VOUS SUPPOSEZ QU'UNE MINE POURRAIT Y ETRE CACHEE.");
    lig=lig+20;
    textprintf_ex(screen, font, col, lig, makecol(0,0,0),-1,"SACHEZ QUE VOUS POUVEZ EGALEMENT CHOISIR LE NOMBRE DE CASES DE LA GRILLE DE JEU");
    lig=lig+20;
    textprintf_ex(screen, font, col, lig, makecol(0,0,0),-1,"AINSI QUE LE NOMBRE DE MINES VIA LE NIVEAU DE DIFFICULTE PERSONNALISE.");
    textprintf_ex(screen, font, 20, SCREEN_H-20, makecol(255, 255, 255),-1,"APPUYEZ SUR ECHAP POUR REVENIR AU MENU PRECEDENT");
    while(!done)
    {
        touche=readkey()>>8;
        if(touche==KEY_ESC)
        {
            done=1;
        }
    }
    destroy_bitmap(img);
}
//procédure affichant les commandes du jeu
void afficher_commandes(int lig,int col)
{
    //ressources
    int done=0;
    int touche;
    BITMAP* img;
    //création et chargement du bitmap
    img=create_bitmap(SCREEN_W,SCREEN_H);
    img=load_bitmap("image/démineur4.bmp",NULL);
    if(!img)
    {
        allegro_message("Impossible d'ouvrir img");
    }
    //affichage
    clear_bitmap(screen);
    draw_sprite(screen,img,0,0);
    textprintf_right_ex(screen, font, col, lig, makecol(0,0,0), -1,"-TOUCHES DIRECTIONNELLES :");
    lig=lig+20;
    textprintf_right_ex(screen, font, col, lig, makecol(0,0,0), -1,"DEPLACEMENT D'UNE CASE VERS LA GAUCHE -> flèche de GAUCHE ou 4");
    lig=lig+20;
    textprintf_right_ex(screen, font, col, lig, makecol(0,0,0), -1,"DEPLACEMENT D'UNE CASE VERS LA DROITE -> flèche de DROITE ou 6");
    lig=lig+20;
    textprintf_right_ex(screen, font, col, lig, makecol(0,0,0), -1,"DEPLACEMENT D'UNE CASE VERS LE HAUT -> flèche du HAUT ou 8");
    lig=lig+20;
    textprintf_right_ex(screen, font, col, lig, makecol(0,0,0), -1,"DEPLACEMENT D'UNE CASE VERS LE BAS -> flèche du BAS ou 2");
    lig=lig+20;
    textprintf_right_ex(screen, font, col, lig, makecol(0,0,0), -1,"-POSER/ENLEVER UN DRAPEAU SUR UNE CASE CACHEE -> TOUCHE ESPACE ou clique droit");
    lig=lig+20;
    textprintf_right_ex(screen, font, col, lig, makecol(0,0,0), -1,"-REVELER UNE CASE -> TOUCHE ENTREE ou clique gauche");
    textprintf_ex(screen, font, 20, SCREEN_H-20, makecol(255, 255, 255), -1,"APPUYEZ SUR ECHAP POUR REVENIR AU MENU PRECEDENT");
    while(!done)
    {
        touche=readkey()>>8;
        if(touche==KEY_ESC)
        {
            done=1;
        }
    }
    destroy_bitmap(img);
}
//procédure affichant une animation
void animation_bombe(int lig,int col)
{
    //ressources
    BITMAP** img;
    char buff[50];
    int i;
    //allocation dynamique de pointeur sur BITMAP
    img=(BITMAP**)malloc(25*sizeof(BITMAP*));
    //création des pointeurs
    for(i=0; i<25; i++)
    {
        img[i]=create_bitmap(SCREEN_W,SCREEN_H);
        sprintf(buff,"image/bombe%d.bmp",i+2);
        img[i]=load_bitmap(buff,NULL);
        if(!img[i])
        {
            allegro_message("Erreur de chargement de l'image bombe%d.bmp",i+2);
        }
        masked_blit(img[i],screen,0,0,col,lig,SCREEN_W,SCREEN_H);
        rest(50);
    }
    //libérer les pointeurs
    for(i=0; i<25; i++)
    {
        destroy_bitmap(img[i]);
    }
    free(img);
}
//procédure affichant le "menu" de fin de jeu
void fin()
{
    clear_bitmap(screen);
    rectfill(screen,0,0,SCREEN_W,SCREEN_H,makecol(102,0,0));
    rectfill(screen,190,60,460,90,makecol(251,242,183));
    rect(screen,190,60,460,90,makecol(219,23,2));
    rect(screen,189,59,461,89,makecol(219,23,2));
    textprintf_centre_ex(screen,font, 325, 70, makecol(58,2,13), -1,"A BIENTOT");
    animation_bombe(100,100);
    allegro_exit();
}
//procédure permettant de choisir le niveau de difficulté
void difficulte(int* l,int* c,int* m)
{
    //ressources
    int W,H;
    int done=0;
    char ch=0xFF;
    BITMAP* buffer;
    BITMAP* img;
    //initialisation du buffer
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    img=create_bitmap(SCREEN_W,SCREEN_H);
    img=load_bitmap("image/démineur6.bmp",NULL);
    //boucle d'éxécution
    while(!done)
    {
        //initialisation de la souri
        mouse_b=0;
        clear_bitmap(buffer);
        //affichage
        draw_sprite(buffer,img,0,0);
        W=text_length(font,"FACILE");
        H=text_height(font);
        if(ch&0x01)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(208,192,122));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 60+100+H, makecol(58,2,13),-1,"FACILE");
        W=text_length(font,"NORMAL");
        if(ch&0x02)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(208,192,122));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 160+40+H, makecol(58,2,13),-1,"NORMAL");
        W=text_length(font,"DIFFICILE");
        if(ch&0x04)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(208,192,122));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 200+40+H, makecol(58,2,13),-1,"DIFFICILE");
        W=text_length(font,"PERSONNALISE");
        if(ch&0x08)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,240+40,(SCREEN_W/2)+(W/2)+10,240+40+3*H,makecol(208,192,122));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,240+40,(SCREEN_W/2)+(W/2)+10,240+40+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,240+40,(SCREEN_W/2)+(W/2)+10,240+40+3*H,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 240+40+H, makecol(58,2,13),-1,"PERSONNALISE");
        //affichage sur l'écran
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        //lecture
        W=text_length(font,"FACILE");
        if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=160)&&(mouse_y<=60+100+3*H))
        {
            ch=0xFE;
            if(mouse_b&1)
            {
                *l=8;
                *c=8;
                *m=10;
                done=1;
            }
        }
        else
        {
            W=text_length(font,"NORMAL");
            if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=200)&&(mouse_y<=200+3*H))
            {
                ch=0xFD;
                if(mouse_b&1)
                {
                    *l=15;
                    *c=15;
                    *m=45;
                    done=1;
                }
            }
            else
            {
                W=text_length(font,"DIFFICILE");
                if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=240)&&(mouse_y<=240+3*H))
                {
                    ch=0xFB;
                    if(mouse_b&1)
                    {
                        *l=20;
                        *c=20;
                        *m=80;
                        done=1;
                    }
                }
                else
                {
                    W=text_length(font,"PERSONNALISE");
                    if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=280)&&(mouse_y<=280+3*H))
                    {
                        ch=0xF7;
                        if(mouse_b&1)
                        {
                            clear_bitmap(screen);
                            draw_sprite(screen,img,0,0);
                            textprintf_ex(screen, font, 20, 20, makecol(0,0,0),-1,"VEUILLEZ ENTRER UN NOMBRE DE COLONNES:");
                            *c=lireEntier(20,400,0,0,0);
                            while((*c>37)||(*c<3))
                            {
                                clear_bitmap(screen);
                                draw_sprite(screen,img,0,0);
                                textprintf_ex(screen, font, 20, 20, makecol(0,0,0),-1,"VEUILLEZ ENTRER UN NOMBRE DE COLONNES COMPRIS ENTRE 3 ET 37:");
                                *c=lireEntier(20,600,0,0,0);
                            }
                            clear_bitmap(screen);
                            draw_sprite(screen,img,0,0);
                            textprintf_ex(screen, font, 20, 20, makecol(0,0,0),-1,"VEUILLEZ ENTRER UN NOMBRE DE LIGNES:");
                            *l=lireEntier(20,400,0,0,0);
                            while((*l>*c)||(*l<3)||(*l>20))
                            {
                                clear_bitmap(screen);
                                draw_sprite(screen,img,0,0);
                                textprintf_ex(screen, font, 20, 20, makecol(0,0,0),-1,"VEUILLEZ ENTRER UN NOMBRE DE LIGNES COMPRIS ENTRE 3 ET 20 et inférieur à %d:",*c);
                                *l=lireEntier(20,650,0,0,0);
                            }
                            clear_bitmap(screen);
                            draw_sprite(screen,img,0,0);
                            textprintf_ex(screen, font, 20, 20, makecol(0,0,0),-1,"VEUILLEZ ENTRER UN NOMBRE DE MINES:");
                            *m=lireEntier(20,400,0,0,0);
                            while((*m>((*l)*(*c)-1))||(*m<=0))
                            {
                                clear_bitmap(screen);
                                draw_sprite(screen,img,0,0);
                                textprintf_ex(screen, font, 20, 20, makecol(0,0,0),-1,"VEUILLEZ ENTRER UN NOMBRE DE MINES COMPRIS ENTRE 1 ET %d:",(*l)*(*c)-1);
                                *m=lireEntier(20,600,0,0,0);
                            }
                            done=1;
                        }
                    }
                    else
                    {
                        ch=0xFF;
                    }
                }
            }
        }
    }
    destroy_bitmap(buffer);
    destroy_bitmap(img);
}
//procédure affichant les instructions
void instruction()
{
    //ressources
    BITMAP* img1;
    BITMAP* buffer;
    int done=0;
    int W,H;
    char ch=0xFF;
    //chargement de l'image en mémoire
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    img1=create_bitmap(SCREEN_W,SCREEN_H);
    img1=load_bitmap("image/démineur3.bmp",NULL);
    if(!img1)
    {
        allegro_message("Impossible d'ouvrir img1");
    }
    //boucle d'éxécution
    while (!done)
    {
        //initialisation de la souri
        mouse_b=0;
        clear_bitmap(buffer);
        //affichage de l'image
        W=text_length(font,"REVENIR AU MENU PRINCIPAL");
        H=text_height(font);
        draw_sprite(buffer,img1,0,0);
        W=text_length(font,"REGLES DU JEU");
        rectfill(buffer,(SCREEN_W/2)-(W/2)-10,60,(SCREEN_W/2)+(W/2)+10,60+3*H,makecol(251,242,183));
        rect(buffer,(SCREEN_W/2)-(W/2)-10,60,(SCREEN_W/2)+(W/2)+10,60+3*H,makecol(208,192,122));
        rect(buffer,(SCREEN_W/2)-(W/2)-10-1,60-1,(SCREEN_W/2)+(W/2)+10+1,60+3*H+1,makecol(208,192,122));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 60+H, makecol(58,2,13), -1,"REGLES DU JEU");
        W=text_length(font,"BUT DU JEU");
        if(ch&0x01)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(251,242,183));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(208,192,122));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 60+100+H, makecol(58,2,13),-1,"BUT DU JEU");
        W=text_length(font,"COMMANDES DU JEU");
        if(ch&0x02)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(251,242,183));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(208,192,122));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 160+40+H, makecol(58,2,13),-1,"COMMANDES DU JEU");
        W=text_length(font,"REVENIR AU MENU PRINCIPAL");
        if(ch&0x04)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(251,242,183));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(208,192,122));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 200+40+H, makecol(58,2,13),-1,"REVENIR AU MENU PRINCIPAL");
        //affichage sur l'écran
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        //lecture du choix
        W=text_length(font,"BUT DU JEU");
        if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=160)&&(mouse_y<=60+100+3*H))
        {
            ch=0xFE;
            if(mouse_b&1)
            {
                afficher_butdujeu(25,20);
            }
        }
        else
        {
            W=text_length(font,"COMMANDES DU JEU");
            if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=200)&&(mouse_y<=200+3*H))
            {
                ch=0xFD;
                if(mouse_b&1)
                {
                    afficher_commandes(20,SCREEN_W-20);
                }
            }
            else
            {
                W=text_length(font,"REVENIR AU MENU PRINCIPAL");
                if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=240)&&(mouse_y<=240+3*H))
                {
                    ch=0xFB;
                    if(mouse_b&1)
                    {
                        done=1;
                    }
                }
                else
                {
                    ch=0xFF;

                }
            }
        }
    }
    //libération du bitmap
    destroy_bitmap(img1);
    destroy_bitmap(buffer);
}
//procédure affichant le menu du jeu
void menu(int* l,int* c,int* m,char* key)
{
    //ressources
    int done=0;
    int W,H;
    char ch=0xFF;
    BITMAP* img1;
    BITMAP* buffer;
    //création de l'image
    img1=create_bitmap(SCREEN_W,SCREEN_H);
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    //chargement des images
    img1=load_bitmap("image/démineur1.bmp",NULL);
    if(!img1)
    {
        allegro_message("Impossible d'ouvrir img1");
    }
    while (!done)
    {
        //initialisation de la souri
        mouse_b=0;
        clear_bitmap(buffer);
        //affichage de l'image
        W=text_length(font,"Bienvenue sur le jeu du DEMINEUR");
        H=text_height(font);
        draw_sprite(buffer,img1,0,0);
        rectfill(buffer,(SCREEN_W/2)-(W/2)-10,60,(SCREEN_W/2)+(W/2)+10,60+3*H,makecol(208,192,122));
        rect(buffer,(SCREEN_W/2)-(W/2)-10,60,(SCREEN_W/2)+(W/2)+10,60+3*H,makecol(150,0,24));
        rect(buffer,(SCREEN_W/2)-(W/2)-10-1,60-1,(SCREEN_W/2)+(W/2)+10+1,60+3*H+1,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 60+H, makecol(58,2,13), -1,"Bienvenue sur le jeu du DEMINEUR");
        W=text_length(font,"REGLES DU JEU");
        if(ch&0x01)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(208,192,122));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,60+100,(SCREEN_W/2)+(W/2)+10,60+100+3*H,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 60+100+H, makecol(58,2,13),-1,"REGLES DU JEU");
        W=text_length(font,"JOUER UNE NOUVELLE PARTIE");
        if(ch&0x02)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(208,192,122));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,160+40,(SCREEN_W/2)+(W/2)+10,160+40+3*H,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 160+40+H, makecol(58,2,13),-1,"JOUER UNE NOUVELLE PARTIE");
        W=text_length(font,"CHARGER UNE PARTIE");
        if(ch&0x04)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(208,192,122));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,200+40,(SCREEN_W/2)+(W/2)+10,200+40+3*H,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 200+40+H, makecol(58,2,13),-1,"CHARGER UNE PARTIE");
        W=text_length(font,"QUITTER");
        if(ch&0x08)
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,240+40,(SCREEN_W/2)+(W/2)+10,240+40+3*H,makecol(208,192,122));
        }
        else
        {
            rectfill(buffer,(SCREEN_W/2)-(W/2)-10,240+40,(SCREEN_W/2)+(W/2)+10,240+40+3*H,makecol(255,255,255));
        }
        rect(buffer,(SCREEN_W/2)-(W/2)-10,240+40,(SCREEN_W/2)+(W/2)+10,240+40+3*H,makecol(150,0,24));
        textprintf_centre_ex(buffer,font, SCREEN_W/2, 240+40+H, makecol(58,2,13),-1,"QUITTER");
        //affichage sur l'écran
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        //lecture
        W=text_length(font,"REGLES DU JEU");
        if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=160)&&(mouse_y<=60+100+3*H))
        {
            ch=0xFE;
            if(mouse_b&1)
            {
                instruction();
            }
        }
        else
        {
            W=text_length(font,"JOUER UNE NOUVELLE PARTIE");
            if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=200)&&(mouse_y<=200+3*H))
            {
                ch=0xFD;
                if(mouse_b&1)
                {
                    difficulte(l,c,m);
                    done=1;
                    clear_bitmap(screen);
                    rectfill(screen,0,0,SCREEN_W,SCREEN_H,makecol(102,0,0));
                    animation_bombe(100,100);
                    clear_bitmap(screen);
                }
            }
            else
            {
                W=text_length(font,"CHARGER UNE PARTIE");
                if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=240)&&(mouse_y<=240+3*H))
                {
                    ch=0xFB;
                    if(mouse_b&1)
                    {
                        done=1;
                        *key='C';
                        clear_bitmap(screen);
                        rectfill(screen,0,0,SCREEN_W,SCREEN_H,makecol(102,0,0));
                        animation_bombe(100,100);
                        clear_bitmap(screen);
                    }
                }
                else
                {
                    W=text_length(font,"QUITTER");
                    if((mouse_x>=(SCREEN_W/2)-(W/2)-10)&&(mouse_x<=(SCREEN_W/2)+(W/2)+10)&&(mouse_y>=280)&&(mouse_y<=280+3*H))
                    {
                        ch=0xF7;
                        if(mouse_b&1)
                        {
                            done=1;
                            *key='Q';
                        }
                    }
                    else
                    {
                        ch=0xFF;
                    }
                }
            }
        }
    }
    //libérer la mémoire allouer pour les BITMAP
    destroy_bitmap(buffer);
    destroy_bitmap(img1);
}
