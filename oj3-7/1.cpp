#include <bits/stdc++.h>
using namespace std;

#define MAXN 362900
#define end 362879

int a[9],b[9]={0,1,2,3,4,5,6,7,8};

struct permute{
    int c[9],state,color,d,parent;
}per[MAXN];

vector<int>edge[MAXN];
queue<int>q;
int find_state(int* z);
void permutation(int x,int y);
void link(int x1,int y1,int z,int origin);
int fact(int x)
{
    if(x == 0)
        return 1;
    else return x*fact(x-1);
}
void bfs(int x);
char find_op(int x,int y);

int main()
{
    for(int & i : a)
        scanf("%d",&i);
    if(a[0]==1&&a[1]==2&&a[2]==3&&a[3]==4&&a[4]==5&&a[5]==6&&a[6]==7&&a[7]==8&&a[8]==0)
        return 0;
    permutation(0,9);
    int zero = -1;
    for(int i = 0;i < end;i++)
    {
        for(int j = 0;j < 9;j++)
            if(per[i].c[j] == 0) {zero = j;break;};
        link(zero/3-1,zero%3,i,zero);
        link(zero/3+1,zero%3,i,zero);
        link(zero/3,zero%3-1,i,zero);
        link(zero/3,zero%3+1,i,zero);
    }
    int origin = find_state(a);
    bfs(origin);
    int d[9] = {1,2,3,4,5,6,7,8,0};
    int temp = find_state(d),num=0;
    char op[1000]={0};
    if(per[temp].parent == -1)
        printf("unsolvable\n");
    else{
        while(per[temp].state != origin)
        {
            op[num++] = find_op(temp,per[temp].parent);
            temp = per[temp].parent;
        }
        for(int i = num-1;i >=0 ;i--)
            printf("%c",op[i]);
    }


}

void permutation(int x,int y)
{
    if(x == y)
    {
        int temp = find_state(b);
        per[temp].state = temp;
        for(int i = 0;i < 9;i ++)
            per[temp].c[i] = b[i];
    }
    else{
        for(int i = x;i < y;i++)
        {
            swap(b[x],b[i]);
            permutation(x+1,y);
            swap(b[x],b[i]);
        }
    }

}

int find_state(int* z)
{
    int ret = 0,temp[9]={0};
    for(int i = 0;i < 9;i ++)
        for(int j = i+1;j < 9;j++)
        {
            if(z[i] > z[j])
                temp[i]++;
        }
    for(int i = 0;i < 9;i ++)
    {
        ret+=temp[i]*fact(8-i);
    }
    return ret;
}

void link(int x,int y,int z,int origin)
{
    if(x<0||x>2||y<0||y>2)
        return;
    else {
        int temp;
        swap(per[z].c[origin], per[z].c[3 * x + y]);
        temp = find_state(per[z].c);
        edge[z].push_back(temp);
        swap(per[z].c[origin], per[z].c[3 * x + y]);
        return;
    }
}

void bfs(int x)
{
    int temp;
    for(int i = 0;i < end;i++)
    {
        per[i].d = INT32_MAX;
        per[i].parent = -1;
        per[i].color = 0;
    }
    per[x].color = 1;
    per[x].d = 0;
    per[x].parent = -1;
    q.push(x);
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        for(auto &it:edge[temp]) {
            if (per[it].color == 0) {
                per[it].color = 1;
                per[it].d = per[temp].d + 1;
                per[it].parent = temp;
                q.push(it);
            }
        }
    }

}

char find_op(int x,int y)
{
    int zero_x,zero_y;
    for(int j = 0;j < 9;j++)
        if(per[x].c[j] == 0) {zero_x = j;break;};
    for(int j = 0;j < 9;j++)
        if(per[y].c[j] == 0) {zero_y = j;break;};
    if(zero_x - zero_y == 3)
        return 'd';
    if(zero_y - zero_x == 3)
        return 'u';
    if(zero_y - zero_x == 1)
        return 'l';
    if(zero_x - zero_y == 1)
        return 'r';
}