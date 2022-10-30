#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

struct Dumbbell
{
    int weight;
    int reps;
};

bool cmp(Dumbbell &x, Dumbbell &y)
{
    if(x.weight == y.weight)
        return x.reps > y.reps;
    return x.weight > y.weight;
}

int main()
{
    ifstream in("sala.in");
    ofstream out("sala.out");

    int n, m;
    in >> n >> m;
    Dumbbell *v = new Dumbbell[n];
    for(int i = 0; i < n; ++i)
        in >> v[i].weight >> v[i].reps;
	// sort dumbbells primarily descending by weight, then descending by weight
    sort(v, v + n, cmp);

    long long sum = v[0].reps;
    int cnt = 1;
    multiset<int> reps_set; // set of reps sorted in ascending order
    reps_set.insert(v[0].reps);
    long long result = 1LL * v[0].weight * v[0].reps;
    long long res;
    for(int i = 1; i < n; ++i)
    {
        if(cnt < m)
        {
            // select dumbbell and check if new solution
            cnt++;
            sum += v[i].reps;
            reps_set.insert(v[i].reps);
            res = 1LL * v[i].weight * sum;
            if(res > result)
                result = res;
        }
        // if I can increase the total number of reps in reps_set
        else if(v[i].reps > *reps_set.begin())
        {
            // select dumbbell and check if new solution
            sum += v[i].reps - *reps_set.begin();
            reps_set.erase(reps_set.begin());
            reps_set.insert(v[i].reps);
            res = 1LL * v[i].weight * sum;
            if(res > result)
                result = res;
        }
    }
    out << result << "\n";

    delete v;
    return 0;
}
