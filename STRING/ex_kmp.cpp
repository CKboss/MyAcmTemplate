/*
扩展KMP
next[i]: P[i..m-1] 与 P[0..m-1]的最长公共前缀
ex[i]: T[i..n-1] 与 P[0..m-1]的最长公共前缀
×/

char T[maxn],P[maxn];  
int next[maxn],ex[maxn];  
  
void pre_exkmp(char P[])  
{  
    int m=strlen(P);  
    next[0]=m;  
    int j=0,k=1;  
    while(j+1<m&&P[j]==P[j+1]) j++;  
    next[1]=j;  
    for(int i=2;i<m;i++)  
    {  
        int p=next[k]+k-1;  
        int L=next[i-k];  
        if(i+L<p+1) next[i]=L;  
        else  
        {  
            j=max(0,p-i+1);  
            while(i+j<m&&P[i+j]==P[j]) j++;  
            next[i]=j; k=i;  
        }  
    }  
}  
  
void exkmp(char P[],char T[])  
{  
    int m=strlen(P),n=strlen(T);  
    pre_exkmp(P);  
    int j=0,k=0;  
    while(j<n&&j<m&&P[j]==T[j]) j++;  
    ex[0]=j;  
    for(int i=1;i<n;i++)  
    {  
        int p=ex[k]+k-1;  
        int L=next[i-k];  
        if(i+L<p+1) ex[i]=L;  
        else  
        {  
            j=max(0,p-i+1);  
            while(i+j<n&&j<m&&T[i+j]==P[j]) j++;  
            ex[i]=j; k=i;  
        }  
    }  
}  
