//bibliothèque
#include "main.h"

//procédure déterminant les coordonnées de la case marquée par le curseur
void curseur(t_case** T,int* i,int* j,int l,int c)
{
    //ressources
    int g,k;
    for(g=0;g<l;g++)
    {
        for(k=0;k<c;k++)
        {
            if(T[g][k].curseur==1)
            {
                *i=g;
                *j=k;
            }
        }
    }
}
