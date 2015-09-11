
/*
采用的hash表达式如下 
对于结点u, u有儿子结点v1, v2, ..., vk 
其中儿子结点的Hash值已经处理出来时H[1~k] 
那么首先对于Hash值进行排序, (相同的子树的hash值一定是一样的, 于是同构的子树一定会被排在一起 
Hash(v) = ((...(((((a*p ^ H[1]) mod q) *p ^ H[2]) % q) * p ^ .... H[k - 1]) mod q)*p ^ H[k]) * b % q 
其中a, p, q, b为参数自选, ^表示异或, 这里没考虑优先级问题, 表达式从左向右计算 
*/

LL Hash[maxn];

const LL h_A=233LL,h_P=23333LL,h_B=50009LL,h_Q=1e9+1027LL;

void GetHash(int u,int fa)
{
	vector<LL> hs;
	for(int i=Adj[u];~i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa) continue;
		GetHash(v,u);
		hs.push_back(Hash[v]);
	}
	int sz=hs.size();
	if(sz==0)
	{
		Hash[u]=h_A*h_P;
		Hash[u]*=h_B;
		Hash[u]%=h_Q;
		return ;
	}
	sort(hs.begin(),hs.end());
	LL HS=h_A;
	for(int i=0;i<sz-1;i++)
	{
		HS=HS*h_P;
		HS=HS^hs[i];
		HS%=h_Q;
	}
	
	HS=HS*h_P;
	HS=HS^hs[sz-1];
	HS=HS*h_B;
	HS=HS%h_Q;

	Hash[u]=HS;
}
