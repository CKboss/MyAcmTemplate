// 点集凸包
// 如果不希望在凸包的边上有输入点,把两个 <= 改成 <
// 注意:输入点集会被修改
vector<Point> CovexHull(vector<Point>& p)
{
  sort(p.begin(),p.end());
  p.erase(unique(p.begin(),p.end()),p.end());
  int n=p.size();
  int m=0;
  vector<Point> ch(n+1);
  for(int i=0;i<n;i++)
    {
      while(m>1&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
      ch[m++]=p[i];
    }
  int k=m;
  for(int i=n-2;i>=0;i--)
    {
      while(m>k&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
      ch[m++]=p[i];
    }
  if(n>1) m--;
  ch.resize(m);
  return ch;
}

/// n^2 旋转卡壳求凸包内接三角形的面积
double Rotating_Calipers(vector<Point>& p,int n)  
{  
    double ans=0;  
    for(int i=0;i<n;i++)  
    {  
        int j=(i+1)%n;  
        int k=(j+1)%n;  
        while(j!=i&&k!=i)  
        {  
            ans=max(ans,Area2(p[i],p[j],p[k]));  
            while(Cross(p[i]-p[j],p[(k+1)%n]-p[k])<0)  
                k=(k+1)%n;  
            j=(j+1)%n;  
        }  
    }  
    return ans;  
}  
