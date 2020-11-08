#include <bits/stdc++.h>
using namespace std;
#define ls ch[x][0]
#define rs ch[x][1]
typedef long long ll;
const int N = 3e5+100;
const int INF = 0x3f3f3f3f;
struct LCT{
    int ch[N][2],fa[N],tag[N],siz[N];
    inline void init(int n){
        for(int i=1;i<=n;++i){
            ch[i][0]=ch[i][1]=0;
            fa[i]=0;
            tag[i]=siz[i]=0;
        }
    }
    inline void pushup(int x){
        siz[x]=siz[ls]+siz[rs]+1;
    }
    inline void pushdown(int x){
        if(tag[x]){
            if(ls) swap(ch[ls][0],ch[ls][1]),tag[ls]^=tag[x];
            if(rs) swap(ch[rs][0],ch[rs][1]),tag[rs]^=tag[x];
            tag[x]=0;
        }
    }
    inline int get(int x){
        return x==ch[fa[x]][1];
    }
    inline bool isroot(int x){
        return  ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    inline void rotate(int x){
        int y=fa[x],z=fa[y],k=get(x);
        if(!isroot(y)) ch[z][ch[z][1]==y]=x;
        ch[y][k]=ch[x][k^1]; fa[ch[y][k]]=y;
        ch[x][k^1]=y; fa[y]=x; fa[x]=z;
        pushup(y); pushup(x);
    }
    inline void splay(int x){
        update(x);
        for(int f=fa[x];!isroot(x);f=fa[x]){
            if(!isroot(f)) rotate(get(f)==get(x)?f:x);
            rotate(x);
        }
    }
    inline int access(int x){
        int p;
        for(p=0;x;p=x,x=fa[x]){
            splay(x); ch[x][1]=p; pushup(x);
        }
        return p;
    }
    void update(int x){
        if(!isroot(x)) update(fa[x]);
        pushdown(x);
    }
    inline void makeroot(int x){
        x=access(x); swap(ls,rs);
        tag[x]^=1;
    }
    inline void link(int x,int y){
        makeroot(x); splay(x);
        makeroot(y); splay(y);
        if(fa[x]||fa[y]) return;
        fa[y]=x;
    }
    inline void split(int x,int y){
        makeroot(x); access(y); splay(y);
    }
    inline void cut(int x,int y){
        makeroot(y); access(x); splay(x);
        if(siz[x]!=2||ls!=y) return;
        ls=fa[y]=0;
    }
    inline int find(int x){
        access(x); splay(x);
        while(ls) pushdown(x),x=ls;
        splay(x); return x;
    }
}lct;
struct Node{
	int val,cnt;
	Node(int _val=INF,int _cnt=0){
		val=_val; cnt=_cnt;
	}
	Node operator + (const Node &rhs) const{
		if(val==rhs.val) return Node(val,cnt+rhs.cnt);
		else if(val<rhs.val) return Node(val,cnt);
		else return rhs;
	}
}tr[N<<2]; int lz[N<<2],a[N];
void build(int k,int l,int r){
	lz[k]=0;
	if(l==r){
		tr[k]=Node(l,1);
		return;
	}
	int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
	build(lk,l,mid); build(rk,mid+1,r);
	tr[k]=tr[lk]+tr[rk];
}
Node query(int a,int b,int k,int l,int r){
	if(a>r||b<l) return Node();
	if(a<=l&&r<=b) return tr[k];
	int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
	if(lz[k]){
		lz[lk]+=lz[k]; lz[rk]+=lz[k];
		tr[lk].val+=lz[k]; tr[rk].val+=lz[k];
		lz[k]=0;
	}
	Node ret=query(a,b,lk,l,mid)+query(a,b,rk,mid+1,r);
	tr[k]=tr[lk]+tr[rk];
	return ret;
}
void update(int a,int b,int x,int k,int l,int r){
	if(a>r||b<l) return;
	if(a<=l&&r<=b){
		lz[k]+=x; tr[k].val+=x; return;
	}
	int lk=k<<1,rk=k<<1|1,mid=(l+r)>>1;
	if(lz[k]){
		lz[lk]+=lz[k]; lz[rk]+=lz[k];
		tr[lk].val+=lz[k]; tr[rk].val+=lz[k];
		lz[k]=0;
	}
	update(a,b,x,lk,l,mid); update(a,b,x,rk,mid+1,r);
	tr[k]=tr[lk]+tr[rk];
}
int n,m,cnt[N]; ll ans;
struct Edge{
	int u,v;
	bool operator < (const Edge &e) const{
		if(v!=e.v) return v<e.v;
		return u<e.u;
	}
}e[N];
vector<int> g[N];
int main(){
    scanf("%d %d",&n,&m); lct.init(n);
    for(int i=1;i<=m;++i){
    	scanf("%d %d",&e[i].u,&e[i].v);
    	if(e[i].u>e[i].v) swap(e[i].u,e[i].v);
    }
	sort(e+1,e+1+m); e[m+1].u=e[m+1].v=n+1;
	for(int i=1;i<=m;++i){
		g[e[i].u].push_back(i);
	}
	build(1,1,n);
	for(int i=1,j=1;i<=n;++i){
		while(j<=m){
			if(e[j].u>=i){
				if(lct.find(e[j].u)==lct.find(e[j].v)) break;
				if(cnt[e[j].u]==2||cnt[e[j].v]==2) break;
				lct.link(e[j].u,e[j].v);
				cnt[e[j].u]++; cnt[e[j].v]++;
				update(e[j].v,n,-1,1,1,n);
			}
			++j;
		}
		Node tp=query(i,e[j].v-1,1,1,n);
		if(tp.val==1) ans+=tp.cnt;
		for(auto o:g[i]){
			if(o>=j) continue;
			lct.cut(e[o].u,e[o].v);
			cnt[e[o].u]--; cnt[e[o].v]--;
			update(e[o].v,n,1,1,1,n);
		}
		update(i,n,-1,1,1,n);
	}
	printf("%lld\n",ans);
}
