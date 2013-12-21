//URAL 1297 
//
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char str[1100],ans[3300];
int p[3300],pos,how;

void pre()
{
    int tot=1;
    memset(ans,0,sizeof(ans));
    ans[0]='$';
    int len=strlen(str);
    for(int i=0;i<len;i++)
    {
        ans[tot]='#';tot++;
        ans[tot]=str[i];tot++;
    }
    ans[tot]='#';
}

void manacher()
{
    pos=-1;how=0;
    memset(p,0,sizeof(p));
    int len=strlen(ans);
    int mid=-1,mx=-1;
    for(int i=0;i<len;i++)
    {
        int j=-1;
        if(i<mx)
        {
            j=2*mid-i;
            p[i]=min(p[j],mx-i);
        }
        else p[i]=1;

        while(i+p[i]<len&&ans[i+p[i]]==ans[i-p[i]])
        {
            p[i]++;
        }

        if(p[i]+i>mx)
        {
            mx=p[i]+i; mid=i;
        }
        if(p[i]>how)
        {
            how=p[i]; pos=i;
        }
    }
}

int main()
{
    while(scanf("%s",str)!=EOF)
    {
        pre();
        manacher();
        how--;
        for(int i=pos-how;i<=pos+how;i++)
        {
            if(ans[i]!='#') putchar(ans[i]);
        }
        putchar(10);
    }
    return 0;
}
