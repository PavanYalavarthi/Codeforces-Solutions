/*
Problem credits: https://codeforces.com/problemset/problem/1083/A

The Fair Nut is going to travel to the Tree Country, in which there are n
 cities. Most of the land of this country is covered by forest. Furthermore, the local road system forms a tree (connected graph without cycles). Nut wants to rent a car in the city u
 and go by a simple path to city v
. He hasn't determined the path, so it's time to do it. Note that chosen path can consist of only one vertex.

A filling station is located in every city. Because of strange law, Nut can buy only wi
 liters of gasoline in the i
-th city. We can assume, that he has infinite money. Each road has a length, and as soon as Nut drives through this road, the amount of gasoline decreases by length. Of course, Nut can't choose a path, which consists of roads, where he runs out of gasoline. He can buy gasoline in every visited city, even in the first and the last.

He also wants to find the maximum amount of gasoline that he can have at the end of the path. Help him: count it.

Solution:
    In dfs, we return whats the best +ve path fromm that node towards down.

    ans is max of gasoline[node] + best1 + best2 subtrees.
*/

#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<vector<pair<int, int>>> gr;
vector<int> val;
ll ans = 0;

ll dfs(int node, int par) {
    ll best1 = 0, best2 = 0;
    for(auto& [child, cost]: gr[node]) {
        if (child != par) {
            ll curr = max(dfs(child, node) - cost, 0ll);
            if (curr > best1) {
                best2 = best1;
                best1 = curr;
            } else if (curr > best2) {
                best2 = curr;
            }
        }
    }
    ans = max(ans, val[node] + best1 + best2);
    return (ll)val[node] + best1;
}

int main() {
	int n;
	cin >> n;
	val.resize(n+1);
	for(int i = 1; i <=n ; i++) cin >> val[i];
	gr.resize(n+1);
	for(int i = 1; i < n; i++) {
	    int u, v, c;
	    cin >> u >> v >> c;
	    gr[u].push_back({v, c});
	    gr[v].push_back({u, c});
	}
	dfs(1, 0);
	cout << ans;
}
