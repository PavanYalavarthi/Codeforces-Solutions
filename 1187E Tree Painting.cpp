/*

You are given a tree (an undirected connected acyclic graph) consisting of n vertices. You are playing a game on this tree.

Initially all vertices are white. On the first turn of the game you choose one vertex and paint it black. Then on each turn you choose a white vertex adjacent (connected by an edge) to any black vertex and paint it black.

Each time when you choose a vertex (even during the first turn), you gain the number of points equal to the size of the connected component consisting only of white vertices that contains the chosen vertex. The game ends when all vertices are painted black

Your task is to maximize the number of points you gain.

Input
The first line contains an integer n - the number of vertices in the tree (2 <= n <= 2,10^5).

Each of the next n-1 lines describes an edge of the tree. Edge i is denoted by two integers ui and vi, the indices of vertices it connects (1<= ui,v1 <= n, ui != vi).

It is guaranteed that the given edges form a tree.

Output
Print one integer - the maximum number of points you gain if you will play optimally.

#DP_on_trees #rerooting
*/

/*

Solution: 

Topic involves rerooting of trees.

When re-rooting, dp[node] becomes dp[node] + (par_res + size of par), size of par = n - size of node

and par_res becomes => dp[node] - dp[child] - sz[child], from dp[node] removing child controbution
*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long

int n;
ll ans = 0;
vector<ll>sz, dp;
void dfs1(int node, int par, vector<int> gr[]) {
    for(int child : gr[node]) {
        if (child != par) {
            dfs1(child, node, gr);
            sz[node] += sz[child];
            dp[node] += dp[child];
        }
    }
    dp[node] += sz[node];
}

void dfs2(int node, int par, ll par_res, vector<int> gr[]) {
    dp[node] += par_res + n - sz[node]; // Adding par_res + size of parent
    ans = max(ans, dp[node]);
    for(int child: gr[node]) {
        if (child != par) {
            dfs2(child, node, dp[node] - dp[child] - sz[child], gr); // In dp[node], removing dp[child] and sz[child]
        }
    }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    vector<int>gr[n];
    for(int i = 1, u, v; i <n ;i++) {
        cin >> u >> v;
        u--, v--;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    sz.assign(n, 1);
    dp.assign(n, 0);
    dfs1(0, -1, gr);
    dfs2(0, -1, 0, gr);
    cout << ans;
}