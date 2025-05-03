#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIM_STUDENTI 5050
#define LUNGIME_NUME 200

typedef struct{
    char nume[LUNGIME_NUME];
    double nota;
}Student;
void citire(FILE *fis,Student *studenti,int *numar_studenti)
{
    int index=0;
    char buffer[LUNGIME_NUME];
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {
        buffer[strcspn(buffer,"\n")]='\0';
        strcpy(studenti[index].nume,buffer);    
        fgets(buffer,sizeof(buffer),fis);
        buffer[strcspn(buffer,"\n")]='\0';
        studenti[index].nota=atof(buffer);
        index++;
    }
    *numar_studenti=index;
}
void afisare(FILE *gis,Student *studenti,int numar_studenti)
{
    int i=0;
    for(i=0;i<numar_studenti;i++)
    {
        fprintf(gis,"%s\n%0.2lf\n",studenti[i].nume,studenti[i].nota);
    }
}
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("Studenti2.txt","r");
    if(fis==NULL)
    {
        perror("Eroare la deschiderea fiserului de intrare\n");
        exit(-1);
    }
    gis=fopen("Lab5.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschiderea fiserului de iesire\n");
        exit(-1);
    }
    Student studenti[MAXIM_STUDENTI];
    int numar_studenti=0;
    citire(fis,studenti,&numar_studenti);
    afisare(gis,studenti,numar_studenti);
    fclose(fis);
    fclose(gis);

    return 0;
}