#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

int a[3]={'a','b','c'};
int v[MAX];
int contor=0;

int valid(int k)
{
    int contor_a=0;
    int contor_b=0;
    int contor_c=0;
    int i=0;
    for(i=0;i<=k;i++)
    {
        if(v[i]=='a')
            contor_a++;
        if(v[i]=='b')
            contor_b++;
        if(v[i]=='c')
            contor_c++;
    }
    if(contor_a>3)
        return 0;
    if(contor_b>4)
        return 0;
    if(contor_c>3)
        return 0;
    return 1;
}
int solutie(int k)
{
    if(k==MAX-1)
        return 1;
    return 0;
}
void afisare(int k)
{
    int i=0;
    for(i=0;i<=k;i++)
    {
        printf("%c",v[i]);
    }
    printf("\n");
}
void back(int k)
{   
    int i=0;
    if(contor<6)
    {
        for(i=0;i<3;i++)
        {   
            v[k]=a[i];
            if(valid(k)==1)
            {
                if(solutie(k)==1)
                {   
                    afisare(k);
                    contor++;
                }
                else
                {
                    back(k+1);
                }
            }
        }
    }
}

int main(void)
{
    back(0);

    return 0;
}