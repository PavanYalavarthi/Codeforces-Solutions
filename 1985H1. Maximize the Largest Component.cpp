/*
Problem credits: https://codeforces.com/problemset/problem/1985/H1

Alex has a grid with n rows and m columns consisting of '.' and '#' characters.

A set of '#' cells forms a connected component if from any cell in this set, it is possible to reach any other cell in this set by only moving to another cell in the set that shares a common side.

The size of a connected component is the number of cells in the set.

In one operation, Alex selects any row r (1 <= r <= n) or any column c (1 <= c <= m), then sets every cell in row r or column c to be '#'.

Help Alex find the maximum possible size of the largest connected component of '#' cells that he can achieve after performing the operation at most once.

Input

The first line of the input contains a single integer t (1 <= t <= 10000), the number of test cases.

The first line of each test case contains two integers n and m (1 <= n * m <= 1000000), the number of rows and columns of the grid.

The next n lines each contain m characters. Each character is either '.' or '#'.

It is guaranteed that the sum of n * m over all test cases does not exceed 1000000.

Output

For each test case, output a single integer, the maximum possible size of a connected component of '#' cells that Alex can achieve.

Example

Input

6
1 1
.
4 2
..
#.
#.
.#
3 5
.#.#.
..#..
.#.#.
5 5
#...#
....#
#...#
.....
...##
6 6
.#..#.
#..#..
.#...#
#.#.#.
.#.##.
###..#
6 8
..#....#
.####.#.
###.#..#
.##.#.##
.#.##.##
#..##.#.


Output

1
6
9
11
15
30

Solution: expanding the box of the component for i, j 

and setting the sum to the edges of the box so that Can use sweepline to add them to respective row
*/

#include <bits/stdc++.h>
using namespace std;
int minR, maxR, minC, maxC, n, m, sz;
vector<vector<char>>arr;
vector<vector<bool>> visited;
vector<int>rCount, cCount;

void dfs(int i, int j) {
    if (i< 0 || j < 0 || i == n || j == m || visited[i][j] || arr[i][j] == '.')
        return;
    minC = min(j, minC);
    maxC = max(j, maxC);
    minR = min(i, minR);
    maxR = max(i, maxR);
    sz++;
    visited[i][j] = true;
    dfs(i-1, j);
    dfs(i, j-1);
    dfs(i+1, j);
    dfs(i, j+1);
}

int main() {
	int t;
	cin >> t;
	while (t--) {
	    cin >> n >> m;
	    vector<int>freeR(n,  0), freeC(m, 0);
	    arr.assign(n, vector<char>(m));
	    for(int i = 0; i < n; i++) {
	        for(int j = 0; j < m; j++) {
	            cin >> arr[i][j];
	            if (arr[i][j] == '.') {
	                freeR[i]++;
	                freeC[j]++;
	            }
	        }
	    }
	    
	    visited.assign(n, vector<bool>(m, false));
	    
	    rCount.assign(n+1, 0);
	    cCount.assign(m+1, 0);
	    
	    for(int i =0; i < n; i++) {
	        for(int j = 0; j < m; j++) {
	            if (visited[i][j] or arr[i][j] == '.') continue;
	            
	            sz = 0;
	            minC = m;
	            maxC = -1;
	            minR = n;
	            maxR = -1;
	            
	            dfs(i, j);
	            
                // adjacent cells also needed to be considered
	            minC = max(0, minC -1 );
                maxC = min(m-1, maxC + 1);
                minR = max(0, minR - 1);
                maxR = min(n-1, maxR + 1);
                
                rCount[minR] += sz;
                rCount[maxR+1] -= sz;
                cCount[minC] += sz;
                cCount[maxC + 1] -= sz;
	        }
	    }
	    
	    int ans = 0;
	    for(int i = 0; i < n; i++) {
	        rCount[i] += (i == 0 ? 0 : rCount[i-1]);
	        ans = max(ans, rCount[i] + freeR[i]);
	    }
	    
	    for(int i = 0; i < m; i++) {
	        cCount[i] += (i == 0 ? 0 : cCount[i-1]);
	        ans = max(ans, cCount[i] + freeC[i]);
	    }
	    
	    cout << ans << endl;
	    
	}

}
