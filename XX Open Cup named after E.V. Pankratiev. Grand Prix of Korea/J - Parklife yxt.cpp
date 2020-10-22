#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> G[300300];
struct node{
	int x,y;ll w;int id;
	bool operator < (const node& b)const{
		if(x!=b.x) return x<b.x;
		else return y>b.y;
	}
};
node a[300300];
node sta[300300];int top=0;
priority_queue<ll> q[300300];
void dfs(int pos){
	int ma=-1,pt=-1;
	for(int i:G[pos]){
		dfs(i);
		if((int)q[i].size()>ma){
			ma=(int)q[i].size();
			pt=i;
		}
	}
	if(pt!=-1){
		q[pos].swap(q[pt]);
		for(int i:G[pos]){
			if(i==pt) continue;
			vector<ll> v;
			while(!q[i].empty()){
				ll x=q[i].top();q[i].pop();
				ll y=q[pos].top();q[pos].pop();
				y+=x;
				v.push_back(y);	
			}
			for(ll tt:v){
				q[pos].push(tt);
			}
		}
	} 
	q[pos].push(a[pos].w);
	return;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int f,t;ll w;
		scanf("%d%d%lld",&f,&t,&w);
		a[i]={f,t,w,0};
	}
	a[n+1]={1,1000001,0,0};
	sort(a+1,a+2+n);
	top=0;
	for(int i=1;i<=n+1;i++){
		a[i].id=i;
		while(top && a[i].x>=sta[top-1].y){
			top--;
		}
		if(top){
			G[sta[top-1].id].push_back(a[i].id);
		}
		sta[top++]=a[i];
	}
	dfs(1);
	ll ans=0;
	for(int i=1;i<=n;i++){
		if(q[1].size()){
			ans+=q[1].top();
			q[1].pop();
		}
		if(i-1) printf(" ");
		printf("%lld",ans);
	}
	printf("\n");
	return 0;
}
