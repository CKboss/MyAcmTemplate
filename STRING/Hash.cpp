
/*简单的字符串hash*/

ull xp[maxn],hash[maxn];

void init()
{
	xp[0]=1;
	for(int i=1;i<maxn;i++)
		xp[i]=xp[i-1]*175;
}

ull get_hash(int i,int L)
{
	return hash[i]-hash[i+L]*xp[L];
}

scanf("%s",str);
int n=strlen(str);
hash[n]=0;
for(int i=n-1;i>=0;i--)
{
	hash[i]=hash[i+1]*175+(str[i]-'a'+1);
}
