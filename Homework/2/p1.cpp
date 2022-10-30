#include <bits/stdc++.h>
#define NMAX 100005
using namespace std;
ifstream in("p1.in");
ofstream out("p1.out");

bool start[NMAX];
int idx[NMAX];
vector<int> adj[NMAX];
vector<int> road;
bool used[NMAX];
int max_blocked_index;

bool blocked(int city)
{
    return idx[city] <= max_blocked_index;
}

bool cmp_cities(int &c1, int &c2)
{
    return idx[c1] < idx[c2];
}

// returns true if search reached a start point
bool explore(int u, unsigned int depth)
{
    bool new_road = false;

    for(unsigned int i = 0; i < adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if(!blocked(v))
        {
            if(start[v])
            {
                new_road = true;
                road.push_back(v);
                int min_index = NMAX;
                int city_min_index = NMAX;
                for(auto it = road.begin(); it != road.end(); ++it)
                    if(idx[*it] < min_index)
                    {
                        min_index = idx[*it];
                        city_min_index = *it;
                    }
                max_blocked_index = min_index;
                while(road.back() != city_min_index)
                {
                    used[road.back()] = false;
                    road.pop_back();
                }
                used[city_min_index] = false;
                road.pop_back();
                if(road.size() < depth)
                    break;
            }
            else if(!used[v])
            {
                used[v] = true;
                road.push_back(v);
                bool nr = explore(v, depth + 1);
                new_road = new_road || nr; // works too
                if(road.size() < depth)
                    break;
                if(!road.empty() && road.back() == v)
                {
                    // nodes that did not reach a start point in the end remain used
                    if(nr) used[v] = false;
                    road.pop_back();
                }
            }
        }
    }
    return new_road;
}

bool DFS(int u)
{
    for(unsigned int i = 0; i < adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if(!blocked(v))
        {
            if(start[v])
            {
                road.push_back(v);
                int min_index = NMAX;
                for(auto it = road.begin(); it != road.end(); ++it)
                    if(idx[*it] < min_index)
                    {
                        min_index = idx[*it];
                    }
                max_blocked_index = min_index;
                return true;
            }
            else if(!used[v])
            {
                used[v] = true;
                road.push_back(v);
                bool found = DFS(v);
                if(found) return true;
                road.pop_back();
            }
        }
    }
    return false;
}

int main()
{
    int n, m, nr_starts;
    in >> n >> m >> nr_starts;
    for(int i = 0, s; i < nr_starts; ++i)
    {
        in >> s;
        start[s] = true;
    }
    for(int i = 1, city; i < n; ++i)
    {
        in >> city;
        idx[city] = i;
    }
    for(int i = 0, x, y; i < m; ++i)
    {
        in >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    used[1] = true;
    explore(1, 0);

    bool found_road = true;
    while(found_road)
    {
        found_road = false;
        memset(used, 0, NMAX);
        road.clear();
        used[1] = true;
        found_road = DFS(1);
    }
    out << max_blocked_index << "\n";

    return 0;
}
