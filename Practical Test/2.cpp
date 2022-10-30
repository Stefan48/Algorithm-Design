#include <bits/stdc++.h>
#define NMAX 205
#define VMAX 21000
#define OFFSET 10005
using namespace std;
ifstream in("in");
ofstream out("out");

int v[NMAX];
vector<int> min_ops(VMAX, -1);
queue<int> Q;

int main()
{
    int n, src, dest;
    in >> n;
    for(int i = 0; i < n; ++i)
    {
        in >> v[i];
    }
    in >> src >> dest;

    int u;

    min_ops[src + OFFSET] = 0;
    Q.push(src);
    while(!Q.empty())
    {
        u = Q.front();
        Q.pop();
        if(u == dest) break;
        for(int i = 0; i < n; ++i)
        {
            if(u + v[i] <= 10000 && min_ops[u + v[i] + OFFSET] == -1)
            {
                min_ops[u + v[i] + OFFSET] = min_ops[u + OFFSET] + 1;
                Q.push(u + v[i]);
            }
            if(u - v[i] >= -10000 && min_ops[u - v[i] + OFFSET] == -1)
            {
                min_ops[u - v[i] + OFFSET] = min_ops[u + OFFSET] + 1;
                Q.push(u - v[i]);
            }
        }
    }

    out << min_ops[dest + OFFSET] << '\n';

    return 0;
}
