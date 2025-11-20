/*

Problem credits : https://codeforces.com/problemset/problem/1114/d

You are given a line of n
 colored squares in a row, numbered from 1
 to n
 from left to right. The i
-th square initially has the color ci
.

Let's say, that two squares i
 and j
 belong to the same connected component if ci=cj
, and ci=ck
 for all k
 satisfying i<k<j
. In other words, all squares on the segment from i
 to j
 should have the same color.

For example, the line [3,3,3]
 has 1
 connected component, while the line [5,2,4,4]
 has 3
 connected components.

The game "flood fill" is played on the given line as follows:

At the start of the game you pick any starting square (this is not counted as a turn).
Then, in each game turn, change the color of the connected component containing the starting square to any other color.
Find the minimum number of turns needed for the entire line to be changed into a single color.

Input
The first line contains a single integer n
 (1<=n<=5000
) - the number of squares.

The second line contains integers c1,c2,...,cn
 (1<=ci<=5000
) - the initial colors of the squares.

Output
Print a single integer - the minimum number of the turns needed.

#dp

*/

/*
Solution:
    first we can remove consective unique elements.

    if (dp[i] == dp[j]) then as internal elements differ, these needed to change to internal so + 1
    else  min(dp[i+1][j], dp[i][j-1])
*/
#include<bits/stdc++.h>
using namespace std;

int helper(vector<int>& arr, int i, int j, vector<vector<int>>& dp) {
    if(i == j) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(arr[i] == arr[j]) return dp[i][j] = 1 + helper(arr, i+1, j-1, dp);
    return dp[i][j] = 1 + min(helper(arr, i+1, j, dp), helper(arr, i, j-1, dp)); 
} 
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
    vector<vector<int>>dp(arr.size(), vector<int>(arr.size(), -1));
    cout << helper(arr, 0, arr.size() -1, dp);
    return 0;
}