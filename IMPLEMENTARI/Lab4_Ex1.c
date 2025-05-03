#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGIME_NUME 200
#define MAXIM_NUMAR_STUDENTI 5001

typedef struct{
    char nume[LUNGIME_NUME];
    char data1[LUNGIME_NUME];
    char data2[LUNGIME_NUME];
    char data3[LUNGIME_NUME];
    char data4[LUNGIME_NUME];
}Student;

void citire(FILE *fis,Student *studenti,int *numar_studenti)
{
    int index=0;
    char buffer[LUNGIME_NUME];
    while(fgets(buffer,LUNGIME_NUME,fis)!=NULL)
    {
        buffer[strcspn(buffer,"\n")]='\0';
        strcpy(studenti[index].nota,buffer);
        
    }
}

int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("Studenti1.txt","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("Lab4.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisiere iesire\n");
        exit(-1);
    }
    Student studenti[MAXIM_NUMAR_STUDENTI];
    int numar_studenti=0;
    citire(fis,studenti,&numar_studenti);

    return 0;
}