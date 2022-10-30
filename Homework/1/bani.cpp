#include <iostream>
#include <fstream>
#define MOD 1000000007
using namespace std;

// exponentiation by squaring
int pow2(int exp)
{
    if(exp == 0)
        return 1;
    if(exp % 2)
        return (2 * pow2(exp - 1)) % MOD;
    int tmp = pow2(exp / 2);
    return (1LL * tmp * tmp) % MOD;

}

int main()
{
    ifstream in("bani.in");
    ofstream out("bani.out");

    int type, n;
    in >> type >> n;
    if(type == 1)
    {
        // result is 5 * (2 ^ (n - 1))
        int res = (1LL * 5 * pow2(n - 1)) % MOD;
        out << res;
        return 0;
    }
    int *dp[5];
    // dp[i][j] - the number of ways I can arrange j bills, knowing the
    // first one of them has index i (of the 5 given possibilities)
    for(int i = 0; i < 5; ++i)
    {
        dp[i] = new int[n + 1];
        // I can arrange a single bill in only one way
        dp[i][1] = 1;
    }
    for(int i = 2; i <= n; ++i)
    {
        // compute each step based on the previous ones
        // of the bills each bill depends on
        dp[0][i] = (dp[1][i - 1] + dp[2][i - 1]) % MOD;                        // 10
        dp[1][i] = (dp[0][i - 1] + dp[3][i - 1]) % MOD;                        // 50
        dp[2][i] = (dp[0][i - 1] + dp[2][i - 1]) % MOD;                        // 100
        dp[3][i] = ((dp[1][i - 1] + dp[2][i - 1]) % MOD + dp[4][i - 1]) % MOD; // 200
        dp[4][i] = (dp[0][i - 1] + dp[3][i - 1]) % MOD;                        // 500
    }
    // the final result is the sum of the total number of ways
    // for each starting bill
    long long res = 0;
    for(int i = 0; i < 5; ++i)
    {
        res += dp[i][n];
        delete dp[i];
    }
    res %= MOD;
    out << res;
    return 0;
}
