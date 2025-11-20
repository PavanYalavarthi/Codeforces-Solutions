/*
Problem credits: https://codeforces.com/problemset/problem/959/f


Ehab has an array a of n integers. He likes the bitwise-xor operation and he likes to bother Mahmoud so he came up with a problem. He gave Mahmoud q queries. In each of them, he gave Mahmoud 2 integers l and x, and asked him to find the number of subsequences of the first l elements of the array such that their bitwise-xor sum is x. Can you help Mahmoud answer the queries?

A subsequence can contain elements that are not neighboring.

Input
The first line contains integers n and q (1 <= n, q <= 105), the number of elements in the array and the number of queries.

The next line contains n integers a1, a2, ..., an (0 <= ai < 220), the elements of the array.

The next q lines, each contains integers l and x (1 <= l <= n, 0 <= x < 220), representing the queries.

Output
For each query, output its answer modulo 109 + 7 in a newline.

*/
#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int>arr(n+1), queries(q);
    for(int i =1; i<= n; i++) cin >> arr[i];
    unordered_map<int, vector<pair<int, int>>> mp;
    for(int i =0; i< q; i++) {
        int l, x;
        cin >> l >> x;
        mp[l].push_back({i, x});
    }
    
    int ans = 1;
    unordered_set<int> s;
    s.insert(0);
    for(int i = 1; i<= n; i++) {
        if(s.find(arr[i]) != s.end()) ans = (2 * ans) % MOD;
        else {
            vector<int> temp;
            for(int x : s) {
                temp.push_back(x ^ arr[i]);
            }
            s.insert(temp.begin(), temp.end());
        }
        for(auto &[index, x] : mp[i]) {
            queries[index] = s.find(x) != s.end() ? ans : 0;
        }
        mp.erase(i);
    }

    for(int i = 0; i< q; i++) {
        cout << queries[i] << '\n';
    }
    return 0;
}