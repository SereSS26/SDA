#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void afisare_indentare(FILE *gis, int nivel_indentare)
{   
    int i=0;
    for(i=0;i<nivel_indentare;i++)
    {
        fputc('\t',gis);
    }
}
void formateaza_cod(FILE *fis,FILE *gis) 
{
    int nivel_indentare=0;
    char c, precedent='\0';
    int newline=1;
    while((c=fgetc(fis))!=EOF)
    {
        switch(c) 
        {
            case '{':
                if(!newline) 
                    fputc('\n',gis);
                afisare_indentare(gis, nivel_indentare);
                fputc(c,gis);
                fputc('\n',gis);
                nivel_indentare++;
                newline=1;
                break;
            case '}':
                nivel_indentare--;
                afisare_indentare(gis,nivel_indentare);
                fputc(c,gis);
                fputc('\n',gis);
                newline=1;
                break;
            case ';':
                fputc(c,gis);
                fputc('\n',gis);
                newline=1;
                break;
            case '(':
                fputc(' ',gis);
                fputc(c,gis);
                break;
            case ')':
                fputc(c,gis);
                break;
            case ' ':
                if(precedent!=' '&&precedent!='\n'&&precedent!='\t')
                    fputc(c,gis);
                break;
            case'\n':
                newline=1;
                break;
            default:
                if(newline)
                {
                    afisare_indentare(gis,nivel_indentare);
                    newline=0;
                }
                fputc(c,gis);
        }
        precedent=c;
    }
}
int main(void)
{
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("curs9.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("curs9.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier iesire\n");
        exit(-1);
    }
    formateaza_cod(fis,gis);
    fclose(fis);
    fclose(gis);

    return 0;
}
