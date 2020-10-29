#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[10];
int sta[1010],top=0;
int f[10];
int main(){
	int m;
	scanf("%d",&m);
	while(m--){
		for(int i=1;i<=7;i++){
			scanf("%d",&a[i]);
			f[i]=-1;
		}
		int cur;
		scanf("%d",&cur);
		top=0;
		for(int i=1;i<=cur+1;i++){
			while(top && a[sta[top-1]]>=a[i]) top--;
			if(top) f[i]=sta[top-1];
			sta[top]=i;
			top++;
		}
		vector<int> v;
		int pt=cur+1;
		while(pt!=-1){
			v.push_back(pt);
			pt=f[pt];
		}
		for(int i=(int)v.size()-1;i>=0;i--){
			printf("%d%c",v[i]-1," \n"[i==0]);
		}
	}
}
