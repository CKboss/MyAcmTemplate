char t[1000],p[1000];
int f[1000];

void getfail(char* p,int* f)
{
    int m=strlen(p);
    f[0]=f[1]=0;
    for(int i=1;i<m;i++)
    {
        int j=f[i];
        while(j&&p[j]!=p[i]) j=f[j];
        f[i+1]=(p[i]==p[j])?j+1:0;
    }
}

void kmp(char* t,char* p,int* f)
{
    int n=strlen(t),m=strlen(p);
    getfail(p,f);
    int j=0;
    for(int i=0;i<n;i++)
    {
        while(j&&p[j]!=t[i]) j=f[j];
        if(p[j]==t[i]) j++;
        if(j==m)
        {
            ///i-m+1
            /// ans++; 
            j=f[j];
        }
    }
}
