#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const double eps=1e-6;

int dcmp(double x){if(fabs(x)<eps) return 0; return (x<0)?-1:1;}

struct Point
{
    double x,y;
    Point(double _x=0,double _y=0):x(_x),y(_y){};
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

///有向直线
struct Line
{
    Point p;
    Point v;
    double ang;
    Line(Point _p,Point _v):p(_p),v(_v){ang=atan2(v.y,v.x);}
    Point point(double a) {return p+(v*a);}
    bool operator<(const Line& L)const
        {
            return ang<L.ang;
        }
};

///直线平移距离d
Line LineTransHor(Line l,int d)
{
    Point vl=Verunit(l.v);
    Point p1=l.p+vl*d,p2=l.p-vl*d;
    Line ll=Line(p1,l.v);
    return ll;
}

///直线交点（假设存在）
Point GetLineIntersection(Line a,Line b)
{
    return GetLineIntersection(a.p,a.v,b.p,b.v);
}

///点p在有向直线的左边
bool OnLeft(const Line& L,const Point& p)
{
    return Cross(L.v,p-L.p)>=0;
}

///圆
const double pi=acos(-1.0);

struct Circle
{
    Point c;
    double r;
    Circle(Point _c=0,double _r=0):c(_c),r(_r){}
    Point point(double a)///根据圆心角算圆上的点
    {
        return Point(c.x+cos(a)*r,c.y+sin(a)*r);
    }
};

///a点到b点（逆时针）在圆上的圆弧长度
double D(Point a,Point b,Circle C)
{
    double ang1,ang2;
    Point v1,v2;
    v1=a-C.c; v2=b-C.c;
    ang1=atan2(v1.y,v1.x);
    ang2=atan2(v2.y,v2.x);
    if(ang2<ang1) ang2+=2*pi;
    return C.r*(ang2-ang1);
}

///直线与圆交点 返回交点个数
int getLineCircleIntersection(Line L,Circle C,double& t1,double& t2,vector<Point>& sol)
{
    double a=L.v.x,b=L.p.x-C.c.x,c=L.v.y,d=L.p.y-C.c.y;
    double e=a*a+c*c,f=2*(a*b+c*d),g=b*b+d*d-C.r*C.r;
    double delta=f*f-4.*e*g;
    if(dcmp(delta)<0) return 0;//相离
    if(dcmp(delta)==0)//相切
    {
        t1=t2=-f/(2.*e); sol.push_back(L.point(t1));
        return 1;
    }
    //相切
    t1=(-f-sqrt(delta))/(2.*e); sol.push_back(L.point(t1));
    t2=(-f+sqrt(delta))/(2.*e); sol.push_back(L.point(t2));
    return 2;
}


///圆与圆交点 返回交点个数
int getCircleCircleIntersection(Circle C1,Circle C2,vector<Point>& Sol)
{
    double d=Length(C1.c-C2.c);
    if(dcmp(d)==0)
    {
        if(dcmp(C1.r-C2.r)==0) return -1;//重合
        return 0;
    }
    if(dcmp(C1.r+C2.r-d)<0) return 0;
    if(dcmp(fabs(C1.r-C2.r)-d)>0) return 0;

    double a=Angle(C2.c-C1.c);
    double da=acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));

    Point p1=C1.point(a-da),p2=C1.point(a+da);

    Sol.push_back(p1);
    if(p1==p2) return 1;

    Sol.push_back(p2);
    return 2;
}

///P到圆的切线 v[] 储存切线向量
int getTangents(Point p,Circle C,Point* v)
{
    Point u=C.c-p;
    double dist=Length(u);
    if(dist<C.r) return 0;
    else if(dcmp(dist-C.r)==0)
    {
        ///p在圆上只有一条切线
        v[0]=Rotate(u,pi/2);
        return 1;
    }
    else
    {
        double ang=asin(C.r/dist);
        v[0]=Rotate(u,-ang);
        v[1]=Rotate(u,ang);
        return 2;
    }
}

//两圆公切线 a,b  公切线再 圆 A B 上的切点
int getTengents(Circle A,Circle B,Point* a,Point* b)
{
    int cnt=0;
    if(A.r<B.r) { swap(A,B); swap(a,b); }
    int d2=(A.c.x-B.c.x)*(A.c.x-B.c.x)+(A.c.y-B.c.y)*(A.c.y-B.c.y);
    int rdiff=A.r-B.r;
    int rsum=A.r+B.r;
    if(d2<rdiff*rdiff) return 0;///内含

    double base=atan2(B.c.y-A.c.y,B.c.x-A.c.x);
    if(d2==0&&A.r==B.r) return -1; ///无穷多
    if(d2==rdiff*rdiff)//内切 1条
    {
        a[cnt]=A.point(base); b[cnt]=B.point(base); cnt++;
        return 1;
    }
    ///外切
    double ang=acos((A.r-B.r)/sqrt(d2));
    a[cnt]=A.point(base+ang); b[cnt]=B.point(base+ang); cnt++;
    a[cnt]=A.point(base-ang); b[cnt]=B.point(base-ang); cnt++;
    if(d2==rsum*rsum)// one
    {
        a[cnt]=A.point(base); b[cnt]=B.point(pi+base); cnt++;
    }
    else if(d2>rsum*rsum)// two
    {
        double ang=acos((A.r-B.r)/sqrt(d2));
        a[cnt]=A.point(base+ang); b[cnt]=B.point(pi+base+ang); cnt++;
        a[cnt]=A.point(base-ang); b[cnt]=B.point(pi+base-ang); cnt++;
    }
    return cnt;
}

