#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIM_STUDENTI 5050
#define LUNGIME_CHEIE 200

typedef struct{
    char nume[LUNGIME_CHEIE];
    char cheia1[LUNGIME_CHEIE];
    char cheia2[LUNGIME_CHEIE];
    char cheia3[LUNGIME_CHEIE];
    char cheia4[LUNGIME_CHEIE];
    double nota;
}Student;
void citire(FILE *fis,Student *studenti,int *numar_studenti)
{
    char buffer[LUNGIME_CHEIE];
    int index=0;
    char *p=NULL;
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {
        buffer[strcspn(buffer,"\n")]='\0';
        strcpy(studenti[index].nume,buffer);
        fgets(buffer,sizeof(buffer),fis);
        buffer[strcspn(buffer,"\n")]='\0';
        p=strtok(buffer," ");
        if(p!=NULL)
        {
            strcpy(studenti[index].cheia1,p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            strcpy(studenti[index].cheia2,p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            strcpy(studenti[index].cheia3,p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            strcpy(studenti[index].cheia4,p);
        }
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
        fprintf(gis,"%s\n%s %s %s %s\n%0.2lf\n",studenti[i].nume,studenti[i].cheia1,studenti[i].cheia2,studenti[i].cheia3,studenti[i].cheia4,studenti[i].nota);
    }
}
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("Studenti3.txt","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier de intrare\n");
        exit(-1);
    }
    gis=fopen("Lab5.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier de iesire\n");
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