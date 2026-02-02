/*

Problem credits: https://codeforces.com/problemset/problem/1665/C/

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a vertex v (different from the root) is the previous-to-v vertex on the shortest path from the root to v. Children of a vertex v are all vertices for which v is the parent.

You are given a rooted tree with n vertices. Vertex 1 is the root. Initially, all vertices are healthy.

Each second you perform two operations in this order:

Spreading: For each vertex v, if at least one child of v is infected, you may infect at most one other child of v of your choice (i.e., each vertex with >=1 infected child can infect at most one additional child during spreading).

Injection: You may choose any single healthy vertex (anywhere in the tree) and infect it.

These two operations repeat every second until the whole tree is infected. Find the minimal number of seconds needed to infect the whole tree.
*/

/*

Solution:
We keep track of number of immediate children for each node using hashmap

Now, no.of sibling set = no.of nodes that are parents as each comp (i.e., map size) + 1 (root to be counted)


And we need to see max sibling size to get infected.

Assuming max size is n, the infected node count goes 1 -> 2 -> 4 -> 8. So the time taken is 1 + ceil(log2(n))

We needed max of noOfSiblingSet, timeToInfectMaxChildrenSize
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
	    int n;
	    cin >> n;
	    unordered_map<int, int>mp;
        mp[0] = 1;
	    for(int i = 1, par; i < n; i++) {
	        cin >> par;
	        ++mp[par];
	    }
        vector<int>sibling_sz;
	    for(auto& [_, noOfChild]: mp) {
	       sibling_sz.push_back(noOfChild);
	    }
        sort(sibling_sz.begin(), sibling_sz.end(), greater<int>());
        int ans = 0;
        for(int i = 1; i <= sibling_sz.size(); i++) {
            
            ans = max(ans, i + (int)ceil(log2(sibling_sz[i-1])));
        }
        cout << ans << endl;
	}
}
