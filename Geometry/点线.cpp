/**计算几何
基本1:与点线有关的操作
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const double eps = 1e-8;

int dcmp(double x){if(fabs(x)<eps) return 0; return (x<0)?-1:1;}

struct Point
{
    double x,y;
    Point(double _x,double _y):x(_x),y(_y){};
};

Point operator+(Point A,Point B) {return Point(A.x+B.x,A.y+B.y);}
Point operator-(Point A,Point B) {return Point(A.x-B.x,A.y-B.y);}
Point operator*(Point A,double p) {return Point(A.x*p,A.y*p);}
Point operator/(Point A,double p) {return Point(A.x/p,A.y/p);}

bool operator<(const Point&a,const Point&b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}

bool operator==(const Point&a,const Point&b){return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}

double Dot(Point A,Point B) {return A.x*B.x+A.y*B.y;}
double Length(Point A) {return sqrt(Dot(A,A));}
double Angle(Point A,Point B) {return acos(Dot(A,B)/Length(A)/Length(B));}
double Angle(Point v) {return atan2(v.y,v.x);}
double Cross(Point A,Point B) {return A.x*B.y-A.y*B.x;}

/**Cross
    P*Q > 0 P在Q的顺时针方向
    P*Q < 0 P在Q的逆时针方向
    P*Q = 0 PQ共线
*/

Point Horunit(Point x) {return x/Length(x);}///单位向量
Point Verunit(Point x) {return Point(-x.y,x.x)/Length(x);}///单位法向量

Point Rotate(Point A,double rad)///逆时针旋转
{
    return Point(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}

double Area2(const Point A,const Point B,const Point C)
{
    return Cross(B-A,C-A);
}

/// 过两点p1, p2的直线一般方程ax+by+c=0  (x2-x1)(y-y1) = (y2-y1)(x-x1)
void getLineGeneralEquation(const Point& p1, const Point& p2, double& a, double&b, double &c)
{
    a = p2.y-p1.y;
    b = p1.x-p2.x;
    c = -a*p1.x - b*p1.y;
}

///P+t*v Q+w*t的焦点
Point GetLineIntersection(Point P,Point v,Point Q,Point w)
{
    Point u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}


///点到直线距离
double DistanceToLine(Point P,Point A,Point B)
{
    Point v1=B-A,v2=P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}

///点到线段距离
double DistanceToSegment(Point P,Point A,Point B)
{
    if(A==B) return Length(P-A);
    Point v1=B-A,v2=P-A,v3=P-B;
    if(dcmp(Dot(v1,v2))<0) return Length(v2);
    else if(dcmp(Dot(v1,v3))>0) return Length(v3);
    else return fabs(Cross(v1,v2))/Length(v1);
}

///点到直线投影
Point GetLineProjection(Point P,Point A,Point B)
{
    Point v=B-A;
    return A+v*(Dot(v,P-A)/Dot(v,v));
}

///判断规范相交
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2)
{
    double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);
    double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);

    return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}

///一个点是否在直线端点上
bool OnSegment(Point p,Point a1,Point a2)
{
    return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<0;
}

///多边形有向面积
double PolygonArea(Point* p,int n)
{
    double area=0;
    for(int i=1;i<n-1;i++)
        area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

int main()
{
    return 0;
}
