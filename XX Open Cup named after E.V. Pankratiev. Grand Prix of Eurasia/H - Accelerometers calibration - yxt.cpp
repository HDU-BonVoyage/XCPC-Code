#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double LD;
const LD PI=acos(-1.0);
//const LD eps=1e-4;
LD a1[10],a2[10],d1,d2,alp1,alp2,p1,p2;
LD arccos(LD x){
	LD lb=0,ub=PI;
	LD ans;
	for(int i=0;i<=60;i++){
		ans=(lb+ub)/2.0;
		if(cos(ans)>x){
			lb=ans;
		}
		else ub=ans;
	}
	return ans;
}
long double modi(long double ag){
	while(ag<0) ag+=360;
	while(ag>360) ag-=360;
	return ag;
}
int main(){
	for(int i=1;i<=4;i++){
		scanf("%Lf%Lf",&a1[i],&a2[i]);
	}
	d1=(a1[1]+a1[3])/2.0;d2=(a2[1]+a2[3])/2.0;
	for(int i=1;i<=4;i++){
		a1[i]-=d1;a2[i]-=d2;
	}
	p1=sqrt(a1[1]*a1[1]+a1[2]*a1[2]);p2=sqrt(a2[1]*a2[1]+a2[2]*a2[2]);
	for(int i=1;i<=4;i++){
		a1[i]/=p1;a2[i]/=p2;
	}
	alp1=arccos(a1[1])*180/PI-90;
	alp2=arccos(a2[4])*180/PI-90;
	//alp1=180*alp1/PI;alp2=180*alp2/PI;
	int T;
	scanf("%d",&T);
	while(T--){
		LD x,y;
		scanf("%Lf%Lf",&x,&y);
		x-=d1;x/=p1;y-=d2;y/=p2;
		long double beta1=180*arccos(x)/PI,beta2=180*arccos(y)/PI;
		long double rbeta1=360-beta1-alp1,rbeta2=360-beta2-alp2;
		beta1-=alp1;beta2-=alp2;
		modi(beta1);modi(rbeta1);modi(beta2);modi(rbeta2);
		long double r[5];
		r[1]=abs(modi(beta2-beta1)-90);r[2]=abs(modi(rbeta2-beta1)-90);r[3]=abs(modi(rbeta2-rbeta1)-90),r[4]=abs(modi(beta2-rbeta1)-90);
		long double mii=min(r[1],min(r[2],min(r[3],r[4])));
		if(min(r[1],r[2])<min(r[3],r[4])){
			printf("%.15Lf\n",modi(beta1-90));
		}
		else{
			printf("%.15Lf\n",modi(rbeta1-90));
		}
		//else assert(0);
		/*
		if(abs(modi(beta2-beta1)-90)<eps){
			printf("%.9f\n",modi(beta1-90));
		}
		else if(abs(modi(rbeta2-beta1)-90)<eps){
			printf("%.9f\n",modi(beta1-90));
		}
		else if(abs(modi(rbeta2-rbeta1)-90)<eps){
			printf("%.9f\n",modi(rbeta1-90));
		}
		else if(abs(modi(beta2-rbeta1)-90)<eps){
			printf("%.9f\n",modi(rbeta1-90));
		}
		else assert(0);
		*/
	}
}
