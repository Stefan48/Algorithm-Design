#include <bits/stdc++.h>
#define NMAX 100005
using namespace std;
ifstream in("p2.in");
ofstream out("p2.out");

vector< pair<int, int> > adj[NMAX];
bool selected[NMAX];
stack<int> S;
vector<int> topsort;
vector<long long> d(NMAX, LLONG_MAX);

void DFS(int u)
{
    for(unsigned int i = 0; i < adj[u].size(); ++i)
    {
        int v = adj[u][i].first;
        if(!selected[v])
        {
            selected[v] = true;
            DFS(v);
        }
    }
    S.push(u);
}

int main()
{
    int n, m;
    int source, dest;
    in >> n >> m >> source >> dest;
    for(int i = 0, x, y, w; i < m; ++i)
    {
        in >> x >> y >> w;
        adj[x].push_back({y, w});
    }

    selected[source] = true;
    DFS(source);
    while(!S.empty())
    {
        topsort.push_back(S.top());
        S.pop();
    }

    d[source] = 0;
    for(unsigned int i = 0; i < topsort.size(); ++i)
    {
        int u = topsort[i];
        if(d[u] == LLONG_MAX) continue;
        for(unsigned int j = 0; j < adj[u].size(); ++j)
        {
            int v = adj[u][j].first;
            int w = adj[u][j].second;
            if(d[v] > d[u] + w)
                d[v] = d[u] + w;
        }
    }

    out << d[dest] << '\n';

    return 0;
}
