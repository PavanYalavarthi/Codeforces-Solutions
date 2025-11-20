/*

Problem credits: https://codeforces.com/problemset/gymProblem/102152/D

A bitwise XOR takes two bit patterns of equal length and performs the logical exclusive OR operation on each pair of corresponding bits. The result in each position is 1
 if both bits are different (only one of them is 1
 and the other is 0
), but will be 0
 if both bits are the same (both are 0
 or both are 1
). For example, the bitwise XOR of the patterns 0101
 and 1100
 is 1001
.

In this problem, you are given 3
 binary strings of lengths 10
 digits such that all digits are either 0
 or 1
. You can swap any two digits in the same string infinitely, but you cannot swap two digits from two different strings.

Your task is to rearrange digits in the given strings in a way such that the bitwise XOR of the strings after rearranging their digits is as largest as possible. Can you?

Input
The first line contains an integer T
 (1<=T<=250
) specifying the number of test cases.

Each test case consists of 3
 lines each of which contains a binary string of length 10
 digits such that all digits are either 0
 or 1
.

Output
For each test, print a single line containing a binary string of length 10
 representing the largest value of bitwise XOR that can be optioned by rearranging digits in each string.

A binary string x
 is larger than a binary string y
 if after converting both strings to the decimal representation, the decimal value of string x
 is larger than the decimal value of string y
. For example, string "1100" is larger than string "0101" because its decimal value 12
, while the decimal value of string "0101" is 5
.

#dp
*/

/*
Solution:
    its self explainatory, xor becomes 1 << i when odd number is taken else, XOR doesnt change
*/
#include<bits/stdc++.h>
using namespace std;
int dp[10][11][11][11];
int helper(int i, int x1, int x2, int x3) {
    if (x1 < 0 || x2 < 0 || x3 < 0) return INT_MIN;
    if (i == -1) return (x1 == 0 && x2 ==0 && x3 == 0) ? 0 : INT_MIN;
    if(dp[i][x1][x2][x3] != -1) return dp[i][x1][x2][x3];
    return dp[i][x1][x2][x3] = max({
        helper(i-1, x1, x2, x3),
        (1 << i) + helper(i-1, x1 -1, x2, x3),
        (1 << i) + helper(i-1, x1, x2 -1, x3),
        (1 << i) + helper(i-1, x1, x2, x3-1),
        helper(i-1, x1-1, x2 -1, x3),
        helper(i-1, x1-1, x2, x3 -1),
        helper(i-1, x1, x2 -1, x3-1),
        (1 << i) + helper(i-1, x1 - 1, x2 -1, x3 - 1)
    });
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        int cnt[3];
        string temp;
        for(int i = 0;i<3; i++) {
            cin >> temp;
            cnt[i] = count(temp.begin(), temp.end(), '1');
        }
        memset(dp, -1, sizeof(dp));
        cout << bitset<10>(helper(temp.size() - 1, cnt[0], cnt[1], cnt[2])) << endl;
    }
    return 0;
}