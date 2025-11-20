/*

You are given a weighted tree consisting of n vertices. Recall that a tree is a connected graph without cycles. Vertices ui and vi are connected by an edge with weight wi
.

You are given m queries. The i-th query is given as an integer qi. In this query you need to calculate the number of pairs of vertices (u,v) (u<v) such that the maximum weight of an edge on a simple path between u and v doesn't exceed qi.

Input
The first line of the input contains two integers n and m (1<=n,m<=2.10^5) - the number of vertices in the tree and the number of queries.

Each of the next n-1 lines describes an edge of the tree. Edge i is denoted by three integers ui, vi and wi - the labels of vertices it connects (1<=ui,vi<=n
, ui!=vi) and the weight of the edge (1<=wi<=2.10^5). It is guaranteed that the given edges form a tree.

The last line of the input contains m integers q1,q2,...,qm (1<=qi<=2.105), where qi is the maximum weight of an edge in the i-th query.

Output
Print m integers - the answers to the queries. The i-th value should be equal to the number of pairs of vertices (u,v) (u<v) such that the maximum weight of an edge on a simple path between u and v doesn't exceed qi.

#dsu
*/

/*

Solution:

We sort the edges and add edges of specific weight consecutively and keep storing in map.

and map to value for specific weight

*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct DSU {
    vector<int> par, sz;

    DSU(int n) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        sz.assign(n, 1);
    }

    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    ll unite(int x, int y) {
        int u = find(x), v = find(y);
        ll ret_val = 1LL * sz[u] * sz[v];
        if (sz[u] > sz[v]) swap(u, v);
        par[u] = v;
        sz[v] += sz[u];
        return ret_val; 
    }

};

int main() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n+1);
    vector<vector<int>> edges;
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }
    sort(edges.begin(), edges.end());
    map<int, ll> mp;
    for(auto& edge: edges) {
        int w = edge[0], u = edge[1], v = edge[2];
        mp[w] += dsu.unite(u, v);
    }
    ll prev_val = 0;
    for(auto& entry: mp) {
        entry.second += prev_val;
        prev_val = entry.second;
    }
    while(m--) {
        int w;
        cin >> w;
        auto it = mp.upper_bound(w);
        cout << (it != mp.begin() ? (--it)->second : 0) << ' ';
    }
    return 0;
}