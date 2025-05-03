#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIM_FILME 5050
#define LUNGIME_NUME 200

typedef struct{
    int an;
    int durata;
    char nume[LUNGIME_NUME];
    char categorie[LUNGIME_NUME];
    char premiu[LUNGIME_NUME];
}Film;

void citire(FILE *fis,Film *filme,int *numar_filme)
{
    int index=0;
    char buffer[LUNGIME_NUME];
    fgets(buffer,sizeof(buffer),fis);
    char *p=NULL;
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {   
        buffer[strcspn(buffer,"\n")]='\0';
        p=strtok(buffer,"\t");
        if(p!=NULL)
        {
            filme[index].an=atoi(p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            filme[index].durata=atoi(p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(filme[index].nume,p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(filme[index].categorie,p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(filme[index].premiu,p);
        }
        index++;
    }
    *numar_filme=index;
}
void afisare(FILE *gis,Film *filme,int numar_filme)
{
    int i=0;
    for(i=0;i<numar_filme;i++)
    {
        fprintf(gis,"%d %d %s %s %s\n",filme[i].an,filme[i].durata,filme[i].nume,filme[i].categorie,filme[i].premiu);
    }
}
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("Filme.txt","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier de intrare\n");
        exit(-1);
    }
    gis=fopen("Lab8.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier de iesire\n");
        exit(-1);
    }
    Film filme[MAXIM_FILME];
	Film filme_aux[MAXIM_FILME];
    int numar_filme=0;
    citire(fis,filme,&numar_filme);
    afisare(gis,filme,numar_filme);
    fclose(fis);
    fclose(gis);
    
    return 0;
}