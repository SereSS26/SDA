#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 3

int a[]={1,2,3,4,5,6};
int v[MAX];

int valid(int k)
{
    int contor=0;
    if(k==1)
    {
        if(v[k]!=2&&v[k]!=4)
            return 0;
    }
    for(int i=0;i<=k;i++)
    {
        if(v[i]==1)
            contor++;
    }
    if(contor!=1)
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
        printf("%d ",v[i]);
    }
    printf("\n");
}
void back(int k)
{
    for(int i=0;i<6;i++)
    {
        v[k]=a[i];
        if(valid(k)==1)
        {
            if(solutie(k)==1)
            {
                afisare(k);
            }
            back(k+1);
        }
    }
}
int main(void)
{   
    back(0);

    return  0;
}