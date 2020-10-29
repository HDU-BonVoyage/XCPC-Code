#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int fa[N][2],k[N],c[N],n,x,y;
char num[N][8];
bitset<N> b[N],op,cur,tp;
map<int,int> mp;
char s[N];
void dfs(int u,int f){
	if(c[u]==f) return;
	c[u]=f; b[f].set(u);
	for(int i=0;i<k[u];++i) dfs(fa[u][i],f);
}
int read(){
	scanf("%s",s);
	int rs=0;
	for(int i=0;i<6;++i){
		rs=rs*16+(s[i]>='a'?s[i]-'a'+10:s[i]-'0');
	}
	return rs;
}
bool que(int x){
	printf("check %s\n",num[x]); fflush(stdout);
	scanf("%s",s); return s[0]=='b';
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		mp[read()]=i; strcpy(num[i],s);
		scanf("%d",&k[i]);
		for(int j=0;j<k[i];++j) fa[i][j]=mp[read()];
		dfs(i,i); op.set(i);
		//cout<<b[i]<<endl;
	}
	while(1){
		scanf("%s",s); int o=read();
		if(!o) break; o=mp[o]; cur=b[o];
		while(cur.count()>1){
			x=-1; y=N*3; //cout<<cur<<endl;
			for(int i=cur._Find_next(0);i<N;i=cur._Find_next(i)){
				//printf("find %d %d\n",i,abs((int)cur.count()-(int)tp.count()*2));
				tp=cur&b[i];
				if(abs((int)cur.count()-(int)tp.count()*2)<y){
					x=i;
					y=abs((int)cur.count()-(int)tp.count()*2);
				}
			}
			if(que(x)){
				cur=cur&b[x];
			}else{
				cur=cur&(b[x]^op);
			}
		}
		printf("fix %s\n",num[(int)cur._Find_next(0)]);
		fflush(stdout);
	}
}
