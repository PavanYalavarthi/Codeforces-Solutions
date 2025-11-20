/*

Problem credits: https://codeforces.com/problemset/problem/429/b

Summer is coming! It's time for Iahub and Iahubina to work out, as they both want to look hot at the beach. The gym where they go is a matrix a with n lines and m columns. Let number a[i][j] represents the calories burned by performing workout at the cell of gym in the i-th line and the j-th column.

Iahub starts with workout located at line 1 and column 1. He needs to finish with workout a[n][m]. After finishing workout a[i][j], he can go to workout a[i + 1][j] or a[i][j + 1]. Similarly, Iahubina starts with workout a[n][1] and she needs to finish with workout a[1][m]. After finishing workout from cell a[i][j], she goes to either a[i][j + 1] or a[i - 1][j].

There is one additional condition for their training. They have to meet in exactly one cell of gym. At that cell, none of them will work out. They will talk about fast exponentiation (pretty odd small talk) and then both of them will move to the next workout.

If a workout was done by either Iahub or Iahubina, it counts as total gain. Please plan a workout for Iahub and Iahubina such as total gain to be as big as possible. Note, that Iahub and Iahubina can perform workouts with different speed, so the number of cells that they use to reach meet cell may differs.

Input
The first line of the input contains two integers n and m (3 <= n, m <= 1000). Each of the next n lines contains m integers: j-th number from i-th line denotes element a[i][j] (0 <= a[i][j] <= 105).

Output
The output contains a single number - the maximum total gain possible.
*/

/*
Solution:
    We construct 4 DPs, 
        boy_start => boy starting from 0,0 to i, j 
        boy_end => boy starting from m, n to i, j
        girl_start => girl starting from m, 0 to i, j
        girl_end => girl starying from 0, n to i, j

    We have 2 cases at the cross point: (Due to only crossing at single cell)
        Boy coming from left and moving right and girl bottom to top
        or
        Boy coming from bottom to top and girl left to right

    We need to find max of the above cases, at every cell )(i, j)
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int m, n;
    cin >> m >> n;
    vector<vector<int>>grid(m, vector<int>(n));
    for(int i = 0; i < m; i++) {
        for(int j =0; j <n; j++) {
            cin >> grid[i][j];
        }
    }
    vector<vector<int>>boy_start, boy_end, girl_start, girl_end;
    boy_start = boy_end = girl_start = girl_end = vector<vector<int>>(m+2, vector<int>(n+2, 0));
    for(int i = 1; i<=m; i++) {
        for(int j = 1; j <= n; j++) {
            boy_start[i][j] = max(boy_start[i-1][j], boy_start[i][j-1]) + grid[i-1][j-1];
        }
    }
    for(int i = m; i>0; i--) {
        for(int j = n; j > 0; j--) {
            boy_end[i][j] = max(boy_end[i+1][j], boy_end[i][j+1]) + grid[i-1][j-1];
        }
    }
    for(int i = m; i>0; i--) {
        for(int j = 1; j <= n; j++) {
            girl_start[i][j] = max(girl_start[i+1][j], girl_start[i][j-1]) + grid[i-1][j-1];
        }
    }
    for(int i = 1; i<=m; i++) {
        for(int j = n; j > 0; j--) {
            girl_end[i][j] = max(girl_end[i][j +1], girl_end[i-1][j]) + grid[i-1][j-1];
        }
    }

    int ans = 0;
    for(int i =2; i< m; i++){
        for(int j = 2; j < n; j++) {
            ans = max({ans, 
                boy_start[i][j-1] + boy_end[i][j+1] + girl_start[i+1][j] + girl_end[i-1][j],
                boy_start[i-1][j] + boy_end[i+1][j] + girl_start[i][j-1] + girl_end[i][j+1]
            });
        }
    }
    cout << ans;
    return 0;
}