#include "main.h"

//fonction permettant de lire le nom du fichier saisi par l'utilisateur
char* lireNomFichier(char* nomfichier,char* format)
{
    //ressources
    char* ch=NULL;
    FILE* fp=NULL;
    //lire le nom du fichier
    nomfichier=question_ouverte("Comment souhaitez-vous nommer votre fichier ?",nomfichier);
    //ajout du préfixe sauvegarde/
    ch=(char*)malloc((strlen(nomfichier)+1)*sizeof(char));
    ch=strcpy(ch,nomfichier);
    nomfichier=strcpy(nomfichier,"sauvegarde/");
    nomfichier=strcat(nomfichier,ch);
    //ajout du suffixe .txt
    nomfichier=strcat(nomfichier,format);
    //écrire le nom du fichier dans un fichier texte
    fp=fopen("sauvegarde/nomfichier.txt","a");
    if(fp!=NULL)
    {
        fprintf(fp,"%s \n",nomfichier);
        fclose(fp);
    }
    else
    {
        allegro_message("Problème d'ouverture de nomfichier en écriture");
    }
    //libération de la mémoire
//    free(ch);
    //retour de nomfichier
    return nomfichier;
}
//procédure sauvegardant la partie
char* sauvegarde(t_case** T,int l,int c,int m,int D,char* nomfichier)
{
    //ressources
    FILE* fp=NULL;
    int i=0,j=0;
    if(strcmp(nomfichier,"%%%%")==0)
    {
        //lire le nom du fichier de sauvegarde
        nomfichier=lireNomFichier(nomfichier,".txt");
    }
    //création du fichier
    fp=fopen(nomfichier,"w");
    if(fp!=NULL)
    {
        //écrire le nombre de lignes, de colonnes et de mines de la matrice de jeu
        fprintf(fp,"%d ",l);
        fprintf(fp,"%d ",c);
        fprintf(fp,"%d ",m);
        fprintf(fp,"%d \n",D);
        //écrire toutes les T[i][j].mine
        for(i=0; i<l; i++)
        {
            for(j=0; j<c; j++)
            {
                if(j==c-1)
                {
                    fprintf(fp,"%c \n",T[i][j].mine);
                }
                else
                {
                    fprintf(fp,"%c",T[i][j].mine);
                }
            }
        }
        //écrire toutes les T[i][j].cache
        for(i=0; i<l; i++)
        {
            for(j=0; j<c; j++)
            {
                if(j==c-1)
                {
                    fprintf(fp,"%d \n",T[i][j].cache);
                }
                else
                {
                    fprintf(fp,"%d ",T[i][j].cache);
                }
            }
        }
        //écrire toutes les T[i][j].drapeau
        for(i=0; i<l; i++)
        {
            for(j=0; j<c; j++)
            {
                if(j==c-1)
                {
                    fprintf(fp,"%d \n",T[i][j].drapeau);
                }
                else
                {
                    fprintf(fp,"%d ",T[i][j].drapeau);
                }
            }
        }
        //écrire toutes les T[i][j].nombre
        for(i=0; i<l; i++)
        {
            for(j=0; j<c; j++)
            {
                if(j==c-1)
                {
                    fprintf(fp,"%d \n",T[i][j].nombre);
                }
                else
                {
                    fprintf(fp,"%d ",T[i][j].nombre);
                }
            }
        }
        //écrire toutes les T[i][j].curseur
        for(i=0; i<l; i++)
        {
            for(j=0; j<c; j++)
            {
                if(j==c-1)
                {
                    fprintf(fp,"%d \n",T[i][j].curseur);
                }
                else
                {
                    fprintf(fp,"%d ",T[i][j].curseur);
                }
            }
        }
        //fermeture du fichier
        fclose(fp);
    }
    else
    {
        allegro_message("ouverture du fichier en écriture impossible");
    }
    return nomfichier;
}
//fonction chargeant une partie
t_case** charge(t_case** T,int* l,int* c,int* m,int* D,char** nomfichier)
{
    //ressources
    FILE* fp=NULL;
    FILE* fp1=NULL;
    int i,j;
    char ch[100];
    char tab[500];
    char Ch='0';
    char C='0';
    //lire le nom du fichier
    fp1=fopen("sauvegarde/nomfichier.txt","r");
    if(fp1!=NULL)
    {
        while(C!='O')
        {
            Ch=fgetc(fp1);
            while((Ch!=EOF)&&(C!='O'))
            {
                fseek(fp1,-1L,SEEK_CUR);
                fscanf(fp1,"%s",tab);
                fgets(ch,5,fp1);
                C=question_ferme("Voulez-vous charger",tab);
                if(C=='O')
                {
                    *nomfichier=(char*)malloc((strlen(tab)+1)*sizeof(char));
                    *nomfichier=strcpy(*nomfichier,tab);
                }
                Ch=fgetc(fp1);
            }
            rewind(fp1);
            if(C!='O')
            {
                C=question_ferme("Souhaitez-vous revenir au menu","\0");
            }
        }
        fclose(fp1);
        if(strcmp(*nomfichier,"%%%%")!=0)
        {
            //lire le fichier
            fp=fopen(*nomfichier,"r");
            if(fp!=NULL)
            {
                //lire le nombre de lignes, de colonnes et de mines de la matrice de jeu
                fscanf(fp,"%d",l);
                fscanf(fp,"%d",c);
                fscanf(fp,"%d",m);
                fscanf(fp,"%d",D);
                fgets(ch,100,fp);
                //allocation dynamique de la matrice de jeu
                T=allocationTab(T,*l,*c);
                //lire toutes les T[i][j].mine
                for(i=0; i<*l; i++)
                {
                    for(j=0; j<*c; j++)
                    {
                        T[i][j].mine=fgetc(fp);
                    }
                    fgets(ch,100,fp);
                }
                //lire toutes les T[i][j].cache
                for(i=0; i<*l; i++)
                {
                    for(j=0; j<*c; j++)
                    {
                        fscanf(fp,"%d",&(T[i][j].cache));
                    }
                    fgets(ch,100,fp);
                }
                //lire toutes les T[i][j].drapeau
                for(i=0; i<*l; i++)
                {
                    for(j=0; j<*c; j++)
                    {
                        fscanf(fp,"%d",&(T[i][j].drapeau));
                    }
                    fgets(ch,100,fp);
                }
                //lire toutes les T[i][j].nombre
                for(i=0; i<*l; i++)
                {
                    for(j=0; j<*c; j++)
                    {
                        fscanf(fp,"%d",&(T[i][j].nombre));
                    }
                    fgets(ch,100,fp);
                }
                //lire toutes les T[i][j].curseur
                for(i=0; i<*l; i++)
                {
                    for(j=0; j<*c; j++)
                    {
                        fscanf(fp,"%d",&(T[i][j].curseur));
                    }
                    fgets(ch,100,fp);
                }
                //fermeture du fichier
                fclose(fp);
            }
            else
            {
                allegro_message("Ouverture en lecture du fichier %s impossible: vous avez peut-etre supprimé ce fichier",*nomfichier);
            }
        }
    }
    else
    {
        allegro_message("ouverture de nomfichier en lecture impossible: vérifiez que vous n'ayez pas supprimé ce fichier");
    }
    return T;
}
