/*
problem credits: https://codeforces.com/problemset/problem/682/C

Alyona decided to go on a diet and went to the forest to get some apples. There she unexpectedly found a magic rooted tree with root in the vertex 1, every vertex and every edge of which has a number written on.

The girl noticed that some of the tree's vertices are sad, so she decided to play with them. Let's call vertex v sad if there is a vertex u in subtree of vertex v such that dist(v, u) > au, where au is the number written on vertex u, dist(v, u) is the sum of the numbers written on the edges on the path from v to u.

Leaves of a tree are vertices connected to a single vertex by a single edge, but the root of a tree is a leaf if and only if the tree consists of a single vertex  - root.

Thus Alyona decided to remove some of tree leaves until there will be no any sad vertex left in the tree. What is the minimum number of leaves Alyona needs to remove?

Solution:
    dist(u, v) = dist(1, u) - dist(1, v) > a[u] => pick min of dist(1,v) and if dist(1,u) - minval > a[u] => add coutn of subtree to ansas all the nodes to be removed.
*/

#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<vector<pair<int, int>>>gr;
vector<int>val;
int ans = 0;

int count(int node, int par) {
    int cnt = 1;
    for(auto& [child, weight]: gr[node]) {
        if (child != par)
            cnt += count(child, node);
    }
    return cnt;
}

void dfs(int node, int par, ll dist, ll min_dist) {
    for(auto& [child, weight]: gr[node]) {
        if (child != par) {
            ll child_dist = dist + weight;
            if (child_dist > val[child] + min_dist) {
                ans += count(child, node);
            } else {
                dfs(child, node, dist + weight, min(min_dist, child_dist));
            }
            
        }   
    }
}

int main() {
	int n;
	cin >> n;
	gr.resize(n+1);
	val.resize(n+1);
	for(int i =1; i <= n; i++) cin >> val[i];
	for(int i = 2, u, w; i <= n; i++) {
	    cin >> u >> w;
	    gr[i].push_back({u, w});
	    gr[u].push_back({i, w});
	}
	dfs(1, 0, 0, 0);
	cout << ans;
}