#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cassert>
#include <utility>
#include <set>
#define pii pair<__int128,__int128>
#define mp make_pair
#define lch (n<<1)
#define rch ((n<<1)+1)
#define fr first
#define sc second
using namespace std;
const long long inf=1e18+10;
const int mo=1e9+7;
const int maxn=3e5+10;
int n,root=1,id=1,topt,v[maxn],p[maxn],ppp[maxn],x0;
__int128 num[maxn],tag[maxn];
struct da{int l,r;long long add,mul,sum;}a[maxn<<2];
set<pii>s[40];
map<__int128,int>idd[40];
int lowbit(int x){return x&(-x);}
void add(int x,int k){while (x<=n+1) {v[x]+=k; x+=lowbit(x);}}
int qury(int x){int sum=0; while (x) {sum+=v[x]; x-=lowbit(x);} return sum;}
void build_tree(int n,int l,int r)
{
	a[n].l=l; a[n].r=r; a[n].add=0; a[n].mul=1; 
	if (l==r) return;
	int mid=(l+r)>>1;
	build_tree(lch,l,mid); build_tree(rch,mid+1,r);
}
void push_down(int n)
{
	if (a[n].mul!=1)
	{
		a[lch].sum=a[lch].sum*a[n].mul%mo;
		a[lch].add=a[lch].add*a[n].mul%mo;
		a[lch].mul=a[lch].mul*a[n].mul%mo;
		a[rch].sum=a[rch].sum*a[n].mul%mo;
		a[rch].add=a[rch].add*a[n].mul%mo;
		a[rch].mul=a[rch].mul*a[n].mul%mo;
		a[n].mul=1;
	}
	if (a[n].add!=0)
	{
		a[lch].sum=(a[lch].sum+1ll*(a[lch].r-a[lch].l+1)*a[n].add)%mo;
		a[lch].add=(a[lch].add+a[n].add)%mo;
		a[rch].sum=(a[rch].sum+1ll*(a[rch].r-a[rch].l+1)*a[n].add)%mo;
		a[rch].add=(a[rch].add+a[n].add)%mo;
		a[n].add=0;
	}
}
void tree_add(int n,int L,int R,int l,int r,int k)
{
	if (L==l && R==r)
	{
		a[n].sum=(a[n].sum+1ll*(a[n].r-a[n].l+1)*k)%mo;
		a[n].add=(a[n].add+k)%mo; return;
	}
	int mid=(L+R)>>1; push_down(n);
	if (r<=mid) tree_add(lch,L,mid,l,r,k);
	else if (l>=mid+1) tree_add(rch,mid+1,R,l,r,k);
	else tree_add(lch,L,mid,l,mid,k),tree_add(rch,mid+1,R,mid+1,r,k);
}
void tree_mul(int n,int L,int R,int l,int r,int k)
{
	if (L==l && R==r)
	{
		a[n].sum=a[n].sum*k%mo;
		a[n].add=a[n].add*k%mo;
		a[n].mul=a[n].mul*k%mo;
		return;
	}
	int mid=(L+R)>>1; push_down(n);
	if (r<=mid) tree_mul(lch,L,mid,l,r,k);
	else if (l>=mid+1) tree_mul(rch,mid+1,R,l,r,k);
	else tree_mul(lch,L,mid,l,mid,k),tree_mul(rch,mid+1,R,mid+1,r,k);
}
int qury(int n,int l,int r,int lc)
{
	if (l==r) return a[n].sum;
	int mid=(l+r)>>1; push_down(n);
	if (lc<=mid) return qury(lch,l,mid,lc);else return qury(rch,mid+1,r,lc);
}
int main()
{
	scanf("%d",&n); build_tree(root,1,n+1);
	p[0]=1; for (int i=1;i<maxn;i++) p[i]=p[i-1]*2%mo;
	ppp[0]=1; for (int i=1;i<=30;i++) ppp[i]=ppp[i-1]*2;
	tree_add(root,1,n+1,id,id,0); num[id]=inf; s[0].insert(mp(0,0)); idd[0][0]=id; x0=id;
	for (int _=1;_<=n;_++)
	{
		int op; scanf("%d",&op);
		if (op==1)
		{
			int k; scanf("%d",&k); id++;
			if (k>=1)
			{
				//for qury 2
				tree_add(root,1,n+1,1,id-1,k);
				tree_add(root,1,n+1,id,id,0); num[id]=k;
				//for qury 3
				for (int i=0;i<=30;i++) tag[i]+=k;
				s[0].insert(mp((ppp[0]-tag[0]%ppp[0])%ppp[0],0-tag[0]));
				idd[0][0-tag[0]]=id; x0=id;
			}
			else
			{
				//for qury 2
				tree_mul(root,1,n+1,1,id-1,2);
				tree_add(root,1,n+1,id,id,1); num[id]=inf;
				add(1,1); add(id+1,-1);
				//for qury 3
				for (int i=30;i>=0;i--)
				{
					s[i].clear(); tag[i]=0; idd[i].clear();
					if (i) 
					{
						for (auto j:s[i-1]) 
						{
							s[i].insert(mp(2ll*(j.sc+tag[i-1])%ppp[i],2ll*(j.sc+tag[i-1]))); 
							idd[i][2ll*(j.sc+tag[i-1])]=idd[i-1][j.sc];
						}
					}
				}
				//printf("%lld %lld\n",(1-tag[1]%p[1]+p[1])%p[1],1-tag[1]);
				s[1].insert(mp((1-tag[1]%ppp[1]+ppp[1])%ppp[1],1-tag[1]));
				idd[1][1-tag[1]]=id;
			}
		}
		else if (op==2)
		{
			int g,x; scanf("%d%d",&g,&x); g++;
			long long a=qury(root,1,n+1,g),b=qury(g);
			printf("%lld\n",(a+1ll*(x-1)*p[b]%mo)%mo);
		}
		else if (op==3)
		{
			int x; scanf("%d",&x); long long ans=-100;
			for (int i=0;i<=30;i++)
			{
				long long now=(x%ppp[i]-tag[i]%ppp[i]+ppp[i])%ppp[i];
				auto lc=s[i].upper_bound(mp(now,x-tag[i]));
				//printf("asdasd %lld %d\n",now,x);
				if (lc==s[i].begin()) continue;else lc--;
				if ((*lc).fr!=now) continue;
				int pp=idd[i][(*lc).sc];
				//printf("lalal %lld %lld %d\n",(*lc).fr,(*lc).sc,num[pp]);
				if ((__int128)(*lc).sc+tag[i]<=x && x<=(__int128)(*lc).sc+tag[i]+(__int128)(num[pp]-1)*ppp[i]) {ans=pp; break;}
			}
			//if (ans<0) assert(0);
			if (x==0) ans=x0;
			printf("%lld\n",ans-1);
		}
	}
return 0;	
}
