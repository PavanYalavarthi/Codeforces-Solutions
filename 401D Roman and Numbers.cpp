/*
Problem credits: https://codeforces.com/problemset/problem/401/d

Roman is a young mathematician, very famous in Uzhland. Unfortunately, Sereja doesn't think so. To make Sereja change his mind, Roman is ready to solve any mathematical problem. After some thought, Sereja asked Roma to find, how many numbers are close to number n, modulo m.

Number x is considered close to number n modulo m, if:

it can be obtained by rearranging the digits of number n,
it doesn't have any leading zeroes,
the remainder after dividing number x by m equals 0.
Roman is a good mathematician, but the number of such numbers is too huge for him. So he asks you to help him.


Input
The first line contains two integers: n (1 <= n < 1018) and m (1 <= m <= 100).

Output
In a single line print a single integer - the number of numbers close to number n modulo m.

#Bit_masking_dp
*/

/*
Solution:
    Basic TSP template, where here we see index used.
*/
#include<bits/stdc++.h>
using namespace std;
long long final_mask;
int m, n;
string s;
vector<vector<long long>>dp;
long long helper(int mask, int remainder) {
    if(mask == final_mask) return remainder == 0;
    if(dp[mask][remainder] != -1) return dp[mask][remainder];
    long long ans = 0;
    for(int i = ((mask == 0) ? 1 : 0); i<= 9; i++) {
        for(int j = 0; j <n; j++) {
            if(mask & (1 << j) || s[j] != i + '0') continue;
            ans += helper(mask | (1 << j), ((remainder * 10) % m + i) % m);
            break;
        }
    }
    return dp[mask][remainder] = ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> s >> m;
    n = s.size();
    dp.assign(1 << n, vector<long long>(m, -1));
    final_mask = (1 << n) - 1;
    cout << helper(0, 0);
    return 0 ;
}