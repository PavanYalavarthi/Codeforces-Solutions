/*
Problem credits: https://codeforces.com/problemset/problem/682/d

After returned from forest, Alyona started reading a book. She noticed strings s and t, lengths of which are n and m respectively. As usual, reading bored Alyona and she decided to pay her attention to strings s and t, which she considered very similar.

Alyona has her favourite positive integer k and because she is too small, k does not exceed 10. The girl wants now to choose k disjoint non-empty substrings of string s such that these strings appear as disjoint substrings of string t and in the same order as they do in string s. She is also interested in that their length is maximum possible among all variants.

Formally, Alyona wants to find a sequence of k non-empty strings p1, p2, p3, ..., pk satisfying following conditions:

s can be represented as concatenation a1p1a2p2... akpkak + 1, where a1, a2, ..., ak + 1 is a sequence of arbitrary strings (some of them may be possibly empty);
t can be represented as concatenation b1p1b2p2... bkpkbk + 1, where b1, b2, ..., bk + 1 is a sequence of arbitrary strings (some of them may be possibly empty);
sum of the lengths of strings in sequence is maximum possible.
Please help Alyona solve this complicated problem and find at least the sum of the lengths of the strings in a desired sequence.

A substring of a string is a subsequence of consecutive characters of the string.

Input
In the first line of the input three integers n, m, k (1 <= n, m <= 1000, 1 <= k <= 10) are given - the length of the string s, the length of the string t and Alyona's favourite number respectively.

The second line of the input contains string s, consisting of lowercase English letters.

The third line of the input contains string t, consisting of lowercase English letters.

Output
In the only line print the only non-negative integer - the sum of the lengths of the strings in a desired sequence.

It is guaranteed, that at least one desired sequence exists.

#DP
*/

/*
Solution:
    Dp[i][j] = 
        max {
            dp[i+1][j] //Skipping ith charecter
            dp[i][j+1] //Skiiping jth char
            if (s[i] == s[j]) {
                1+ dp[i+1][j+1] // When picked
            }
*/
#include<bits/stdc++.h>
using namespace std;
string s, t;
int dp[1000][1000][10][2];
int helper(int i, int j, int k, bool doContinue) {
    if (i == s.size() or j == t.size() or k == 0) return (k == 0) ? 0 : INT_MIN;
    if(dp[i][j][k -1][doContinue] != -1) return dp[i][j][k -1][doContinue];
    int ans = INT_MIN;
    if (s[i] == t[j]) // If equal, we can pick and continue or we can pick and end the sequence. In both cases 1 will be added.
        ans = max({ans, 1 + helper(i +1, j +1, k, true), 1 + helper(i +1, j +1, k-1, false)});
    ans = max({ans, helper(i + 1, j, k - doContinue, false), helper(i, j+1, k- doContinue, false)});
    return dp[i][j][k -1][doContinue] = ans;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int m, n, k;
    cin >> m >> n >> k;
    cin >> s >> t;
    memset(dp, -1,  sizeof(dp));
    cout << helper(0, 0, k, false);
    return 0;
}