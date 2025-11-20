/*

You are given a rooted tree consisting of n vertices numbered from 1 to n. The root of the tree is a vertex number 1
A tree is a connected undirected graph with n-1 edges.

You are given m queries. The i-th query consists of the set of ki distinct vertices vi[1],vi[2],...,vi[ki]
. Your task is to say if there is a path from the root to some vertex u
 such that each of the given k vertices is either belongs to this path or has the distance 1 to some vertex of this path.

Input
The first line of the input contains two integers n
 and m
 (2<=n<=2.105
, 1<=m<=2.105
) - the number of vertices in the tree and the number of queries.

Each of the next n-1
 lines describes an edge of the tree. Edge i
 is denoted by two integers ui
 and vi
, the labels of vertices it connects (1<=ui,vi<=n,ui!=vi
).

It is guaranteed that the given edges form a tree.

The next m
 lines describe queries. The i-th line describes the i-th query and starts with the integer ki(1<=ki<=n) - the number of vertices in the current query. 
 Then ki integers follow: vi[1],vi[2],...,vi[ki] (1<=vi[j]<=n), where vi[j] is the j-th vertex of the i-th query.

It is guaranteed that all vertices in a single query are distinct.

It is guaranteed that the sum of ki does not exceed 2.105(sum(i)=1mki<=2.10^5).

Output
For each query, print the answer - "YES", if there is a path from the root to some vertex u
 such that each of the given k
 vertices is either belongs to this path or has the distance 1
 to some vertex of this path and "NO" otherwise.

 #Euler_tour #DFS
*/

/*Solution:
    vertices is either belongs to this path or has the distance 1 to some vertex of this path => means parents of the vertice to be on the path.

    We transform the vertices to its parent and pick the fartest node and check whether all the other nodes like between root and the node using tin and tout (Euler tour)
*/

#include<bits/stdc++.h>
using namespace std;
vector<int> tin, tout, parent, depth;
int timer = 0;
void dfs(int node, int par, vector<int> gr[]) {
    parent[node] = par;
    depth[node] = depth[par] + 1;
    tin[node] = timer++;
    for(int child: gr[node]) {
        if (parent[child] == -1)
            dfs(child, node, gr);
    }
    tout[node] = timer++;
}
int main() {
    int n, m;
    cin >> n >> m;
    n++;
    vector<int> gr[n];
    for(int i = 2; i< n; i++) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    tin = tout = parent = depth = vector<int>(n, -1);
    dfs(1, 0, gr);
    tout[0] = INT_MAX;
    while(m--) {
        int k;
        cin >> k;
        vector<int>v(k);
        int farthestNode = 0;
        for(int& i: v) {
            cin >> i;
            if(depth[farthestNode] < depth[i]) {
                farthestNode = i;
            }
            i = parent[i];
        }
        string ans = "YES";
        for(int i: v) {
            if(tin[i] > tin[farthestNode] || tout[i] < tout[farthestNode]) {
                ans = "NO";
                break;
            }
        }
        cout << ans << endl;
    }
}