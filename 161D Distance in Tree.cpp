/*
problem credits: https://codeforces.com/contest/161/problem/D

A tree is a connected graph that doesn't contain any cycles.

The distance between two vertices of a tree is the length (in edges) of the shortest path between these vertices.

You are given a tree with n vertices and a positive number k. Find the number of distinct pairs of the vertices which have a distance of exactly k between them. Note that pairs (v, u) and (u, v) are considered to be the same pair.

Solution:
    Keep track on #nodes from given node who's distance from node is j (j => 0 .. k)

    Ans ans is i distance from node and k - i - 1 from its child. Count the combination.

    Update nodes combination as dist[i] += child_dist[i-1]; as one edge between node and child exist
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, k;
ll ans = 0;

vector<vector<int>> gr;

vector<ll> dfs(int node, int par) {
    vector<ll>dist(k+1, 0);
    dist[0] = 1;
    for(int child: gr[node]) {
        if (child != par) {
            vector<ll> child_dist = dfs(child, node);
            for(int i = 0; i < k; i++) {
                ans += dist[i] * child_dist[k - i - 1];
            }
            for(int i = 1; i <= k; i++) {
                dist[i] += child_dist[i-1];
            }
        }
    }
    return dist;
} 

int main() {
	cin >> n >> k;
	gr.resize(n+1);
	for(int i = 1, u, v; i < n; i++) {
	    cin >> u >> v;
	    gr[u].push_back(v);
	    gr[v].push_back(u);
	}
	dfs(1, 0);
	cout << ans;
}