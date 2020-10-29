#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>
#include <set>
#define pb push_back
#define fr first
#define sc second
#define pii pair<int,int>
#define mp make_pair
using namespace std;
const int maxn=2e5+10;
int n,k,num,a[maxn];
vector<pii >ans;
multiset<pii >s;
struct da
{
	int sta[maxn],top;
	void init() {memset(sta,0,sizeof sta); top=0;}
	void pb(int x) {sta[++top]=x;}
	void pop() {top--;}
	int tp() {return sta[top];}
}now[120];
void gao(int a,int b) {now[b].pb(now[a].tp()); now[a].pop(); ans.pb(mp(a,b));}
void solve(int idd,int l,int r,bool f)
{
	if (l>=r) return;
	//if (r<0) printf("lala %d %d %d\n",idd,l,r);
	int L[120],id[120],cnt=0;
	for (int i=1;i<=k;i++) if (i!=idd) id[++cnt]=i,L[i]=now[i].top;
	int kk=(r-l+1)/(k-1)+((r-l+1)%(k-1)!=0),p=1,nn=0;
	for (int i=r;i>=l;i--)
	{
		gao(idd,id[p]);
		if (++nn==kk) nn=0,p++;
	}
	if (nn==0) p--;
	for (int i=1;i<=p;i++) solve(id[i],L[id[i]]+1,now[id[i]].top,!f);
	s.clear();
	for (int i=1;i<=p;i++)
	if (now[id[i]].top>L[id[i]] && now[id[i]].top>0) s.insert(mp(now[id[i]].tp(),id[i]));
	for (int _=l;_<=r;_++)
	{
		//if ((int)s.size()==0) printf("RE\n");
		auto pp=s.end(); pp--;
		if (!f) pp=s.begin();
		gao((*pp).sc,idd);
		int lc=(*pp).sc;
		s.erase(pp);
		if (now[lc].top>L[lc] && now[lc].top>0) s.insert(mp(now[lc].tp(),lc));
		
	}
}
bool ck()
{
	int laa=-100000000;
	for (int i=1;i<=k;i++)
     for (int j=now[i].top;j>=1;j--) if (now[i].sta[j]<laa) return 0;else laa=now[i].sta[j];
return 1;
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&k); ans.clear();
	for (int i=1;i<=k;i++) now[i].init();
	scanf("%d",&num);
	for (int i=1;i<=num;i++) scanf("%d",&a[i]);
	for (int i=num;i>=1;i--) now[1].pb(a[i]);
	for (int _=2;_<=k;_++)
	{
		scanf("%d",&num);
		for (int i=1;i<=num;i++) scanf("%d",&a[i]),now[1].pb(a[i]),ans.pb(mp(_,1));
	}
	solve(1,1,n,0);
	for (int i=k;i>=2;i--)
     for (int j=1;j<=n/k;j++) gao(1,i);
	solve(1,1,n/k,1); 
	//printf(ck()?"AC\n":"WA\n");
	printf("%d\n",(int)ans.size());
	for (auto i:ans) printf("%d %d\n",i.fr,i.sc);
return 0;
}
