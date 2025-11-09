#include <stdio.h>

int main()
{
    int n,m;
    FILE *f=fscanf("./state.txt","r");
    if(!f)
    {
        printf("not opening");
        return 1;
    }

    fscanf(f,"%d %d",&n,&m);
    int alloc[10][10],need[10][10],max[10][10], avail[10];

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
        fscanf("%d",&alloc[i][j]);
        }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
        fscanf("%d",&max[i][j]);
        }
    }

    for(int i=0;i<m;i++)
    {
        fscanf("%d",&avail[i]);
    }


    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
        need[i][j]=alloc[i][j]-max[i][j];
        if(need[i][j]<0)
        {
            printf("error");
            return 0;
        }
        }
    }


    int work[10],finish[10]={0},ans[10],count=0;
    
    for(int j=0;j<m;j++)
    {
        work[j]=avail[j];
    }

    while(count<n)
    {
        int found=0;
        for(int i=0;i<n;i++)
        {
            if(!finish[i])
            {
                int j;
                for(j=0;j<m;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        break;
                    }
                }

                if(j==m)
                {
                    for(int k=0;k<m;k++)
                    {
                        work[k]+=alloc[i][k];
                    }

                    ans[count]=i;
                    count++;
                    finish[i]=1;
                    found=1;
                }
            }
        }


    }
    




}