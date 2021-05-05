#include<stdio.h>
#include<stdlib.h>
int **return_arr()
{
    int **arr=(int **)malloc(sizeof(int *)*5);
    int i,j;
    for(i=0;i<5;i++)//checking purpose
    {
        arr[i]=(int *)malloc(sizeof(int)*5);
        for(j=0;j<5;j++)
        {
            arr[i][j]=i*10+j;
        }
    }
    return arr;
}

int main()
{
    int **now;
    now=return_arr();
    int i,j;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            printf("%d ",now[i][j]);
        }
        printf("\n");
    }
    return 0;
}
