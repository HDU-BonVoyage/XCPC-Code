#include <bits/stdc++.h>
using namespace std;
const int N = 55;
const int M = 605;
double eps = 1e-8;
double INF = 1e12;
struct Point{
	double x,y;
	Point(){x=y=0;}
	Point(double _x,double _y){
		x=_x; y=_y;
	}
	Point operator + (Point p){
		return Point(x+p.x,y+p.y);
	}
	Point operator - (Point p){
		return Point(x-p.x,y-p.y);
	}
	Point operator * (double r){
		return Point(x*r,y*r);
	}
	Point operator / (double r){
		return Point(x/r,y/r);
	}
	double length(){
		return sqrt(x*x+y*y);
	}
};
int sgn(double x){
	if(fabs(x)<eps) return 0;
	else return x<0?-1:1;
}
double cross(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}
bool in(Point a,Point b,Point c){
	return c.x>=min(a.x,b.x)&&c.x<=max(a.x,b.x)&&c.y>=min(a.y,b.y)&&c.y<=max(a.y,b.y);
}
double insec(Point a,Point b,Point p,Point q){
	double U=cross(p-a,q-p);
	double D=cross(b-a,q-p);
	if(sgn(D)==0) return INF;
	Point o=a+(b-a)*(U/D);
	if(!in(a,o,b)||!in(p,q,o)) return INF;
	return ((b-a)*(U/D)-(b-a)).length();
}
bool cmpxy(Point a,Point b){
	if(sgn(a.x-b.x)) return a.x<b.x;
	else return a.y<b.y;
}
int convex_hull(Point *v,int n,Point *c){
	sort(v,v+n,cmpxy); int m=0;
	for(int i=0;i<n;++i){
		while(m>1&&cross(c[m-1]-c[m-2],v[i]-c[m-2])<=0) --m;
		c[m++]=v[i];
	}
	int k=m;
	for(int i=n-2;i>=0;--i){
		while(m>k&&cross(c[m-1]-c[m-2],v[i]-c[m-2])<=0) --m;
		c[m++]=v[i];
	}
	if(n>1) --m;
	return m;
}
int n,m[N],k; int z;
Point p[N][M],c[N][M],fl,fr,bl,br;
double ans[N];
int main(){
	scanf("%d",&k);
	scanf("%lf %lf",&fr.x,&fr.y);
	scanf("%lf %lf",&fl.x,&fl.y);
	scanf("%lf %lf",&bl.x,&bl.y);
	scanf("%lf %lf",&br.x,&br.y);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&m[i]); ans[i]=INF;
		for(int j=0;j<m[i];++j){
			scanf("%lf %lf",&p[i][j].x,&p[i][j].y);
			scanf("%d",&z);
			if(z) --j,--m[i];
		}
		m[i]=convex_hull(p[i],m[i],c[i]);
		for(int j=0;j<m[i];++j){
			ans[i]=min(ans[i],insec(bl,fl,c[i][j],c[i][(j+1)%m[i]]));
			ans[i]=min(ans[i],insec(br,fr,c[i][j],c[i][(j+1)%m[i]]));
		}
	}
	ans[n+1]=INF; sort(ans+1,ans+1+n);
	if(k>=n||ans[k+1]==INF) printf("oo\n");
	else printf("%.8lf\n",ans[k+1]);
	return 0;
}
