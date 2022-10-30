#include <bits/stdc++.h>
using namespace std;
ifstream in("in");
ofstream out("out");

int firstUppercasePos(string s, char upper)
{
    for(int i = 0; s[i] != '\0'; ++i)
    {
        if(s[i] == upper) return i;
        if(s[i] >= 'A' && s[i] <= 'Z')
            return -1;
    }
    return -1;
}
int firstLowercasePos(string s, char upper)
{
    for(int i = 0; s[i] != '\0'; ++i)
    {
        if(s[i] == upper + 32) return i;
        if(s[i] >= 'A' && s[i] <= 'Z')
            return -1;
    }
    return -1;
}
bool solution(string s1, string s2)
{
    if(s2[0] == '\0')
    {
        // return true;
        for(int i = 0; s1[i] != '\0'; ++i)
            if(s1[i] >= 'A' && s1[i] <= 'Z')
                return false;
        return true;
    }
    bool sol = false;
    int pos = firstUppercasePos(s1, s2[0]);
    if(pos != -1)
    {
        sol = solution(&s1[pos + 1], &s2[1]);
    }
    if(!sol)
    {
        pos = firstLowercasePos(s1, s2[0]);
        if(pos != -1)
        {
            sol = solution(&s1[pos + 1], &s2[1]);
        }
    }
    return sol;
}

int main()
{
    int nrq;
    in >> nrq;
    string s1, s2;
    bool sol;
    for(int q = 0; q < nrq; ++q)
    {
        in >> s1 >> s2;
        sol = solution(s1, s2);
        if(sol) out << "YES\n";
        else out << "NO\n";
    }

    return 0;
}
