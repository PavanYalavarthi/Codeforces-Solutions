/*

problem credits: https://codeforces.com/problemset/problem/1036/c

Let's call some positive integer classy if its decimal representation contains no more than 3
 non-zero digits. For example, numbers 4
, 200000
, 10203
 are classy and numbers 4231
, 102306
, 7277420000
 are not.

You are given a segment [L;R]
. Count the number of classy integers x
 such that L<=x<=R
.

Each testcase contains several segments, for each of them you are required to solve the problem separately.

Input
The first line contains a single integer T
 (1<=T<=104
) - the number of segments in a testcase.

Each of the next T
 lines contains two integers Li
 and Ri
 (1<=Li<=Ri<=1018
).

Output
Print T
 lines - the i
-th line should contain the number of classy integers on a segment [Li;Ri]
.
*/

/*

Solution:

Basic Digit DP template
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll dp[20][4][2];
int helper (int pos, int cnt, bool tight, string s) {
    if(pos == s.size()) return 1;
    if (dp[pos][cnt][tight] != -1) return dp[pos][cnt][tight];
    int last_digit = tight ? s[pos] - '0' : 9;
    int res = 0;
    for(int i = 0; i <= last_digit; i++) {
        int cur_cnt = cnt + (i > 0);
        if (cur_cnt <= 3) {
            res += helper(pos+1, cur_cnt, tight && (i == last_digit), s);
        }
    }
    return dp[pos][cnt][tight] = res;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        ll l, r, right_ans;
        cin >> l >> r;
        memset(dp, -1, sizeof(dp));
        right_ans = helper(0, 0, true,to_string(r));
        memset(dp, -1, sizeof(dp));
        cout <<  right_ans - helper(0, 0, true, to_string(l-1)) << endl;
    }
}