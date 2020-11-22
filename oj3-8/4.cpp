#include <bits/stdc++.h>

using namespace std;

int n,m,weight[210],u,v,w,t,w1,w2,edge[205][205],vis[205][205],start;

struct node{
    long long int d;
    int pre,cur;
    pair<int,int>pi;
    bool operator < (const struct node a) const
    {
        return d > a.d;
    }
}cost[205][205];

void Dijkstra();
void output();
void path(pair<int,int>a);

int main()
{
    scanf("%d%d%d%d",&n,&m,&w1,&w2);
    weight[0] = min(w1,w2);
    start = max(w1,w2);
    for(int i = 1;i <= n;i ++)
        scanf("%d",&weight[i]);
    for(int i = 0;i < m;i ++)
    {
        scanf("%d%d%d",&u,&v,&w);
        edge[u][v] = w;
    }
    scanf("%d",&t);
    Dijkstra();
    output();
}

void Dijkstra()
{
    priority_queue<struct node>q;
    for(int i = 0;i <= n;i++)
        for(int j = 0;j <= n;j++)
        {
            cost[i][j].d = 0x7ffffffffffff;
            cost[i][j].cur = i;
            cost[i][j].pre = j;
        }
    cost[0][201].d = 0;
    cost[0][201].cur = 0;
    cost[0][201].pre = 201;
    cost[0][201].pi = {0,0};
    vis[0][201] = 0;
    weight[201] = start;
    q.push(cost[0][201]);
    /*for(int i = 1;i <= n;i ++)
    {
        if(edge[i][0] != 0)
        {
            cost[i][0].d = edge[i][0]*(weight[0] + start);
            cost[i][0].pi = {0,0};
            q.push(cost[i][0]);
        }
    }*/
    while(!q.empty())
    {
        struct node temp = q.top();
        q.pop();
        int x = temp.cur,y = temp.pre;
        if(vis[x][y]) continue;
        vis[x][y] = 1;
        for(int i = 0;i <= n;i ++)
            if(cost[i][x].d > cost[x][y].d + 1LL*edge[x][i]*(1LL*weight[x]+1LL*weight[y])&&edge[x][i] != 0&&i != x)
            {
                cost[i][x].d = cost[x][y].d + 1LL*edge[x][i]*(1LL*weight[x]+1LL*weight[y]);
                cost[i][x].pi = {x,y};
                q.push(cost[i][x]);
            }
    }
}

void output()
{
    long long int ans = LONG_LONG_MAX,end;
    for(int i = 0; i <= n;i ++)
    {
        if(cost[t][i].d < ans&&i != t)
        {
            ans = cost[t][i].d;
            end = i;
        }
    }
    path({t,end});
}


void path(pair<int,int> a) {
    if(a.first == 0)
    {
        printf("%d ",0);
        return;
    }
    path(cost[a.first][a.second].pi);
    printf("%d ",a.first);
}


/*
3 5 2 3
1 2 1
0 1 2
0 3 5
1 3 5
1 2 5
3 2 2
2

 3 3 2 3
1 2 1
0 1 2
2 1 3
2 3 5
 3

 4 6 7 10
5 9 7 6
0 1 5
0 2 5
1 2 2
2 4 4
2 3 6
4 3 2
4
 */