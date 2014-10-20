/**计算几何
基本1:与点有关的操作
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

int main()
{
    return 0;
}
