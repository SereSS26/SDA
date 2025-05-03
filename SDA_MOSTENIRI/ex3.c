#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

int a[]={1,2,3};
int v[MAX];
int contor=0;

int valid(int k)
{
    int contor_a=0;
    int contor_b=0;
    int contor_c=0;
    for(int i=0;i<=k;i++)
    {
        if(v[i]==1)
            contor_a++;
        if(v[i]==2)
            contor_b++;
        if(v[i]==3)
            contor_c++;
    }
    if(contor_a>3||contor_b>4||contor_c>3)
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
    for(int i=0;i<=k;i++)
    {
        printf("%d",v[i]);
    }
    printf("\n");
}
void back(int k)
{
    if(contor<6)
    {
        for(int i=0;i<3;i++)
        {
            v[k]=a[i];
            if(valid(k)==1)
            {
                if(solutie(k)==1)
                {
                    afisare(k);
                    contor++;
                }
                back(k+1);
            }
        }
    }
}
int main(void)
{   
    back(0);

    return 0;
}