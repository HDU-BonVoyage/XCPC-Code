#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5+10;
struct Node{
	int l,r,v;
	bool operator < (const Node &rhs) const{
		if(l!=rhs.l) return l<rhs.l;
		else return r>rhs.r;
	}
}a[N]; int n; ll ans;
priority_queue<ll> q[N];
stack<int> st;
vector<int> g[N];
vector<ll> tp;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d %d %d",&a[i].l,&a[i].r,&a[i].v);
		--a[i].r;
	}
	++n; a[n].l=-1e7,a[n].r=1e7,a[n].v=0;
	sort(a+1,a+1+n); st.push(1); 
	for(int i=2;i<=n;++i){
		while(!st.empty()&&a[st.top()].r<a[i].l) st.pop();
		g[st.top()].push_back(i); st.push(i);
	}
	for(int u=n,o;u>=1;--u){
		o=-1;
		for(auto v:g[u]){
			if(o==-1){
				o=v; continue;
			}
			if(q[o].size()<q[v].size()) swap(o,v);
			tp.clear();
			while(!q[o].empty()&&!q[v].empty()){
				tp.push_back(q[o].top()+q[v].top());
				q[o].pop(); q[v].pop();
			}
			for(auto w:tp) q[o].push(w);
		}
		if(o!=-1) q[u].swap(q[o]); q[u].push(a[u].v);
	}
	for(int i=1;i<n;++i){
		if(!q[1].empty()){
			ans+=q[1].top();
			q[1].pop();
		}
		printf("%lld ",ans);
	}
}
