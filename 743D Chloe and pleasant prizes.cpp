/*
Problem credits: https://codeforces.com/contest/743/problem/D

Generous sponsors of the olympiad in which Chloe and Vladik took part allowed all the participants to choose a prize for them on their own. Christmas is coming, so sponsors decided to decorate the Christmas tree with their prizes.

They took n prizes for the contestants and wrote on each of them a unique id (integer from 1 to n). A gift i is characterized by integer ai - pleasantness of the gift. The pleasantness of the gift can be positive, negative or zero. Sponsors placed the gift 1 on the top of the tree. All the other gifts hung on a rope tied to some other gift so that each gift hung on the first gift, possibly with a sequence of ropes and another gifts. Formally, the gifts formed a rooted tree with n vertices.

The prize-giving procedure goes in the following way: the participants come to the tree one after another, choose any of the remaining gifts and cut the rope this prize hang on. Note that all the ropes which were used to hang other prizes on the chosen one are not cut. So the contestant gets the chosen gift as well as the all the gifts that hang on it, possibly with a sequence of ropes and another gifts.

Our friends, Chloe and Vladik, shared the first place on the olympiad and they will choose prizes at the same time! To keep themselves from fighting, they decided to choose two different gifts so that the sets of the gifts that hang on them with a sequence of ropes and another gifts don't intersect. In other words, there shouldn't be any gift that hang both on the gift chosen by Chloe and on the gift chosen by Vladik. From all of the possible variants they will choose such pair of prizes that the sum of pleasantness of all the gifts that they will take after cutting the ropes is as large as possible.

Print the maximum sum of pleasantness that Vladik and Chloe can get. If it is impossible for them to choose the gifts without fighting, print Impossible.

Solution:
    Every dfs call returns sum of its subtree and best subtree of it (inclusing itself).

    At every root, we pick the best 2 and update the ans with maximum of that sum.
*/

#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<vector<int>>gr;
vector<int>val;

ll ans = LLONG_MIN;
pair<ll, ll> dfs(int node, int par) {
    ll best1 = LLONG_MIN, best2 = LLONG_MIN;
    ll sum = val[node];
    for(int child: gr[node]) {
        if (child != par) {
            auto [child_sum, child_best] = dfs(child, node);
            sum += child_sum;
            if (child_best > best1) {
                best2 = best1;
                best1 = child_best;
            } else if (child_best > best2) {
                best2 = child_best;
            }
        }
    }
    if (best2 != LLONG_MIN) {
        ans = max(ans, best1 + best2);
    }
    return {sum, max({best1, sum})};
} 
int main() {
	int n;
	cin >> n;
	val.resize(n+1);
	for(int i = 1; i <= n; i++) cin >> val[i];
	gr.resize(n+1);
	for(int i = 1, u, v; i < n; i++) {
	    cin >> u >> v;
	    gr[u].push_back(v);
	    gr[v].push_back(u);
	}
	dfs(1, 0);
	if (ans == LLONG_MIN)
	    cout << " Impossible";
	else 
	    cout << ans;
}
