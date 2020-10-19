#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int a[N][N],n;
int getmin(){
    int sm=0;
    for(int i=1,op;i<=n;++i){
        op=N;
        for(int j=1;j<=n;++j){
            op=min(op,a[i][j]);
        }
        if(sm<op) sm=op;
    }
    return sm;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j) scanf("%d",&a[i][j]);
    printf("%d\n",getmin());
}
