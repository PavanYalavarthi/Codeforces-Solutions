/*
Problem credits: https://codeforces.com/contest/2060/problem/E

You are given two simple undirected graphs F and G, each having n vertices.

Graph F has m1 edges.

Graph G has m2 edges.

You may perform the following two types of operations on graph F any number of times:

Remove an edge
Choose two integers u and v (1 <= u, v <= n) such that there is an edge between u and v in F, and remove that edge from F.

Add an edge
Choose two integers u and v (1 <= u, v <= n) such that there is no edge between u and v in F, and add an edge between u and v in F.

Objective

Determine the minimum number of operations required so that for all pairs of vertices u and v (1 <= u, v <= n):

There exists a path from u to v in graph F if and only if there exists a path from u to v in graph G.

Solution:
    If G-comp of u and v are not same, needed to remove the edge so incremnting at that

    And if G-comp and f-comp of u are not same, incrementng the ans again
*/

#include <bits/stdc++.h>
using namespace std;
int n, res;
vector<vector<int>>F_gr, G_gr;
vector<int>F_comp, G_comp;

void G_dfs(int u, int c) {
    G_comp[u] = c;
    for(int v: G_gr[u]) {
        if (G_comp[v] == -1) {
            G_dfs(v, c);
        }
    }
}

void F_dfs(int u, int c) {
    F_comp[u] = c;
    for(int v: F_gr[u]) {
        if (F_comp[v] == -1) {
            if (G_comp[v] != G_comp[u]) res++;
            else F_dfs(v, c);
        }
    }
}

void read_graph(vector<vector<int>>& gr, int size) {
    for(int i = 0; i < size; i++) {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        n++;
        res = 0;
        int f_edges, g_edges;
        cin >> f_edges >> g_edges;
        F_gr.assign(n, {}), G_gr.assign(n, {});
        read_graph(F_gr, f_edges);
        read_graph(G_gr, g_edges);
        F_comp.assign(n, -1), G_comp.assign(n, -1);
        for(int i = 1; i < n; i++) {
            if (G_comp[i] == -1) {
                G_dfs(i, i);
            }
            if (F_comp[i] == -1) {
                F_dfs(i, i);
                if (G_comp[i] != F_comp[i]) res++;
            }
        }
        cout << res << endl;
    }
}
