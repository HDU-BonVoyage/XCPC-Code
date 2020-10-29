#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double LD;
struct node{
	LD x,y;
};
node a[100100];
LD vx,vy;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&a[i].x,&a[i].y);
	}
	LD h=a[n].y-a[1].y,d=a[n].x-a[1].x;
	vx=sqrt(5*d*d/sqrt(h*h+d*d));
	vy=sqrt(5*h*h/sqrt(h*h+d*d)+5*sqrt(h*h+d*d)+10*h);
	for(int i=2;i<n;i++){
		LD t=(a[i].x-a[1].x)/vx;
		LD cy=-5*t*t+vy*t;
		if(cy+a[1].y<a[i].y){
			LD x1=a[i].x-a[1].x,x2=a[n].x-a[1].x,y1=a[i].y-a[1].y,y2=a[n].y-a[1].y;
			if((5*x2*x2-5*x1*x2)/(x2/x1*y1-y2)<0) assert(0);
			vx=sqrt((5*x2*x2-5*x1*x2)/(x2/x1*y1-y2));
			vy=(5*x1*x1+y1*vx*vx)/(x1*vx);
		}
	}/*
	for(int i=1;i<=n;i++){
		LD t=(a[i].x-a[1].x)/vx;
		LD cy=-5*t*t+vy*t;
		printf("%d:%f %f\n",i,t,cy+a[1].y);
	}*/
	printf("%.10f\n",sqrt(vx*vx+vy*vy));
}
/*
6
1 2
4 4
5 0
6 3
8 4
11 2
*/
