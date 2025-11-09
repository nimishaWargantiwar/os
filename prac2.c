#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>

int main(int narg,char *arg[])
{
    int n=narg-1;
    int a[n];
    for(int i=0;i<n;i++)
    {
        a[i]=atoi(arg[i+1]);
    }

    int l=0,m,key,h=n-1,flag=0;
    printf("enter the key : ");
    scanf("%d",&key);
    while(l<=h)
    {
        m=(l+h)/2;
        if(a[m]==key)
        {
            flag=1;
            break;
        }
        else if(a[m]<key)
        {
            l=m+1;
        }
        else 
        {
            h=m-1;
        }
    }

    if(flag)
    {
        printf("the element %d found at index : %d",key,m+1);
    }
    else
    {
        printf("no");
    }
}