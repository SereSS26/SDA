#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 4
#define N 3

int harta[N][N];
int culori[MAX]={1,2,3,4};

int dx[]={-1,-1,1,1};
int dy[]={-1,1,1,-1};

void afisare()
{
    int i=0,j=0;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d ",harta[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int valid(int x, int y, int c) {
    int i;
    for (i = 0; i < 4; i++) {  // Verifică vecinii pe diagonale
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Verifică dacă vecinul este valid (în limitele matricei)
        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            // Dacă vecinul are aceeași culoare, nu este valid
            if (harta[nx][ny] == c) {
                return 0;
            }
        }
    }
    return 1;  // Dacă nu sunt conflicte, culoarea este validă
}
int contor=0;
void back(int x,int y)
{
    if(x==N)
    {   
        if(contor==0)
        {
            afisare();
            contor++;
        }
        return;
    }      
    if(y==N)
    {
        back(x+1,0);
        return;
    }
    int c=0;
    for(c=0;c<MAX;c++)
    {
        if(valid(x,y,culori[c])==1)
        {
            harta[x][y]=culori[c];
            back(x, y + 1);

            // Dacă nu am găsit o soluție, revenim (backtracking)
            harta[x][y] = 0;
            
        }
    }

}
int main(void)
{
    back(0,0);

    return 0;
}