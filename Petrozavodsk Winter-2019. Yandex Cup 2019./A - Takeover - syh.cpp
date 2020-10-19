#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <set>
#include <algorithm>
using namespace std;
const int inf=2e9+1;
const int maxn=3e5+10;
int n,X=1,Y=1,cnt,xx[maxn],yy[maxn],pa,pb;
bool f[maxn];
struct da{int x,y,id;}a[maxn],b[maxn];
struct daa
{
    int fr,sc;
    bool operator < (const daa& r)const {
        if (fr!=r.fr) return fr<r.fr;
        return sc<r.sc;
    }
};
set<daa>s1,s2,s3;
bool cmpx(da aa,da bb){return aa.x<bb.x;}
bool cmpy(da aa,da bb){return aa.y<bb.y;}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int x,y; scanf("%d%d",&x,&y); xx[i]=x; yy[i]=y;
        if (x<=1) s1.insert({y,i});
        else if (y<=1) s2.insert({x,i});
        else {cnt++; a[cnt]={x,y,i}; b[cnt]={x,y,i}; s3.insert({x+y,i}); f[i]=1;}
    }
    //printf("%d\n",(int)s1.size());
    sort(a+1,a+cnt+1,cmpx); sort(b+1,b+cnt+1,cmpy); pa=1; pb=1;
    for (int _=1;_<=n;_++)
    {
        int ans1=inf,ans2=inf,ans3=inf;
        if ((int)s1.size()!=0) ans1=((*s1.begin()).fr-Y);
        if ((int)s2.size()!=0) ans2=((*s2.begin()).fr-X);
        if ((int)s3.size()!=0) ans3=((*s3.begin()).fr-(X+Y));
        //printf("%d %d %d %d\n",_,ans1,ans2,ans3);
        if (ans1<=ans2 && ans1<=ans3)
        {
            printf("%d%c",(*s1.begin()).sc,(_==n?'\n':' '));
            Y=max(Y,(*s1.begin()).fr); s1.erase((*s1.begin()));
        }
        else if (ans2<=ans1 && ans2<=ans3)
        {
            printf("%d%c",(*s2.begin()).sc,(_==n?'\n':' '));
            X=max(X,(*s2.begin()).fr); s2.erase((*s2.begin()));
        }
        else
        {
            printf("%d%c",(*s3.begin()).sc,(_==n?'\n':' '));
            f[(*s3.begin()).sc]=0;
            X=max(X,xx[(*s3.begin()).sc]); Y=max(Y,yy[(*s3.begin()).sc]);
            s3.erase((*s3.begin()));
        }
        while (pa<=cnt && a[pa].x<=X)
        {
            if (f[a[pa].id]) s1.insert({a[pa].y,a[pa].id}),f[a[pa].id]=0,s3.erase({a[pa].x+a[pa].y,a[pa].id});
            pa++;
        }
        while (pb<=cnt && b[pb].y<=Y)
        {
            if (f[b[pb].id]) s2.insert({b[pb].x,b[pb].id}),f[b[pb].id]=0,s3.erase({b[pb].x+b[pb].y,b[pb].id});
            pb++;
        }
        //printf("lalla %d\n",(int)s2.size());
    }
return 0;
}
