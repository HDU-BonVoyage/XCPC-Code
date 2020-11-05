#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node{
	ll l,r;
	bool operator < (const node& b)const{
		return r>b.r;
	}
};
priority_queue<node> q;
vector<node> dis[252525*2];
ll a[252525],b[252525];
ll sta[252525];int top;
int main(){
	int n;ll num=0,req=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
	}
	top=0;
	for(int i=1;i<=n;i++){
		if(i>1 && a[i]!=a[i-1]) req++;
		while(top && a[sta[top-1]]>a[i]) top--;
		if(top && a[sta[top-1]]==a[i] && sta[top-1]!=i-1) dis[sta[top-1]].push_back((node){sta[top-1],i-1}),num++;
		sta[top]=i;
		top++;
	}
	top=0;
	for(int i=1;i<=n;i++){
		if(i>1 && b[i]!=b[i-1]) req++;
		while(top && b[sta[top-1]]>b[i]) top--;
		if(top && b[sta[top-1]]==b[i] && sta[top-1]!=i-1) dis[sta[top-1]].push_back((node){sta[top-1],i-1}),num++;
		sta[top]=i;
		top++;
	}
	ll mat=0,cou=0;
	for(node x:dis[0]) q.push(x);
	for(int i=1;i<n;i++){
		while(!q.empty() && q.top().r<i) q.pop();
		for(node x:dis[i]) q.push(x);
		if(!(a[i]!=a[i+1] && b[i]!=b[i+1])) continue;
		cou++;
		if(!q.empty()){
			mat++;
			q.pop();
		}
	}
	ll ans=num+cou-mat;
	printf("%lld\n",req-ans);
	return 0;
}
