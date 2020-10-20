#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
ll abs(ll x){
	return x>0?x:-x;
}
ll gcd(ll a,ll b){
	return (b==0)?a:gcd(b,a%b);
}
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;y=0;
		return a;
	}
	ll ret=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return ret;
}
ll a1,b1,g,ok;
void ins(ll x,ll y){
	if(x==0){
		if(g==0) g=abs(y);
		else if(y) g=gcd(g,abs(y));
	}
	else{
		ll a=0,b=0;
		if(x<0){
			x*=-1;y*=-1;
		}
		ll na1=a1?exgcd(x,a1,a,b):x;
		ll nb1=a1?a*y+b*b1:y;
		if(a1){
			ll ty=y-x/na1*nb1;
			ty=abs(ty);
			if(g==0) g=ty;
			else if(ty) g=gcd(g,ty);
			ty=b1-a1/na1*nb1;
			ty=abs(ty);
			if(g==0) g=ty;
			else if(ty) g=gcd(g,ty);
		}
		a1=na1;b1=nb1;
		if(g) b1%=g;
	}
}
bool que(ll qx,ll qy){
	if((a1==0 && qx)){
		return 0;
	}
	if(a1==0 && qx==0){
		if(b1==0 && g==0){
			return qy==0;
		}
		else if(b1==0){
			return qy%g==0;
		}
		else if(g==0){
			return qy%b1==0;
		}
		ll gg=gcd(b1,g);
		if(gg==0 && qy==0) return 1;
		else if(gg==0) return 0;
		return qy%gg==0;
	}
	if(qx%a1) return 0;
	ll t=qx/a1;
	qy=qy-t*b1;
	if(g==0 &&  qy==0) return 1;
	else if(g==0) return 0;
	if(abs(qy)%g==0) return 1;
	else return 0;
}
char s[1000];
void read(ll& x){
	scanf("%s",s);
	//printf("%s\n",s);
	x=0;
	for(int i=0;s[i];i++){
		x*=10;
		x+=s[i]-'0';
	}
}
void wri(ll x){
	vector<int> v;
	while(x){
		v.push_back(x%10);
		x/=10;
	}
	if(v.size()==0) v.push_back(0);
	for(int i=(int)v.size()-1;i>=0;i--){
		printf("%d",v[i]);
	}
}
int main(){
	int T;
	scanf("%d",&T);int cas=0;
	while(T--){
		cas++;
		int q;
		scanf("%d",&q);
		ll ans=0;
		ok=1;a1=b1=g=0;
		while(q--){
			int typ;
			scanf("%d",&typ);
			if(typ==2){
				ll x,y,w;
				read(x);read(y);
				read(w);
				if(x==0 && y==0){
					ans+=w;
				}
				else{
					if(que(x,y)){
						ans+=w;
					}
				}
			}
			else{
				ll x,y;
				read(x);read(y);
				ins(x,y);
			}
		}
		printf("Case #%d: ",cas);
		wri(ans);
		putchar('\n');
	}
	return 0;
}
/*
1
3
1 2 1
1 5 3
2 7 4 1
*/
