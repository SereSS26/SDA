#include <stdio.h>
#define MAX 100

int vizitat[MAX][MAX];
int directieX[]={-1,1,0,0};
int directieY[]={0,0,-1,1};

int valid(int x,int y,int n,int m,int matrice[MAX][MAX]) 
{   
    int ok=0;
    if(x>=0&&x<n&&y>=0&&y<m&&matrice[x][y]==1&&vizitat[x][y]==0)
        ok=1;
    return ok;
}
int verifica(int x,int y,int n,int m,int matrice[MAX][MAX])
{
    vizitat[x][y]=1;
    int lungime=1; 
    int i=0;
    for(i=0;i<4;i++)
    {
        int nx=x+directieX[i];
        int ny=y+directieY[i];
        if(valid(nx,ny,n,m,matrice))
        {
            lungime=lungime+verifica(nx,ny,n,m,matrice);
        }
    }
    return lungime;
}
int gasesteLungimeMaxima(int n, int m, int matrice[MAX][MAX])
{
    int lungimeMaxima=0;
    int lungimeCurenta=0;
    int i=0,j=0;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            vizitat[i][j]=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(matrice[i][j]==1&&!vizitat[i][j])
            {
                lungimeCurenta=verifica(i,j,n,m,matrice);
                if(lungimeCurenta>lungimeMaxima)
                {
                    lungimeMaxima=lungimeCurenta;
                }
            }
        }
    }
    return lungimeMaxima;
}
int main(void) {
    int matrice[MAX][MAX]={
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 1}
    };
    int n = 5; 
    int m = 5; 
    int rezultat=gasesteLungimeMaxima(n,m,matrice);
    printf("Lungimea maxima de celule conectate este: %d\n", rezultat);

    return 0;
}
