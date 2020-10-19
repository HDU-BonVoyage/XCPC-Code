#include <bits/stdc++.h>
using namespace std;
//mt19937 mrand(chrono::high_resolution_clock::now().time_since_epoch().count());
//int rnd(int x) { return mrand()%x;}
typedef long long ll;
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
void out(int fg){
	if(fg) printf("+\n");
	else printf("-\n");
	fflush(stdout);
	return;
}
int main(){
	int fg=0;
	int cnt=1;
	int val=0;
	while(!fg){
		int x;
		for(int i=1;i<=cnt;i++){
			out(val);	
			scanf("%d",&x);
			if(x==1) break;
		}
		cnt*=3;
		val^=1;
		
		if(x) break;
	}
	int x;
	out(1);
	scanf("%d",&x);
	out(0);
	scanf("%d",&x);
	if(x==1){
		printf("! ugly\n");
		fflush(stdout);
		return 0;
	}
	out(0);
	scanf("%d",&x);
	if(x==1){
		printf("! good\n");
		fflush(stdout);
	}
	else{
		printf("! bad\n");
		fflush(stdout);
	}
	return 0;
}
