

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
