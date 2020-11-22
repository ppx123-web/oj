#include <bits/stdc++.h>

#define ll long long int
int n,m,a,b,c,edge[505][505],dis[505][505];

ll cntedge[505][505];
void floyd();

int main()
{
    scanf("%d%d",&n,&m);
    for(int i = 0;i < m; i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        edge[a][b] = edge[b][a] = c;
        cntedge[b][a] = cntedge[a][b] = 1;
    }
    floyd();
    for(int i = 1;i <= n;i ++)
    {
        double ans = 0,pass;
        for(int j = 1;j <= n;j ++)
            for(int k = 1;k <= n;k ++)
            {
                if(i == j||i == k||j == k) continue;
                if(dis[j][i] + dis[i][k] == dis[j][k])
                {
                    pass = cntedge[j][i]*cntedge[i][k];
                    ans += (double)pass/(double)cntedge[j][k];
                }
            }
        printf("%.7lf\n",ans);
    }

}

void floyd()
{
    for(int i = 1;i <= n;i ++)
        for(int j = 1;j <= n;j ++)
        {
            if(edge[i][j] != 0) dis[i][j] = edge[i][j];
            else if(i == j) dis[i][j] = 0;
            else dis[i][j] = 0x3f3f3f3f;
        }
    for(int k = 1;k <= n;k ++)
        for(int i = 1;i <= n;i ++)
            for(int j = 1;j <= n;j ++)
            {
                if(dis[i][j] > dis[i][k] + dis[k][j]){
                    dis[i][j] = dis[i][k] + dis[k][j];
                    cntedge[i][j] = cntedge[i][k]*cntedge[k][j];
                }
                else if(dis[i][j] == dis[i][k] + dis[k][j]&&k != j&&i != k)
                {
                    cntedge[i][j] += cntedge[i][k]*cntedge[k][j];
                }
            }
}

/*
6 8
1 2 1
2 4 1
4 6 1
2 3 1
1 3 1
3 5 1
4 5 1
5 6 1


 9 12
 1 2 1
 1 3 1
 2 4 1
 3 4 1
 3 5 1
 4 5 1
 5 6 1
 5 7 1
 6 8 1
 6 7 1
 7 9 1
 8 9 1
 */