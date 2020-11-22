#include <bits/stdc++.h>
using namespace std;

#define N 305

int n,m,key[16],a,b,w,edge[N][N],dis[N][N],p;

bool c[20400][15];

int find_level(int x)
{
    int ret = 0;
    for(int i  = 0; i <= 15;i ++)
    {
        if(((x>>i)&1) == 1) ret++;
    }
    return 10-ret;
}

void floyd();

int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i = 1;i <= p; i++)
        scanf("%d",&key[i]);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            edge[i][j] = 0x3f3f3f3f;
    for(int i = 0; i < m;i++)
    {
        scanf("%d%d%d",&a,&b,&w);
        edge[a][b] = edge[b][a] = w;
    }
    floyd();
    for(int i = 1;i <= n;i ++)
        dis[i][i] = -100;
    for(int i = 1;i <= p;i++)
    {
        if(dis[1][key[i]] <= 10)
            c[1<<(i-1)][i] = true;
    }
    for(int s = 0;s < (1<<p);s ++)
    {
        int level = find_level(s);
        for(int i = 1; i <= p;i++)
        {
            if(c[s][i] == 1&&((s>>(i-1))&1)==1)
            {
                for(int j = 1;j <= p;j ++)
                {
                    if(level >= dis[key[i]][key[j]])
                        c[s|(1<<(j-1))][j] = true;
                }
            }
        }
    }
    int ans = 0;
    for(int s = 0;s < (1<<p);s++)
    {
        int level = find_level(s);
        for(int i = 1;i <= p;i++)
        {
            if(level >= dis[1][key[i]]&&c[s][i] == true)
                ans = max(10-level,ans);
        }
    }
    printf("%d\n",ans);
}


void floyd()
{
    for(int i = 1; i <= n;i ++)
        for(int j = 1;j <= n;j ++)
        {
            if(edge[i][j] != 0x3f3f3f3f) dis[i][j] = edge[i][j];
            else if(i == j) dis[i][j] = 0;
            else dis[i][j] = 0x3f3f3f3f;
        }
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i ++)
            for(int j = 1;j <= n;j ++)
            {
                if(dis[i][j] > max(dis[i][k],dis[k][j]))
                    dis[i][j] = max(dis[i][k],dis[k][j]);
            }
}

