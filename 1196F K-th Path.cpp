/*

You are given a connected undirected weighted graph consisting of n vertices and m edges.

You need to print the k-th smallest shortest path in this graph (paths from the vertex to itself are not counted, paths from i to j and from j to i are counted as one).

More formally, if d is the matrix of shortest paths, where di,j is the length of the shortest path between vertices i and j (1<=i<j<=n), then you need to print the k-th element in the sorted array consisting of all di,j, where 1<=i<j<=n.

Input
The first line of the input contains three integers n,m and k (2<=n<=2.10^5, n-1<=m<=min(n(n-1)2,2.10^5), 1<=k<=min(n(n-1)2,400) - 
the number of vertices in the graph, the number of edges in the graph and the value of k, correspondingly.

Then m lines follow, each containing three integers x, y and w (1<=x,y<=n, 1<=w<=109, x!=y) denoting an edge between vertices x and y of weight w.

It is guaranteed that the given graph is connected (there is a path between any pair of vertices), there are no self-loops (edges connecting the vertex with itself) and multiple edges (for each pair of vertices x and y, there is at most one edge between this pair of vertices in the graph).

Output
Print one integer - the length of the k-th smallest shortest path in the given graph (paths from the vertex to itself are not counted, paths from i to j and from j to i are counted as one).

#Floyd_warshall
*/

/*
Solution:
    As k max is 400, pick min(m, k) edges sorted. and run floyd warshall algo on the edges list and sort the distance between pairs and get k-1 th edge

*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF64 = 1e15;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<array<int,3>> edges(m); // {w, u, v}
    for (int i = 0; i < m; i++) {
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
    }
    sort(edges.begin(), edges.end());

    vector<int> vertices;
    int minEdges = min(k, m);
    for (int i = 0; i < minEdges; i++) {
        vertices.push_back(edges[i][1]);
        vertices.push_back(edges[i][2]);
    }
    sort(vertices.begin(), vertices.end());
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

    int noOfVertices = vertices.size();
    vector<vector<ll>> dist(noOfVertices, vector<ll>(noOfVertices, INF64));
    for (int i = 0; i < noOfVertices; i++) dist[i][i] = 0;

    for (int i = 0; i < minEdges; i++) {
        int x = lower_bound(vertices.begin(), vertices.end(), edges[i][1]) - vertices.begin();
        int y = lower_bound(vertices.begin(), vertices.end(), edges[i][2]) - vertices.begin();
        dist[x][y] = dist[y][x] = edges[i][0];
    }

    // full Floyd-Warshall
    for (int k = 0; k < noOfVertices; k++) {
        for (int i = 0; i < noOfVertices; i++) {
            for (int j = 0; j < noOfVertices; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    vector<ll> res;
    for (int i = 0; i < noOfVertices; i++) {
        for (int j = i + 1; j < noOfVertices; j++) {
            if (dist[i][j] < INF64) res.push_back(dist[i][j]);
        }
    }

    sort(res.begin(), res.end());
    cout << res[k - 1] << "\n";
}
