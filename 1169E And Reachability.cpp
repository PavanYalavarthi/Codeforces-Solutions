/*

Problem description: https://codeforces.com/problemset/problem/1169/e


Toad Pimple has an array of integers a1,a2,...,an.We say that y is reachable from x if x<y and there exists an integer array p such that x=p1<p2<...<pk=y, and api&api+1>0 for all integers i such that 1<=i<k.

Here & denotes the bitwise AND operation.

You are given q pairs of indices, check reachability for each of them.

Input
The first line contains two integers n and q (2<=n<=300000, 1<=q<=300000) - the number of integers in the array and the number of queries you need to answer.

The second line contains n space-separated integers a1,a2,...,an (0<=ai<=300000) - the given array.

The next q lines contain two integers each. The i-th of them contains two space-separated integers xi and yi (1<=xi<yi<=n). 

You need to check if yi is reachable from xi.

Output
Output q lines. In the i-th of them print "Shi" if yi is reachable from xi, otherwise, print "Fou".

#bitmasking_DP
*/

/*

Solution:

we keep go[i][k] = minimal index >= i that can be reached from i and has bit k set.

and check for every set bit of arr[r], can we reach it from arr[l]

*/
#include<bits/stdc++.h>
using namespace std;
#define LG 20
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n ,q;
    cin >> n >> q;
    vector<int> arr(n);
    for(int i =0 ; i< n; i++) cin >> arr[i];
    // go[i][k] = minimal index >= i that can be reached from i and has bit k set
    // use n as sentinel (out of bounds)
    vector<vector<int>>go(n+1, vector<int>(LG, n)); 
    // last[j] Store last index with jth bit set
    vector<int> last(LG, n);
    for(int i = n-1; i >= 0; i--) {
        for(int j = 0; j < LG; j++) {
            if(arr[i] & (1 << j)) {
                if(last[j] != n) {
                    // from i we can reach whatever last[j] could reach
                    for(int k = 0; k< LG; k++) {
                        go[i][k] = min(go[i][k], go[last[j]][k]);
                    }
                }
                go[i][j] = last[j] = i;
            }
        }
    }
    for(int i = 0; i<q; i++) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        bool ok = arr[l] & arr[r];
        for(int j =0; j < LG; j++) {
            if(arr[r] & (1 << j) && go[l][j] <= r)
                ok = true; 
        }
        cout << (ok ? "Shi\n" : "Fou\n");
    }
    return 0;
}