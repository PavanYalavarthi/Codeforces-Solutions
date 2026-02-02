/*
Problem credits: https://codeforces.com/contest/2173/problem/C/

In the afterlife school, Kanade studies a peculiar number game.

She gives you two integers n and k, as well as an array a consisting of n integers, where 1 <= a[i] <= k holds.

For an integer set B = {b1, b2, ..., bm} where 1 <= b[i] <= k, we call it complete if and only if both of the following hold:

For each 1 <= i <= n, at least one divisor of a[i] is contained in B.

For each 1 <= j <= m, all positive multiples of b[j] which are less than or equal to k appear in the array a at least once.

You have to find a complete set B with minimum possible size, or determine that no such set exists.
*/

/*
Solution:
we need to pick the smallest element in the input and add to the ans and delete all its multiples as they need not be processed.

If any multiple. <= k is not present, then return -1;
*/

#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, k;
    cin >> n >> k;
    set<int>s;
    unordered_set<int> isPresent;
    for(int i = 0, ele; i < n; i++)  {
        cin >> ele;
        s.insert(ele);
        isPresent.insert(ele);
    }
    vector<int>ans;
    while(!s.empty()) {
        int ele = *s.begin();
        ans.push_back(ele);
        for(int i = ele; i <= k; i+= ele) {
            if (!isPresent.contains(i)) {
               cout << -1;
               return;
            }
            s.erase(i);
        }
    }
    cout << ans.size() << '\n';
    for(int ele: ans) cout << ele << " ";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
}
