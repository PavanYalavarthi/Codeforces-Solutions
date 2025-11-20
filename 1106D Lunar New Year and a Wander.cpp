/*

problem description: https://codeforces.com/problemset/problem/1106/d

Lunar New Year is approaching, and Bob decides to take a wander in a nearby park.

The park can be represented as a connected graph with n
 nodes and m
 bidirectional edges. Initially Bob is at the node 1
 and he records 1
 on his notebook. He can wander from one node to another through those bidirectional edges. Whenever he visits a node not recorded on his notebook, he records it. After he visits all nodes at least once, he stops wandering, thus finally a permutation of nodes a1,a2,...,an
 is recorded.

Wandering is a boring thing, but solving problems is fascinating. Bob wants to know the lexicographically smallest sequence of nodes he can record while wandering. Bob thinks this problem is trivial, and he wants you to solve it.

A sequence x
 is lexicographically smaller than a sequence y
 if and only if one of the following holds:

x
 is a prefix of y
, but x!=y
 (this is impossible in this problem as all considered sequences have the same length);
in the first position where x
 and y
 differ, the sequence x
 has a smaller element than the corresponding element in y
.
Input
The first line contains two positive integers n
 and m
 (1<=n,m<=105
), denoting the number of nodes and edges, respectively.

The following m
 lines describe the bidirectional edges in the graph. The i
-th of these lines contains two integers ui
 and vi
 (1<=ui,vi<=n
), representing the nodes the i
-th edge connects.

Note that the graph can have multiple edges connecting the same two nodes and self-loops. It is guaranteed that the graph is connected.

Output
Output a line containing the lexicographically smallest sequence a1,a2,...,an
 Bob can record.

#dfs
*/

/*

Keep a set and keep pushing the vertices that can be visited.

and keep poping the s.begin() and append it to ans. so that it gives lexicographically smallest string

*/


#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    n++;
    vector<int>gr[n];
    while(m--) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    set<int>s;
    bool visited[n] = {false};
    vector<int>ans;
    ans.reserve(n - 1);
    s.insert(1);
    while(!s.empty()) {
        int node = *(s.begin());
        s.erase(s.begin());
        if (visited[node]) continue;
        ans.push_back(node);
        visited[node] = true;
        s.insert(gr[node].begin(), gr[node].end());
    }
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    return 0;
}