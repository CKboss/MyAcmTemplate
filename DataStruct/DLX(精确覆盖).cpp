/*POJ3076 Sudoku DLX(精确覆盖)*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=16;
const int maxn=N*N*N+10;
const int maxm=N*N*4+10;
const int maxnode=maxn*4+maxm+10;

char sudoku[maxn];

struct DLX
{
	int n,m,size;
	int U[maxnode],D[maxnode],L[maxnode],R[maxnode],Row[maxnode],Col[maxnode];
	int H[maxnode],S[maxnode];
	int ansd,ans[maxn];
	void init(int _n,int _m)
	{
		n=_n; m=_m;
		for(int i=0;i<=m;i++)
		{
			S[i]=0;
			U[i]=D[i]=i;
			L[i]=i-1;
			R[i]=i+1;
		}
		R[m]=0; L[0]=m;
		size=m;
		for(int i=1;i<=n;i++) H[i]=-1;
	}
	void Link(int r,int c)
	{
		++S[Col[++size]=c];
		Row[size]=r;
		D[size]=D[c];
		U[D[c]]=size;
		U[size]=c;
		D[c]=size;
		if(H[r]<0) H[r]=L[size]=R[size]=size;
		else
		{
			R[size]=R[H[r]];
			L[R[H[r]]]=size;
			L[size]=H[r];
			R[H[r]]=size;
		}
	}
	void remove(int c)
	{
		L[R[c]]=L[c]; R[L[c]]=R[c];
		for(int i=D[c];i!=c;i=D[i])
			for(int j=R[i];j!=i;j=R[j])
			{
				U[D[j]]=U[j];
				D[U[j]]=D[j];
				--S[Col[j]];
			}
	}
	void resume(int c)
	{
		for(int i=U[c];i!=c;i=U[i])
			for(int j=L[i];j!=i;j=L[j])
				++S[Col[U[D[j]]=D[U[j]]=j]];
		L[R[c]]=R[L[c]]=c;
	}
	bool Dance(int d)
	{
		if(R[0]==0)
		{
			for(int i=0;i<d;i++) sudoku[(ans[i]-1)/16]=(ans[i]-1)%16+'A';
			//printf("%s\n",sudoku);
			for(int i=0,sz=N*N;i<sz;i++)
            {
                putchar(sudoku[i]);
                if((i+1)%16==0) putchar(10);
            }
			return true;
		}
		int c=R[0];
		for(int i=R[0];i!=0;i=R[i])
			if(S[i]<S[c]) c=i;
		remove(c);
		for(int i=D[c];i!=c;i=D[i])
		{
			ans[d]=Row[i];
			for(int j=R[i];j!=i;j=R[j]) remove(Col[j]);
			if(Dance(d+1)) return true;
			for(int j=L[i];j!=i;j=L[j]) resume(Col[j]);
		}
		resume(c);
		return false;
	}
};

DLX dlx;

void place(int& r,int& c1,int& c2,int& c3,int& c4,int i,int j,int k)
{
	r=(i*N+j)*N+k;
	c1=i*N+j+1;
	c2=N*N+N*i+k;
	c3=N*N*2+N*j+k;
	c4=N*N*3+((i/4)*4+(j/4))*N+k;
}

int main()
{
	while(scanf("%s",sudoku)!=EOF)
	{
		for(int i=1;i<16;i++)
            scanf("%s",sudoku+i*16);
		dlx.init(N*N*N,N*N*4);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				for(int k=1;k<=N;k++)
				{
					if(sudoku[i*N+j]=='-'||sudoku[i*N+j]==k+'A'-1)
					{
						int r,c1,c2,c3,c4;
						place(r,c1,c2,c3,c4,i,j,k);
						dlx.Link(r,c1);
						dlx.Link(r,c2);
						dlx.Link(r,c3);
						dlx.Link(r,c4);
					}
				}
			}
		}
		dlx.Dance(0);
		putchar(10);
	}
	return 0;
}

