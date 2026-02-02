/*
Problem credits: https://codeforces.com/problemset/problem/598/E

You have a rectangular chocolate bar consisting of n x m single squares. You want to eat exactly k squares, so you may need to break the chocolate bar.

In one move, you can break any single rectangular piece of chocolate into two rectangular pieces. You can break only along lines between squares, either horizontally or vertically.

The cost of breaking is equal to the square of the break length.

For example, if you have a chocolate bar consisting of 2 x 3 unit squares, then:

You can break it horizontally and get two 1 x 3 pieces.
The cost of this break is 3^2 = 9.

Or you can break it vertically and get two pieces 2 x 1 and 2 x 2.
The cost of this break is 2^2 = 4.

For several given values of n, m, and k, find the minimum total cost of breaking.

You can eat exactly k squares of chocolate if after all breaking operations there exists a set of rectangular pieces whose total area is exactly k squares.

The remaining n * m - k squares do not need to form a single rectangular piece.

Solution:
    base case if k is 0 or k = x * y return 0;

    else, make horizontal partition from 1 .. x-1 and distribute k to either halfs

    DO the same for vertical and pick the best
*/

#include<bits/stdc++.h>
using namespace std;

int dp[31][31][51]{};

int helper(int x, int y, int k) {
    int &ans = dp[x][y][k];
    if (k == 0 || k == x*y || ans) return ans;
    ans = 1e9;
    for(int i = 1; i < x; i++) {
        for(int j = 0; j <= k; j++) {
            ans = min(ans, helper(i, y, j) + helper(x - i, y, k - j) + y * y);
        }
    }

    for(int i = 1; i < y; i++) {
        for(int j = 0; j <= k; j++) {
            ans = min(ans, helper(x, i, j) + helper(x, y - i, k - j) + x * x);
        }
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << helper(a, b, c) << endl;
    }
}