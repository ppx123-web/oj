#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <stack>
#include <climits>
using namespace std;
typedef long long ll;
typedef struct {
    int to;
    int dis;
}edge;
struct node{
    int x;
    int y;
    ll d;
};
struct cmp{
    bool operator()(const node a,const node b){
        return a.d>b.d;
    }
};
typedef struct node node;
vector<edge> edges[205];
ll cost[205][205];
struct f{
    int x,y;
};
struct f fa[205][205];
int n,m;
int w[205];
int w1,w2;
int target;
void bfs(){
    for(auto & i : cost){
        for(auto & j : i) {
            j = LLONG_MAX;
        }
    }
    bool vis[205][205];
    memset(vis,0, sizeof(vis));
    cost[0][201]=0;
    if(w1>w2){
        int tmp=w1;
        w1=w2;
        w2=tmp;
    }
    w[0]=w1;w[201]=w2;
    priority_queue<node,vector<node>,cmp>pq;
    pq.emplace(node{0,201,0});
    while(!pq.empty()){
        node tmp=pq.top();
        pq.pop();
        if(vis[tmp.x][tmp.y])continue;
        vis[tmp.x][tmp.y]= true;
        for(size_t i=0;i<edges[tmp.x].size();i++){
            int next=edges[tmp.x][i].to;
            ll newcost=tmp.d+1LL*edges[tmp.x][i].dis*(1LL*w[tmp.x]+1LL*w[tmp.y]);
            if(cost[next][tmp.x]>newcost){
                cost[next][tmp.x]=newcost;
                fa[next][tmp.x]=f{tmp.x,tmp.y};
                pq.emplace(node{next,tmp.x,newcost});
            }
        }
    }
}

int main(){
    memset(fa,-1, sizeof(fa));
    scanf("%d%d%d%d",&n,&m,&w1,&w2);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
    }
    for(int i=0;i<m;i++) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        edges[x].emplace_back(edge{y, c});
    }
    scanf("%d",&target);
    bfs();
    int t=201;
    ll minans=LLONG_MAX;
    for(int i=0;i<=n;i++){
        if(cost[target][i]<minans){
            t=i;
            minans=cost[target][i];
        }
    }
    stack<int>ans;
    ans.push(target);
    while(t!=201){
        ans.push(t);
        int tmp=t;
        t=fa[target][t].y;
        target=tmp;
    }
    while(!ans.empty()){
        printf("%d ",ans.top());
        ans.pop();
    }
}