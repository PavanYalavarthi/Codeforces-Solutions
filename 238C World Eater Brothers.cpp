/*
Problem credits: https://codeforces.com/problemset/problem/238/C

You must have heard of the two brothers dreaming of ruling the world. With all their previous plans failed, this time they decided to cooperate with each other in order to rule the world.

As you know there are n countries in the world. These countries are connected by n - 1 directed roads. If you don't consider direction of the roads there is a unique path between every pair of countries in the world, passing through each road at most once.

Each of the brothers wants to establish his reign in some country, then it's possible for him to control the countries that can be reached from his country using directed roads.

The brothers can rule the world if there exists at most two countries for brothers to choose (and establish their reign in these countries) so that any other country is under control of at least one of them. In order to make this possible they want to change the direction of minimum number of roads. Your task is to calculate this minimum number of roads.

Solution:
    There will always be a point that is reachable from both the worlds. As without it grah becomes disconnected

    Now, dp[node] pick #reverse nodes if node is the root.

    Now, if node is choosed as centre point, we pick s and t from max 2 childs with max reverse nodes
    
    Final answer is min(dp[node] - mx1 - mx2) as rest of reverse nodes neeeded to be flipped
*/
#include<bits/stdc++.h>
using namespace std;
vector<vector<pair<int, bool>>>adj;
vector<int>dp;
void dfs(int node, int par) {
    for(auto& [child, isReverse] : adj[node]) {
        if (child != par) {
            dp[1] += isReverse;
            dfs(child, node);
        }
    }
}

void dfs2(int node, int par) {
    for(auto& [child, isReverse] : adj[node]) {
        if (child != par) {
            dp[child] = dp[node] + (isReverse ? -1 : 1);
            dfs2(child, node);
        }
    }
}

pair<int, int> dfs3(int node, int par) {
    int max1 =0, max2 = 0;
    for(auto& [child, isReverse] : adj[node]) {
        if (child != par) {
            auto [mx1, mx2] = dfs3(child, node);
            int val = mx1 + (isReverse ? 1 : -1);
            max2 = max(max2, val);
            if (max1 < max2) swap(max1, max2);
        }
    }
    return {max1, max2};
}
int main() {
    int n;
    cin >> n;
    adj.resize(n+1);
    for(int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back({v, false});
        adj[v].push_back({u, true});
    }
    dp.resize(n+1, 0);
    dfs(1, 0);
    dfs2(1, 0);
    int ans = n;
    for(int i = 1; i <= n; i++) {
        auto [mx1, mx2] = dfs3(i, 0);
        ans = min(ans, dp[i] - mx1 - mx2);
    }
    cout << ans;
}