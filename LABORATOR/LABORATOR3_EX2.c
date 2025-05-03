#include "timer.h"
#include <stdio.h>
#include <stdlib.h>


int Fibo1(int n)
{
    if(n<=1)
    {
        return n;
    }
    return Fibo1(n-1)+Fibo1(n-2);
}
int Fibo2(int n)
{   
    int a=0,b=1,c=0,i=0;
    if(n<=1)
    {
        return n;
    }
    for(i=2;i<=n;i++)
    {
        c=a+b;
        a=b;
        b=c;
    }
    return b;
}
void Tipareste(FILE *fis, const char *algoritm, int m, float timp)
{	
    fprintf(fis,"%s,%d,%.6f\n",algoritm,m,timp);
}
int main(void)
{ 
	FILE *fis=NULL;
	fis=fopen("results.txt","w");
	if(fis==NULL)
	{
		perror("Eroare la deschiderea fiserului\n");
		exit(-1);
	}
	int input[]={5, 10, 20, 30, 40};
    int n=sizeof(input)/sizeof(input[0]);
    int i=0,m=0;
	for(i=0;i<n;i++)
	{   
        m=input[i];
        starton();
        Fibo1(m);
        float timp1=startoff();
        Tipareste(fis,"Fibonacci recursiv",m,timp1);

        starton();
        Fibo2(m);
        float timp2=startoff();
        Tipareste(fis,"Fibonacci iterativ",m,timp2);
 
	}
	fclose(fis);

	return 0;
} 