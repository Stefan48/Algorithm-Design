#include <iostream>
#include <fstream>
#include <vector>
#define MOD 1000000007
using namespace std;

int main()
{
    ifstream in("bomboane.in");
    ofstream out("bomboane.out");

    int n, sum;
    in >> n >> sum;
    vector< pair <int, int> >intervals(n + 1);
    for(int i = 1; i <= n; ++i)
        in >> intervals[i].first >> intervals[i].second;
    int **dp = new int*[sum + 1];
    // dp[i][j] - the number of ways I can obtain sum i
    // using all the kids from 1 to j and no other kid
    for(int i = 0; i <= sum; ++i)
        dp[i] = new int[n + 1]();
    // initialize for 1st kid's interval
    for(int i = intervals[1].first; i <= intervals[1].second && i <= sum; ++i)
        dp[i][1] = 1;
    // kids from 2 to n
    for(int j = 2; j <= n; ++j)
    {
        // sums from 0 to given sum
        for(int i = 0; i <= sum; ++i)
        {
            // if kid j's interval contains k then add the number of ways
            // the kids from 1 to (k - 1) can obtain the sum (i - k)
            for(int k = intervals[j].first; k <= intervals[j].second && k <= i; ++k)
            {
                dp[i][j] = (dp[i][j] + dp[i - k][j - 1]) % MOD;
            }
        }
    }
    out << dp[sum][n] << "\n";

    for(int i = 0; i <= sum; ++i)
        delete dp[i];
    delete dp;
    return 0;
}
