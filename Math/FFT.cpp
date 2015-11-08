/* ***********************************************
Author        :CKboss
Created Time  :2015年11月08日 星期日 10时10分45秒
File Name     :fft.cpp
************************************************ */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

const double PI = acos(-1.0);

struct Complex
{
    double x,y;
    Complex(double _x=0.0,double _y=0.0):x(_x),y(_y) {}
    Complex operator - (const Complex &b) const {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator + (const Complex &b) const {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator * (const Complex &b) const {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
    Complex operator / (const Complex &b) const {
        double D=b.x*b.x+b.y*b.y;
        return Complex((x*b.x+y*b.y)/D,(x*b.y-y*b.x)/D);
    }
};

/// len 必须取2的幂
void change(Complex y[],int len)
{
    int i,j,k;
    for(i=1,j=len/2;i<len-1;i++)
    {
        if(i<j) swap(y[i],y[j]);
        k=len/2;
        while(j>=k)
        {
            j-=k; k/=2;
        }
        if(j<k) j+=k;
    }
}

//on==1 DFT on==-1 IDFT
void fft(Complex y[],int len,int on)
{
    change(y,len);
    for(int h=2;h<=len;h<<=1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j=0;j<len;j+=h)
        {
            Complex w(1,0);
            for(int k=j;k<j+h/2;k++)
            {
                Complex u=y[k];
                Complex t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
    {
        for(int i=0;i<len;i++) y[i].x/=len;
    }
}

const int maxn=100010;
Complex x1[maxn*2],x2[maxn*2];
char str1[maxn],str2[maxn];
int sum[maxn*2];

int len1,len2,len;

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    while(scanf("%s%s",str1,str2)!=EOF)
    {
        len1=strlen(str1); len2=strlen(str2);
        len=1;
        while(len<len1*2||len<len2*2) len<<=1;

        for(int i=0;i<len;i++)
        {
            if(i<len1) x1[i]=Complex(str1[len1-1-i]-'0',0);
            else x1[i]=Complex(0,0);

            if(i<len2) x2[i]=Complex(str2[len2-1-i]-'0',0);
            else x2[i]=Complex(0,0);
        }

        fft(x1,len,1);
        fft(x2,len,1);

        for(int i=0;i<len;i++) x1[i]=x1[i]*x2[i];

        fft(x1,len,-1);

        for(int i=0;i<len;i++)
            sum[i]=(int)(x1[i].x+0.5);

        for(int i=0;i<len;i++)
        {
            sum[i+1]+=sum[i]/10;
            sum[i]%=10;
        }

        len=len1+len2-1;
        while(sum[len]<=0&&len>0) len--;
        for(int i=len;i>=0;i--) putchar(sum[i]+'0');
        putchar(10);
    }
    
    return 0;
}
