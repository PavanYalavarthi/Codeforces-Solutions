/*
Problem credits: https://codeforces.com/problemset/problem/459/d

Parmida is a clever girl and she wants to participate in Olympiads this year. Of course she wants her partner to be clever too (although he's not)! Parmida has prepared the following test problem for Pashmak.

There is a sequence a that consists of n integers a1, a2, ..., an. Let's denote f(l, r, x) the number of indices k such that: l <= k <= r and ak = x. His task is to calculate the number of pairs of indicies i, j (1 <= i < j <= n) such that f(1, i, ai) > f(j, n, aj).

Help Pashmak with the test.

Input
The first line of the input contains an integer n (1 <= n <= 10^6). The second line contains n space-separated integers a1, a2, ..., an (1 <= ai <= 10^9).

Output
Print a single integer - the answer to the problem.

#fenwick_tree
*/

/*

We precompute:

prefix[i] = count of a[i] up to index i
suffix[i] = count of a[i] from index i to n

This reduces the problem to:

For each position i, count how many positions j > i have suffix[j] < prefix[i]. This is a perfect use case for a Fenwick Tree (Binary Indexed Tree).


*/
#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> bit;
    BIT(int n) { bit.assign(n + 1, 0); }

    void update(int idx, int val) {
        for (; idx < bit.size(); idx += idx & -idx)
            bit[idx] += val;
    }

    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx)
            sum += bit[idx];
        return sum;
    }
};

int main() {
    int n;
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vector<int> v(n), prefix(n), suffix(n);
    map<int, int> freq;
    // Getting prefix frequency and suffix frequency
    for (int i =0; i< n; i++)  {
        cin >> v[i];
        prefix[i] = ++freq[v[i]];
    }
    freq.clear();
    int maxFreq = 0;
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = ++freq[v[i]];
        maxFreq = max(maxFreq, suffix[i]);
    }

    BIT bit(maxFreq);
    long long ans = 0;
    // iterate from right to left
    for (int i = n - 1; i >= 0; i--) {
        ans += bit.query(prefix[i] - 1);  // counts how many suffixSum < current prefixSum
        bit.update(suffix[i], 1);
    }
    cout << ans << '\n';
    return 0;
}
