#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pr;
typedef long long ll;
const int N = 1e5+10;
char ch[54]="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
int v[54]={1,1,2,1,0,0,1,1,0,1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ps(char x){
    if(x>='a') return (x-'a')<<1|1;
    else return (x-'A')<<1;
}
int to[54][3];
int dis(int a,int b){
    return (b-a+52)%52;
}
struct Node{
    int d,o;
    Node(int _d,int _o){
        d=_d; o=_o;
    }
    bool operator < (const Node &rhs) const{
        if(d!=rhs.d) return d<rhs.d;
        else return o<rhs.o;
    }
};
set<Node> st1,st2,st3;
char s[N]; int a[N],b[N],n,ans; ll k;
void prep(){
    memset(to,-1,sizeof(to));
    for(int i=0;i<52;++i)
        for(int j=0;j<52;++j)
            if(to[i][v[(i+j)%52]]==-1) to[i][v[(i+j)%52]]=j;
    for(int i=1;i<=n;++i) a[i]=b[i]=ps(s[i]);
}
void add(int o,int f){
	if(f==1){
		if(v[b[o]]==0){
			st1.insert(Node(to[a[o]][1]-dis(a[o],b[o]),o));
			st2.insert(Node(to[a[o]][2]-dis(a[o],b[o]),o));
		}else if(v[b[o]]==1){
			st1.insert(Node(to[a[o]][2]-dis(a[o],b[o]),o));
			st3.insert(Node(to[a[o]][0]-dis(a[o],b[o]),o));
		}else{
			st3.insert(Node(to[a[o]][1]-dis(a[o],b[o]),o));
		}
	}else{
		if(v[b[o]]==2){
			st1.insert(Node(to[a[o]][1]-dis(a[o],b[o]),o));
			st2.insert(Node(to[a[o]][0]-dis(a[o],b[o]),o));
		}else if(v[b[o]]==1){
			st1.insert(Node(to[a[o]][0]-dis(a[o],b[o]),o));
			st3.insert(Node(to[a[o]][2]-dis(a[o],b[o]),o));
		}else{
			st3.insert(Node(to[a[o]][1]-dis(a[o],b[o]),o));
		}
	}
}
void del(int o,int f){
	if(f==1){
		if(v[b[o]]==0){
			st1.erase(Node(to[a[o]][1]-dis(a[o],b[o]),o));
			st2.erase(Node(to[a[o]][2]-dis(a[o],b[o]),o));
		}else if(v[b[o]]==1){
			st1.erase(Node(to[a[o]][2]-dis(a[o],b[o]),o));
			st3.erase(Node(to[a[o]][0]-dis(a[o],b[o]),o));
		}else{
			st3.erase(Node(to[a[o]][1]-dis(a[o],b[o]),o));
		}
	}else{
		if(v[b[o]]==2){
			st1.erase(Node(to[a[o]][1]-dis(a[o],b[o]),o));
			st2.erase(Node(to[a[o]][0]-dis(a[o],b[o]),o));
		}else if(v[b[o]]==1){
			st1.erase(Node(to[a[o]][0]-dis(a[o],b[o]),o));
			st3.erase(Node(to[a[o]][2]-dis(a[o],b[o]),o));
		}else{
			st3.erase(Node(to[a[o]][1]-dis(a[o],b[o]),o));
		}
	}
}
void solve(){
    int det=0,id;
    for(int i=1;i<=n;++i) det+=v[a[i]];
    det=k-det;
	st1.insert(Node(N,N));
    st2.insert(Node(N,N));
    st3.insert(Node(N,N));
	if(det>0){
        for(int i=1;i<=n;++i) add(i,1);
        while(det--){
            auto o=st1.begin(),p=st2.begin(),q=st3.begin();
            if((*o).d<=(*p).d+(*q).d){
                ans+=(*o).d; id=(*o).o;
                del(id,1);
                if(v[b[id]]==0){
                	b[id]=(a[id]+to[a[id]][1])%52;
				}else if(v[b[id]]==1){
					b[id]=(a[id]+to[a[id]][2])%52;
				}
				add(id,1);
            }else{
				ans+=(*p).d+(*q).d; 
				id=(*p).o; del(id,1);
            	b[id]=(a[id]+to[a[id]][2])%52;
            	add(id,1);
            	id=(*q).o; del(id,1);
            	if(v[b[id]]==1){
            		b[id]=(a[id]+to[a[id]][0])%52;
            	}else if(v[b[id]]==2){
            		b[id]=(a[id]+to[a[id]][1])%52;
				}
            	add(id,1);
			}
        }
    }else if(det<0){
        for(int i=1;i<=n;++i) add(i,-1); det=-det;
        while(det--){
            auto o=st1.begin(),p=st2.begin(),q=st3.begin();
            if((*o).d<=(*p).d+(*q).d){
                ans+=(*o).d; id=(*o).o;
                del(id,-1);
                if(v[b[id]]==2){
                	b[id]=(a[id]+to[a[id]][1])%52;
				}else if(v[b[id]]==1){
					b[id]=(a[id]+to[a[id]][0])%52;
				}
				add(id,-1);
            }else{
				ans+=(*p).d+(*q).d; 
				id=(*p).o; del(id,-1);
            	b[id]=(a[id]+to[a[id]][0])%52;
            	add(id,-1);
            	id=(*q).o; del(id,-1);
            	if(v[b[id]]==1){
            		b[id]=(a[id]+to[a[id]][2])%52;
            	}else if(v[b[id]]==0){
            		b[id]=(a[id]+to[a[id]][1])%52;
				}
            	add(id,-1);
			}
        }
    }
}
int main(){
    scanf("%d %lld %s",&n,&k,s+1); prep();
    if(k>n*2||k<0){
        printf("-1\n");
    }else{
        solve();
        for(int i=1;i<=n;++i) s[i]=ch[b[i]];
        printf("%d\n%s\n",ans,s+1);
    }
}
