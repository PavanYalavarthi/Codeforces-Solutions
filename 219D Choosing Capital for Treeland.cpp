/*
Problem credits: https://codeforces.com/contest/219/problem/D

The country Treeland consists of n cities, some pairs of them are connected with unidirectional roads. Overall there are n - 1 roads in the country. We know that if we don't take the direction of the roads into consideration, we can get from any city to any other one.

The council of the elders has recently decided to choose the capital of Treeland. Of course it should be a city of this country. The council is supposed to meet in the capital and regularly move from the capital to other cities (at this stage nobody is thinking about getting back to the capital from these cities). For that reason if city a is chosen a capital, then all roads must be oriented so that if we move along them, we can get from city a to any other city. For that some roads may have to be inversed.

Help the elders to choose the capital so that they have to inverse the minimum number of roads in the country.

Solution:
    In first dfs, from vertex 1 , count #edges that are reverse in direction.
    And in next dfs, if edge is normal from node to child, we need to add 1 to dp[node] as this needed to be flipped
    And if reverse, -1 as this is unnessarily added to dp[node]

    dp[i] => # reverse nodes if i is root
#dp_on_trees
*/

#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int>>>adj;
vector<int>dp;
int n;

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
int main() {
    cin >> n;
    adj.resize(n+1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, false});
        adj[v].push_back({u, true});
    }
    dp.resize(n+1, 0);
    dfs(1, 0);
    dfs2(1, 0);
    int mn = INT_MAX;
    vector<int>ans;
    for(int i = 1; i <= n; i++) {
        if (dp[i] < mn) {
            mn = dp[i];
            ans.clear();
            ans.push_back(i);
        } else if (dp[i] == mn) {
            ans.push_back(i);
        }
    }
    cout << mn << endl;
    for(int i : ans) cout << i << " ";
}
