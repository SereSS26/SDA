#include <stdio.h>
#include <stdlib.h>

void bisect(int an,int *ok)
{
    if((an%4==0 && an%100!=0)||(an%400==0))
        *ok=1;
}
int main(void)
{   
    int an=0,ok=0;
    printf("Anul este: ");
    scanf("%d",&an);
    bisect(an,&ok);
    printf("Este bisect?: ");
    if(ok==0)
        printf("NU\n");
    else
        printf("DA\n");

    return 0;
}