#include <bits/stdc++.h>
#define NMAX 100005
using namespace std;

vector< pair<int, int> > adj[NMAX];
bool selected[NMAX];
double energy[NMAX];
int parent[NMAX];

void print_road(int u, FILE *out)
{
    if(parent[u])
        print_road(parent[u], out);
    fprintf(out, "%d ", u);
}

int main()
{
    ifstream in("p3.in");
    FILE *out = fopen("p3.out", "w");

    int n, m, E;
    in >> n >> m >> E;
    for(int i = 0, x, y, p; i < m; ++i)
    {
        in >> x >> y >> p;
        adj[x].push_back({y, p});
    }
    auto comp = [](pair<int, double> a, pair<int, double> b) {return a.second < b.second;};
    priority_queue<pair<int, double>, vector< pair<int, double> >, decltype(comp)> pq(comp);
    energy[1] = (double)E;
    pq.push({1, energy[1]});
    while(!pq.empty())
    {
        int u = pq.top().first;
        pq.pop();
        if(selected[u]) continue;
        selected[u] = true;
        for(unsigned i = 0; i < adj[u].size(); ++i)
        {
            int v = adj[u][i].first;
            int p = adj[u][i].second;
            if(!selected[v] && energy[v] < energy[u] * (1.0 - (double)p / 100.0))
            {
                energy[v] = energy[u] * (1.0 - (double)p / 100.0);
                pq.push({v, energy[v]});
                parent[v] = u;
            }
        }
    }

    fprintf(out, "%.8lf\n", energy[n]);
    print_road(n, out);
    fprintf(out, "\n");

    return 0;
}
