

void pack01(int cost,int weight)
{
	for(int i=V;i>=cost;i--)
		dp[i]=max(dp[i-cost]+weight,dp[i]);
}

void packCM(int cost,int weight)
{
	for(int i=cost;i<=V;i++)
		dp[i]=max(dp[i-cost]+weight,dp[i]);
}

void packMU(int cost,int weight,int num)
{
	if(num*cost>=V)
	{
		packCM(cost,weight);
		return ;
	}
	int k=1;
	while(k<num)
	{
		pack01(cost*k,weight*k);
		num-=k;
		k*=2;
	}
	pack01(cost*num,weight*num);
}

///分组背包 c组背包,容量为k,每组物品从mn~mx
for(int i=1;i<=c;i++) /// 每一组背包
{
	for(int v=k;v>=0;v--) /// 背包容量
	{
		dp[i][v]=max(dp[i][v],dp[i-1][v]);
		for(int j=mn[i];j<=mx[i]&&j<=v;j++) /// 第i组的每一个物品
		{
			dp[i][v]=max(dp[i][v],dp[i-1][v-j]+j);
		}
	}
}

