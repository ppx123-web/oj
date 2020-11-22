#include <bits/stdc++.h>
using namespace std;

int t,x,y,start_x,start_y,end_x,end_y,ans,T_x,T_y,F_x,F_y;
bool flag = false;
char ch[505][505];

typedef struct {
    int type,dx,dy,pi_x,pi_y,time;
}node;

typedef struct {
    int dx,dy,state;
}state;

node point[505][505][4];
state temp;
queue<state>q;

void clear(queue<state>& z) {
    queue<state> empty;
    swap(empty, z);
}
void solve(int a,int b,int c,int dx,int dy);
void BFS(int a,int b,int state);

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        flag = false;
        ans = 0;
        clear(q);
        memset(point,0,sizeof(point));
        memset(ch,0,sizeof(ch));
        scanf("%d%d",&x,&y);
        for(int i = 0;i < x;i++)
            scanf("%s",ch[i]);
        for(int i = 0;i < x;i++)
            for(int j = 0;j < y;j++)
            {
                if(ch[i][j] == 'S')
                {
                    start_x = i;
                    start_y = j;
                }
                if(ch[i][j] == 'T')
                {
                    T_x = i;
                    T_y = j;
                }
                if(ch[i][j] == 'F')
                {
                    F_x = i;
                    F_y = j;
                }
                if(ch[i][j] == 'E')
                {
                    end_x = i;
                    end_y =j;
                }
                for(int k = 0;k < 4;k++)
                {
                    point[i][j][k].type = ch[i][j];
                    point[i][j][k].dx = -1;
                    point[i][j][k].dy = -1;
                    point[i][j][k].pi_x = -1;
                    point[i][j][k].pi_y = -1;
                    point[i][j][k].time = -1;
                }
            }
        BFS(start_x,start_y,0);
        printf("%d\n",point[end_x][end_y][ans].time);
    }
}

void BFS(int a,int b,int state)
{
    //point[a][b][state].color = 0;
    temp.dx=a;
    temp.dy=b;
    temp.state=0;
    point[a][b][state].time = 0;
    q.push(temp);
    while(!q.empty())
    {
        temp = q.front();
        q.pop();
        solve(temp.dx-1,temp.dy,temp.state,temp.dx,temp.dy);
        solve(temp.dx+1,temp.dy,temp.state,temp.dx,temp.dy);
        solve(temp.dx,temp.dy-1,temp.state,temp.dx,temp.dy);
        solve(temp.dx,temp.dy+1,temp.state,temp.dx,temp.dy);
        //point[temp.dx][temp.dy][state].color = 0;
        if(flag) return;
    }
}

void solve(int a,int b,int c,int dx,int dy)
{
    if(a < 0||b <0||a >= x||b >= y)
        return;
    state use;
    switch (point[a][b][c].type) {
        case 'S':
        case '.':
            point[a][b][c].pi_x=dx;
            point[a][b][c].pi_y=dy;
            //point[a][b][c].color=0;
            point[a][b][c].time = point[dx][dy][c].time + 1;
            use.dx = a;
            use.dy = b;
            use.state = c;
            q.push(use);
            break;
        case '#':
            if(c == 0)
                return;
            else {
                c--;
                point[a][b][c].pi_x=dx;
                point[a][b][c].pi_y=dy;
                //point[a][b][c].color=0;
                point[a][b][c].time = point[dx][dy][c+1].time + 2;
                use.dx = a;
                use.dy = b;
                use.state = c;
                q.push(use);
                for(int i = 0;i < 4;i++)
                    point[a][b][i].type = '.';
            }
            break;
        case 'H':
            if(c < 3) c++;
            point[a][b][c].pi_x=dx;
            point[a][b][c].pi_y=dy;
            //point[a][b][c].color=0;
            point[a][b][c].time = point[dx][dy][c-1].time + 1;
            use.dx = a;
            use.dy = b;
            use.state = c;
            q.push(use);
            break;
        case 'P':
            point[a][b][c].pi_x=dx;
            point[a][b][c].pi_y=dy;
            //point[a][b][c].color=0;
            point[a][b][c].time = point[dx][dy][c].time;
            use.dx = a;
            use.dy = b;
            use.state = c;
            q.push(use);
            break;
        case 'F':
            point[T_x][T_y][c].pi_x=dx;
            point[T_x][T_y][c].pi_y=dy;
            //point[T_x][T_y][c].color=0;
            point[T_x][T_y][c].time = point[dx][dy][c].time + 1;
            use.dx = T_x;
            use.dy = T_y;
            use.state = c;
            q.push(use);
            break;
        case 'T':
            point[F_x][F_y][c].pi_x=dx;
            point[F_x][F_y][c].pi_y=dy;
            //point[F_x][F_y][c].color=0;
            point[F_x][F_y][c].time = point[dx][dy][c].time + 1;
            use.dx = F_x;
            use.dy = F_y;
            use.state = c;
            q.push(use);
            break;
        case 'E':
            flag = true;
            point[a][b][c].pi_x=dx;
            point[a][b][c].pi_y=dy;
            //point[a][b][c].color=0;
            point[a][b][c].time = point[dx][dy][c].time + 1;
            ans = c;
            break;
    }
}



/*
3
2 2
S#
#E
5 3
S..
..H
###
###
E..
4 5
S#...
...#.
...#.
F.#TE


 1
 2 3
 S.#
 H#E
*/


