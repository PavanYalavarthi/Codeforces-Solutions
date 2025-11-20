/*
Problem credits: https://codeforces.com/problemset/problem/118/d

Gaius Julius Caesar, a famous general, loved to line up his soldiers. Overall the army had n1 footmen and n2 horsemen. Caesar thought that an arrangement is not beautiful if somewhere in the line there are strictly more that k1 footmen standing successively one after another, or there are strictly more than k2 horsemen standing successively one after another. Find the number of beautiful arrangements of the soldiers.

Note that all n1 + n2 warriors should be present at each arrangement. All footmen are considered indistinguishable among themselves. Similarly, all horsemen are considered indistinguishable among themselves.

Input
The only line contains four space-separated integers n1, n2, k1, k2 (1 <= n1, n2 <= 100, 1 <= k1, k2 <= 10) which represent how many footmen and horsemen there are and the largest acceptable number of footmen and horsemen standing in succession, correspondingly.

Output
Print the number of beautiful arrangements of the army modulo 100000000 (108). That is, print the number of such ways to line up the soldiers, that no more than k1 footmen stand successively, and no more than k2 horsemen stand successively.

#dp
*/

/*
Solution:
    DP solution. Code is self explainatory
*/
#include<bits/stdc++.h>
using namespace std;
#define MOD 100000000
int n1, n2, k1, k2;
int dp[101][101][11][11];
int helper(int n1, int n2, int continuous_n1, int continuous_n2) {
    if (n1 ==0 || n2 == 0) return (n1 <= k1 && n2 <= k2);
    if (dp[n1][n2][continuous_n1][continuous_n2] != -1) return dp[n1][n2][continuous_n1][continuous_n2];
    int ans = 0;
    if (n1 != 0 && continuous_n1 < k1) (ans += helper(n1 -1, n2, continuous_n1 + 1, 0)) %= MOD;
    if (n2 != 0 && continuous_n2 < k2) (ans +=helper(n1, n2 -1, 0, continuous_n2 +1)) %= MOD;
    return dp[n1][n2][continuous_n1][continuous_n2] = ans; 
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n1 >> n2 >> k1 >> k2;
    memset(dp, -1, sizeof(dp));
    cout << helper(n1, n2, 0, 0);
    return 0;
}