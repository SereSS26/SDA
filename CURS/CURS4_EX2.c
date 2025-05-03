#include <stdio.h>

void functie(int n)
{   
    int i=0;
    int j=0;
    while(n>1) 
    {
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                printf("*");
            }
        }
        n=n-3;
    }
}

int main(void) 
{
    int n;
    scanf("%d",&n);
    functie(n);

    return 0;
}
