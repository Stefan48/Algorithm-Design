#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Wall
{
    int left;
    int right;
};

bool cmp(Wall x, Wall y)
{
    if(x.right == y.right)
        return x.left < y.left;
    return x.right > y.right;
}

int main()
{
    ifstream in("gard.in");
    ofstream out("gard.out");

    int n;
    in >> n;
    Wall *walls = new Wall[n];
    for(int i = 0; i < n; ++i)
        in >> walls[i].left >> walls[i].right;
    // sort walls primarily descending by right end, then ascending by left end
    sort(walls, walls + n, cmp);
    int cnt = 0;
    Wall last = walls[0]; // last non-redundant wall
    for(int i = 1; i < n; ++i)
    {
        if(walls[i].left >= last.left && walls[i].right <= last.right)
        {
            // wall is redundant
            cnt++;
        }
        else last = walls[i];
    }
    out << cnt;
    delete walls;
    return 0;
}
