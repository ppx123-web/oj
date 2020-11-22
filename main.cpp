#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,p,u,v,p1,p2,par[1000005],rk[1000005];

int find_set(int x)
{
    if(x != par[x])
        par[x] = find_set(par[x]);
    return par[x];
}

void make_set(int x)
{
    par[x] = x;
    rk[x] = 0;
}

void make_union(int x,int y)
{
    if(find_set(x) == find_set(y))
        return;
    else {
        int a = find_set(x);
        int b = find_set(y);
        if(rk[a] < rk[b])
        {
            par[b] = a;
        } else{
            par[a] = b;
            if(rk[a] == rk[b]) rk[b]++;
        }
    }
}



int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i = 0;i <= n;i ++)
        make_set(i);
    for(int i = 0;i < m;i ++)
    {
        scanf("%d%d",&u,&v);
        make_union(u,v);
    }
    for(int i = 0;i < p;i ++)
    {
        scanf("%d%d",&p1,&p2);
        if(find_set(p1) == find_set(p2)) printf("Yes\n");
        else printf("No\n");
    }
}
