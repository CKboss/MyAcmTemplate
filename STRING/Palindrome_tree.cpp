
const int maxn=330000;
const int C=30;

int next[maxn][C];
int fail[maxn];
int cnt[maxn]; // 本质不同的回文串出现的次数(count后)
int num[maxn]; // 表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
int len[maxn]; // 节点i表示的回文串的长度
int s[maxn]; // 节点i存的字符
int last; // 新加一个字母后所形成的最长回文串表示的节点
int p; // 添加节点的个数 p-2为本质不同的回文串个数
int n; // 添加字符的个数

int newnode(int x)
{
	for(int i=0;i<C;i++) next[p][i]=0;
	cnt[p]=0; num[p]=0; len[p]=x;
	return p++;
}

void init()
{
	p=0;
	newnode(0); newnode(-1);
	last=0; n=0;
	s[0]=-1; fail[0]=1;
}

int get_fail(int x)
{
	while(s[n-len[x]-1]!=s[n]) x=fail[x];
	return x;
}

void add(int c)
{
	c-='a';
	s[++n]=c;
	int cur=get_fail(last);
	if(!next[cur][c])
	{
		int now=newnode(len[cur]+2);
		fail[now]=next[get_fail(fail[cur])][c];
		next[cur][c]=now;
		num[now]=num[fail[now]]+1;
	}
	last=next[cur][c];
	cnt[last]++;
}

void count()
{
	for(int i=p-1;i>=0;i--) cnt[fail[i]]+=cnt[i];
}
