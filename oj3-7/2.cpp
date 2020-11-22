#include <bits/stdc++.h>

#define MAXN 1005
#define vmax 1000000

int a[MAXN][MAXN],ans[MAXN][MAXN],n,m;
int answer;
int dfs(int x,int y,int p);

int main()
{
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;i++)
        for(int j = 0;j < m;j++)
            scanf("%d",&a[i][j]);
    for(int i = 0;i < n;i++)
        for(int j = 0;j < m;j ++)
        {
            answer = std::max(answer,dfs(i,j,vmax));
        }
    printf("%d\n",answer);
}

int dfs(int x,int y,int p)
{
    if(x<0||y<0||x>=n||y>=m)
        return 0;
    if(a[x][y] >= p)
        return 0;
    if(ans[x][y] != 0)
        return ans[x][y];
    int ret = 0;
    ret = std::max(ret,std::max(dfs(x-1,y,a[x][y]),dfs(x+1,y,a[x][y]))+1);
    ret = std::max(ret,std::max(dfs(x,y-1,a[x][y]),dfs(x,y+1,a[x][y]))+1);
    ans[x][y] = ret;
    return ret;
}

