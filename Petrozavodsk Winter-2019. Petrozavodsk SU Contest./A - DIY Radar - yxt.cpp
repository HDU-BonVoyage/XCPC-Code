#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void q(int x,int y){
    printf("Q %d %d\n",x,y);
    fflush(stdout);
}
struct node{
    ll x,y;
};
vector<node>v[20100];
vector<node> tmp;
node nd;
ll dis;
int dx[]={-1,1,0,0};
int dy[]={0,0,1,-1};
ll dd(node a,node b){
    ll dx=abs(a.x-b.x),dy=abs(a.y-b.y);
    return dx*dx+dy*dy;
}
int chk(int tx,int ty){
    int ret=0;
    scanf("%lld",&dis);
    //int ppp=rand()%4;
    //dis=dd((node){tx,ty},nd);
    //printf("%lld\n",dis);

    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            int pt=i*101+j;
            int fg=0;
            for(node x:v[pt]){
                if(dd(x,(node){tx,ty})==dis){
                    fg=1;
                    //ret++;
                    for(int k=0;k<4;k++){
                        if(x.x+dx[k]>=0 && x.x+dx[k]<=100 && x.y+dy[k]>=0 &&x.y+dy[k]<=100) tmp.push_back((node){x.x+dx[k],x.y+dy[k]});
                    }
                }
            }
            ret+=fg;
            v[pt].clear();
            for(node x:tmp){
                v[pt].push_back(x);
            }
            tmp.clear();
        }
    }

   // while(!(nd.x+dx[ppp]>=0 && nd.x+dx[ppp]<=100 && nd.y+dy[ppp]>=0 &&nd.y+dy[ppp]<=100)){
     //   ppp=rand()%4;
    //}nd.x+=dx[ppp];nd.y+=dy[ppp];
    return ret;
}
int cou=0;
void work(){
    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            int pt=i*101+j;
            v[pt].push_back((node){i,j});
        }
    }
    ll tx=101,ty=997;
    q(tx,ty);
    int fg=chk(tx,ty);
    //printf("num: %d\n",fg);
    if(fg>1){
        tx=997;ty=101;
        q(tx,ty);
        fg=chk(tx,ty);
        //printf("num: %d\n",fg);
    }
    if(fg>1){
        tx=213;ty=817;
        q(tx,ty);
        fg=chk(tx,ty);
        //printf("num: %d\n",fg);
    }
    if(fg>1){
        tx=523;ty=679;
        q(tx,ty);
        fg=chk(tx,ty);
        //printf("num: %d\n",fg);
    }
    if(fg==1){
        for(int i=0;i<=101*101;i++){
            if(v[i].size()){
                printf("A %d %d\n",i/101,i%101);
                break;
            }
        }
        for(int i=0;i<=101*101;i++){
            v[i].clear();
        }
        tmp.clear();
    }
    else{
        printf("%d %d\n",nd.x,nd.y);
        //assert(0);
        //cou++;
    }

}
int main(){
    //srand(time(0));
    //for(int aa=0;aa<=100;aa++){
     //   for(int bb=9;bb<=100;bb++){
     //       nd.x=aa;nd.y=bb;
            work();
            //printf("%d %d\n",aa,bb);
     //   }
   // }
   // printf("%d\n",cou);
    return 0;
}
