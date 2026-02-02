/*

Problem credits: https://codeforces.com/contest/2173/problem/E/

One day, Sora and Shiro feel bored again, so they decide to settle it with a game.

At the beginning, Sora gives Shiro a permutation p1, p2, ..., pn of length n.
In each operation, Shiro may select two distinct indices x and y (1 <= x != y <= n).
Then Sora flips a fair coin:

With probability 0.5, Sora swaps p[x] and p[y].

With probability 0.5, Sora swaps p[n - x + 1] and p[n - y + 1].

After the operation, Sora replies with the actual pair of indices that were swapped, so that Shiro can update her local permutation accordingly.

Shiro's goal is to sort the permutation p in ascending order by using at most floor(2.5 * n + 800) operations. Help her!

A permutation of length n is an array consisting of n distinct integers from 1 to n in arbitrary order.
For example, [2,3,1,5,4] is a permutation, but [1,2,2] is not (2 appears twice), and [1,3,4] is not (n = 3 but element 4 appears).

Input
Each test contains multiple test cases.
The first line contains the number of test cases t (1 <= t <= 100).
The description of the test cases follows.

The first line of each test case contains a single integer n (1 <= n <= 4000) - the length of p.

The second line contains n integers p1, p2, ..., pn - the elements of p.

It is guaranteed that the sum of n over all test cases does not exceed 20000.
There are exactly 50 tests in this problem.

Interaction
For each test case, you can use at most floor(2.5 * n + 800) moves to sort the permutation p in ascending order.

To make a move, print a line:

? x y
(1 <= x != y <= n)

As a response, you will receive two integers u and v - the actual pair of indices that Sora swapped.
It is guaranteed that (u, v) is randomly chosen from:

(x, y)

(n - x + 1, n - y + 1)

each with equal probability.

To report that the permutation has been sorted, print a line containing only:

!

This does NOT count as a move.
Then continue to the next test case, or terminate if it was the last case.

After printing each query, you must flush the output.
Otherwise, you will get Idleness Limit Exceeded.

If at any time you read -1 instead of valid data, your program must exit immediately.
This means your solution made an invalid query or another mistake.
Failure to exit may result in an unpredictable verdict.

*/

/*

Solution:

We take edges as window and keep shrinking it when ends have required value 
*/
#include<bits/stdc++.h>
using namespace std;

void query(int i, int j, vector<int>& arr, vector<int>& index) {
    cout << "? " << i << " " << j << '\n';
    int x,y;
    cin >> x >> y;
    int val_x = arr[x], val_y=arr[y];
    swap(arr[x], arr[y]);
    index[val_x] = y;
    index[val_y] = x;
}

void solve() {
    int n;
    cin >> n;
    vector<int>arr(n+1), index(n+1);
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        index[arr[i]] = i;
    }

    int l = 1, r = n;

    while(l < r) {
        while(arr[l] != l || arr[r] != r) {
            int u = index[l], v = index[r];
            if (u == r || v == l) query(l, r, arr, index);      //If either l is at r or r is at l, swap l and r
            else if (u == l && v != r) query(v, r, arr, index); //If l has proper but r contains random, then placing random at its place
            else if (u != l && v == r) query(l, u, arr, index); //if r is proper but l contains random, then placing random at its place
            else if (l == v || r == u) query(l, r, arr, index); //If either l is at r or r is at l, swap l and r
            else query(l, u, arr, index);                       // Else l and r contains random, so swapping ele at l with its exact place
        }
        l++;
        r--;
    }
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
        cout << "!\n";
    }
}