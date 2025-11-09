
int lru(int p[],int n,int f)
{
    int fr[f],last[f],i,j;
    int fault=0;
    for(int i=0;i<f;i++)
    {
        last[i]=fr[i]=-1;
    }

    for(int i=0;i<n;i++)
    {
        int hit=0;
        for(int j=0;j<f;j++)
        {
            if(fr[j]==p[i])
            {
                hit=1;
                last[j]=i;
                break;
            }
        }

        if(hit==0)
        {
            int l=0;
            for(int j=1;j<f;j++)
            {
                if(last[j]>last[l])
                {
                    l=j;
                }
            }

            fr[l]=p[i];
            last[l]=i;
            fault++;
        }
    }
    return fault;
}
