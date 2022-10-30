#include <bits/stdc++.h>
#define NMAX 1105
using namespace std;
ifstream in("in");
ofstream out("out");

int n, m;
int v[NMAX][NMAX];
bool visited[NMAX][NMAX];
int depth[NMAX][NMAX];
int rez;

bool validPosition(int x, int y)
{
    return x > 0 && y > 0 && x <= n && y <= m;
}

int main()
{
    int moves, lin, col;
    in >> n >> m >> moves >> lin >> col;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            in >> v[i][j];
    rez = v[lin][col];

    queue< pair<int, int> > Q;
    visited[lin][col] = true;
    depth[lin][col] = 0;

    pair<int, int> pos;
    int x, y;

    Q.push({lin, col});
    while(!Q.empty())
    {
        pos = Q.front();
        Q.pop();
        x = pos.first;
        y = pos.second;
        if(depth[x][y] >= moves)
            break;
        if(validPosition(x-1, y) && !visited[x-1][y])
        {
            visited[x-1][y] = true;
            depth[x-1][y] = depth[x][y] + 1;
            if(v[x-1][y] > rez)
                rez = v[x-1][y];
            Q.push({x-1, y});
        }
        if(validPosition(x+1, y) && !visited[x+1][y])
        {
            visited[x+1][y] = true;
            depth[x+1][y] = depth[x][y] + 1;
            if(v[x+1][y] > rez)
                rez = v[x+1][y];
            Q.push({x+1, y});
        }
        if(validPosition(x, y-1) && !visited[x][y-1])
        {
            visited[x][y-1] = true;
            depth[x][y-1] = depth[x][y] + 1;
            if(v[x][y-1] > rez)
                rez = v[x][y-1];
            Q.push({x, y-1});
        }
        if(validPosition(x, y+1) && !visited[x][y+1])
        {
            visited[x][y+1] = true;
            depth[x][y+1] = depth[x][y] + 1;
            if(v[x][y+1] > rez)
                rez = v[x][y+1];
            Q.push({x, y+1});
        }
    }

    out << rez << '\n';


    return 0;
}
