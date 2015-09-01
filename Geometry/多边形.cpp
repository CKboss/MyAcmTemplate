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


/// 判断点是否在多边形内
/// 凸凹多边形均可

bool OnSegment(Point p,Point a,Point b)
{
	if(dcmp(Cross(p-a,p-b)))return 0;
    return dcmp(a.x-p.x)*dcmp(b.x-p.x)<=0&&dcmp(a.y-p.y)*dcmp(b.y-p.y)<=0;
}

bool isInPolygon(vector<Point>& poly,int n,Point p)
{
	int wn=0;
	for(int i=0;i<n;i++)
	{
		//// 在边界上
		if(OnSegment(p,poly[i],poly[(i+1)%n])==true) return -1; /// onside
		int k=dcmp(Cross(poly[(i+1)%n]-poly[i],p-poly[i]));
		int d1=dcmp(poly[i].y-p.y);
		int d2=dcmp(poly[(i+1)%n].y-p.y);
		if(k>0&&d1<=0&&d2>0) wn++;
		if(k<0&&d2<=0&&d1>0) wn--;
	}
	if(wn!=0) return 1; /// inside
	return 0; /// outside;
}
