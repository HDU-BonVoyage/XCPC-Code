#include <bits/stdc++.h>
using namespace std;
char s[600][600];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
	}
	int fg=1;int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((s[i][j]=='6' && s[n-i+1][m-j+1]=='9') || (s[i][j]=='9' && s[n-i+1][m-j+1]=='6')) continue;
			else if(s[i][j]==s[n-i+1][m-j+1]){
				if(s[i][j]=='8') continue;
				else ans++;
			}
			else{
				fg=0;
				break;
			}
		}
	}
	if((n&1) && (m&1)){
		if(s[(n+1)/2][(m+1)/2]!='8') fg=0;
	}
	if(!fg){
		printf("-1\n");
	}
	else{
		printf("%d\n",ans/2);
	}
	return 0;
}
