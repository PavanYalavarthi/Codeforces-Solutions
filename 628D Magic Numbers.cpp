/*
Problem credits: https://codeforces.com/problemset/problem/628/d

Consider the decimal presentation of an integer. Let's call a number d-magic if digit d appears in decimal presentation of the number on even positions and nowhere else.

For example, the numbers 1727374, 17, 1 are 7-magic but 77, 7, 123, 34, 71 are not 7-magic. On the other hand the number 7 is 0-magic, 123 is 2-magic, 34 is 4-magic and 71 is 1-magic.

Find the number of d-magic numbers in the segment [a, b] that are multiple of m. Because the answer can be very huge you should only find its value modulo 109 + 7 (so you should find the remainder after dividing by 109 + 7).

Input
The first line contains two integers m, d (1 <= m <= 2000, 0 <= d <= 9) - the parameters from the problem statement.

The second line contains positive integer a in decimal presentation (without leading zeroes).

The third line contains positive integer b in decimal presentation (without leading zeroes).

It is guaranteed that a <= b, the number of digits in a and b are the same and don't exceed 2000.

Output
Print the only integer a - the remainder after dividing by 109 + 7 of the number of d-magic numbers in segment [a, b] that are multiple of m.

#digit_dp
*/

/*
Solution
Digit DP template, with inserting d if even else all other digits other than d
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
ll dp[2001][2000][2];
string l, r;
int m, d;
ll helper(int pos, int modM, bool tight, string& s) {
    if (pos == s.size()) return modM == 0;
    if (dp[pos][modM][tight] != -1) return dp[pos][modM][tight];
    int end_digit = tight ? s[pos] - '0' : 9;
    int ans = 0;
    for(int i = 0 ; i <= end_digit; i++) {
        if ((pos & 1) != 0 && i == d) {
            // If position is even (here its odd as pos started from 0), accepting only d
            (ans += helper(pos + 1, (modM*10 + i) % m, tight & (i == end_digit), s)) %= MOD;
            break;
        } else if ((pos & 1)  == 0 && i != d) {
            // in odd positions, accepting all other than d
            (ans += helper(pos + 1, (modM*10 + i) % m, tight & (i == end_digit), s)) %= MOD;
        }
    }
    return dp[pos][modM][tight] = ans;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> d;
    cin >> l >> r;
    int i = l.size() -1;
    while (i >= 0 && l[i] == '0') {
        l[i] = '9';
        i--;
    }
    l[i]--;
    memset(dp, -1, sizeof(dp));
    ll ans = helper(0, 0, true, r);
    memset(dp, -1, sizeof(dp));
    cout << (ans - helper(0, 0, true, l) + MOD) %MOD;
    return 0;
}