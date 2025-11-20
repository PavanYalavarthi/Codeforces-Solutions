/*
Problem credits: https://codeforces.com/problemset/problem/1199/f

There is a square grid of size nxn. Some cells are colored in black, all others are colored in white. In one operation you can select some rectangle and color all its cells in white. It costs max(h,w) to color a rectangle of size hxw.
You are to make all cells white for minimum total cost.

Input
The first line contains a single integer n (1<=n<=50) - the size of the square grid.

Each of the next n lines contains a string of length n, consisting of characters '.' and '#'.
The j-th character of the i-th line is '#' if the cell with coordinates (i,j) is black, otherwise it is white.

Output
Print a single integer - the minimum total cost to paint all cells in white.

#dp
*/

/*
Solution:
    dividing rectangle height and width wise and re-using the subproblems
*/
#include<bits/stdc++.h>
using namespace std;
int dp[50][50][50][50];
int helper(vector<string>& board, int i1, int j1, int i2, int j2) {
    if(i1 == i2 && j1 == j2) return board[i1][j1] == '#';
    if (dp[i1][j1][i2][j2] != -1) return dp[i1][j1][i2][j2];
    int ans = max(i2 -i1, j2 -j1) + 1;
    for(int i = i1; i < i2; i++) {
        ans = min(ans, helper(board, i1, j1, i, j2) + helper(board, i+1, j1, i2, j2));
    }
    for(int j = j1; j < j2; j++) {
        ans = min(ans, helper(board, i1, j1, i2, j) + helper(board, i1, j+1, i2, j2));
    }
    return dp[i1][j1][i2][j2] = ans;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<string>board(n);
    for(int i = 0; i< n; i++)
        cin >> board[i];
    memset(dp, -1, sizeof(dp));
    cout << helper(board, 0,0, n-1, n-1);
    return 0;
}