///三角形外接圆
Circle CircumscribedCircle(Point p1,Point p2,Point p3)
{
    double Bx=p2.x-p1.x,By=p2.y-p1.y;
    double Cx=p3.x-p1.x,Cy=p3.y-p1.y;
    double D=2*(Bx*Cy-By*Cx);
    double cx=(Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D+p1.x;
    double cy=(Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D+p1.y;
    Point p=Point(cx,cy);
    return Circle(p,Length(p1-p));
}

///三角形内切圆
Circle InscribedCircle(Point p1,Point p2,Point p3)
{
    double a=Length(p2-p3);
    double b=Length(p3-p1);
    double c=Length(p1-p2);
    Point p=(p1*a+p2*b+p3*c)/(a+b+c);
    return Circle(p,DistanceToLine(p,p1,p2));
}

double RtoDegree(double x) {return x/pi*180.;}

char op[200];
double a[10];
Point v[10];
double degree[10];
vector<Point> sol;


int main()
{
    while(scanf("%s",op)!=EOF)
    {
        if(strcmp(op,"CircumscribedCircle")==0)
        {
            for(int i=0;i<6;i++) scanf("%lf",a+i);
            Circle C=CircumscribedCircle(Point(a[0],a[1]),Point(a[2],a[3]),Point(a[4],a[5]));
            printf("(%.6lf,%.6lf,%.6lf)\n",C.c.x,C.c.y,C.r);
        }
        else if(strcmp(op,"InscribedCircle")==0)
        {
            for(int i=0;i<6;i++) scanf("%lf",a+i);
            Circle C=InscribedCircle(Point(a[0],a[1]),Point(a[2],a[3]),Point(a[4],a[5]));
            printf("(%.6lf,%.6lf,%.6lf)\n",C.c.x,C.c.y,C.r);
        }
        else if(strcmp(op,"TangentLineThroughPoint")==0)
        {
            for(int i=0;i<5;i++) scanf("%lf",a+i);
            int sz=getTangents(Point(a[3],a[4]),Circle(Point(a[0],a[1]),a[2]),v);
            for(int i=0;i<sz;i++)
            {
                double de=RtoDegree(Angle(v[i]));
                if(dcmp(de)<0) de=180.+de;
                else while(dcmp(de-180.)>=0) de-=180.;
                degree[i]=de;
            }
            sort(degree,degree+sz);
            putchar('[');if(sz==0) putchar(']');
            for(int i=0;i<sz;i++) printf("%.6lf%c",degree[i],(i!=sz-1)?',':']');
            putchar(10);
        }
        else if(strcmp(op,"CircleThroughAPointAndTangentToALineWithRadius")==0)
        {
            for(int i=0;i<7;i++) scanf("%lf",a+i);
            Point A=Point(a[2],a[3]),B=Point(a[4],a[5]);
            Circle C(Point(a[0],a[1]),a[6]);

            Point normal=Verunit(B-A);
            normal=normal/Length(normal)*a[6];

            Point ta=A+normal,tb=B+normal;
            Line l1=Line(ta,tb-ta);
            ta=A-normal,tb=B-normal;
            Line l2=Line(ta,tb-ta);

            sol.clear();
            double t1,t2;
            int aa=getLineCircleIntersection(l1,C,t1,t2,sol);
            int bb=getLineCircleIntersection(l2,C,t1,t2,sol);
            sort(sol.begin(),sol.end());

            putchar('[');
            for(int i=0,sz=sol.size();i<sz;i++)
            {
                if(i) putchar(',');
                printf("(%.6lf,%.6lf)",sol[i].x,sol[i].y);
            }
            putchar(']'); putchar(10);
        }
        else if(strcmp(op,"CircleTangentToTwoLinesWithRadius")==0)
        {
            for(int i=0;i<9;i++) scanf("%lf",a+i);
            Line LA=Line(Point(a[0],a[1]),Point(a[2],a[3])-Point(a[0],a[1]));
            Line LB=Line(Point(a[4],a[5]),Point(a[6],a[7])-Point(a[4],a[5]));
            Line la1=LineTransHor(LA,a[8]),la2=LineTransHor(LA,-a[8]);
            Line lb1=LineTransHor(LB,a[8]),lb2=LineTransHor(LB,-a[8]);

            sol.clear();
            sol.push_back(GetLineIntersection(la1,lb1));
            sol.push_back(GetLineIntersection(la1,lb2));
            sol.push_back(GetLineIntersection(la2,lb1));
            sol.push_back(GetLineIntersection(la2,lb2));
            sort(sol.begin(),sol.end());

            putchar('[');
            for(int i=0,sz=sol.size();i<sz;i++)
            {
                if(i) putchar(',');
                printf("(%.6lf,%.6lf)",sol[i].x,sol[i].y);
            }
            putchar(']'); putchar(10);

        }
        else if(strcmp(op,"CircleTangentToTwoDisjointCirclesWithRadius")==0)
        {
            for(int i=0;i<7;i++) scanf("%lf",a+i);
            Circle C1=Circle(Point(a[0],a[1]),a[2]+a[6]);
            Circle C2=Circle(Point(a[3],a[4]),a[5]+a[6]);
            sol.clear();
            getCircleCircleIntersection(C1,C2,sol);
            sort(sol.begin(),sol.end());
            putchar('[');
            for(int i=0,sz=sol.size();i<sz;i++)
            {
                if(i) putchar(',');
                printf("(%.6lf,%.6lf)",sol[i].x,sol[i].y);
            }
            putchar(']'); putchar(10);
        }
    }
    return 0;
}
