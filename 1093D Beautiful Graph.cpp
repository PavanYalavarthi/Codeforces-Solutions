/*
Problem description: https://codeforces.com/problemset/problem/1093/d

You are given an undirected unweighted graph consisting of n
 vertices and m
 edges.

You have to write a number on each vertex of the graph. Each number should be 1
, 2
 or 3
. The graph becomes beautiful if for each edge the sum of numbers on vertices connected by this edge is odd.

Calculate the number of possible ways to write numbers 1
, 2
 and 3
 on vertices so the graph becomes beautiful. Since this number may be large, print it modulo 998244353
.

Note that you have to write exactly one number on each vertex.

The graph does not have any self-loops or multiple edges.

Input
The first line contains one integer t
 (1<=t<=3.105
) - the number of tests in the input.

The first line of each test contains two integers n
 and m
 (1<=n<=3.105,0<=m<=3.105
) - the number of vertices and the number of edges, respectively. Next m
 lines describe edges: i
-th line contains two integers ui
, vi
 (1<=ui,vi<=n;ui!=vi
) - indices of vertices connected by i
-th edge.

It is guaranteed that sigma(i)=1tn<=3.105
 and sigma(i)=1tm<=3.105
.

Output
For each test print one line, containing one integer - the number of possible ways to write numbers 1
, 2
, 3
 on the vertices of given graph so it becomes beautiful. Since answers may be large, print them modulo 998244353
.
*/

/*

Solution:

    SImple dfs setting parity to each node, when partity is 0 => cnt0++ else cnt1++

    We need to make sure child has differnt parity compared to parent as edge vertices sum needed to be odd.

    So, for 0-parity we can keep 1, 3 and 1-parity 2

    or viceversa

    So ans = 2^cnt0 + 2 ^ cnt1 for all components
*/
#include<bits/stdc++.h>
using namespace std;
#define MOD 998244353
int cnt1, cnt0;
vector<int> visited;

long long pow2 (int n) {
    long long ans = 1, base = 2;
    while (n > 0) {
        if (n & 1) ans = (ans * base) % MOD;
        base = (base * base) % MOD; 
        n >>= 1; 
    }
    return ans;
}
bool dfs(int node, vector<int> gr[], int parity) {
    visited[node] = parity;
    if (parity == 0) cnt0++;
    else cnt1++;
    for(int child: gr[node]) {
        if(visited[child] == parity || (visited[child] == -1 && !dfs(child, gr, 1 - parity)))
            return false;
    }
    return true;
}

long long solve() {
    int n, m;
    cin >> n >> m;
    vector<int> gr[n];
    while(m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    visited.assign(n, -1);
    long long ans = 1;
    for(int i = 0; i< n; i++) {
        if (visited[i] != -1) continue;
        cnt0 = 0, cnt1 =0;
        if (dfs(i, gr, false) == false)
            return 0;
        (ans *= (pow2(cnt0) + pow2(cnt1))) %= MOD;
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        cout << solve() << endl;
    }
    return 0;
}