#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int p[N],n;
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d",&p[i]);
    printf("%d\n",2*n-1);
    for(int i=1;i<=2*n-1;++i){
        for(int j=i;j<i+2*n-1;++j){
            printf("%d ",p[j%n]);
        }
        printf("\n");
    }
}
