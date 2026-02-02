/*
problem credits: https://codeforces.com/problemset/problem/461/B

Appleman has a tree with n vertices. Some of the vertices (at least one) are colored black and other vertices are colored white.

Consider a set consisting of k (0 <= k < n) edges of Appleman's tree. If Appleman deletes these edges from the tree, then it will split into (k + 1) parts. Note, that each part will be a tree with colored vertices.

Now Appleman wonders, what is the number of sets splitting the tree in such a way that each resulting part will have exactly one black vertex? Find this number modulo 1000000007 (10^9 + 7).

Solution:
    To simply the case, we treat node is white and later calculate thing if it is black.

    Post processing child,
        #Whites = Whites of node * (whites + blacks) // As we needed to pick node white and any such that blacks in subtree edges will be broken
        #blacks = (One black to contain) (Whites of node * blacks) or (black and any) //As edge with black in child can be removed

    Now, if node becomes black, #whites become 0 as you can't give parent subtree with only white.
                                #Blacks is #Whites as root becomes black with single black
*/
#include<bits/stdc++.h>
#define MOD 1000000007
#define ll long long
using namespace std;
vector<vector<int>> gr;
vector<bool>isBlack;

/*
    return is
    first: #whites such that par - node edge can exists
    second: #blacks such taht only one black vertex exist
*/
pair<int, int> dfs(int node, int par) {
    ll waysOfWhite = 1, waysOfBlack = 0;

    for(int child: gr[node]) {
        if (child != par) {
            auto [whites, blacks] = dfs(child, node);
            int any = (whites + blacks)%MOD;
            ll newWhites = (waysOfWhite * any) %MOD;
            ll newBlacks = (waysOfWhite * blacks + waysOfBlack * any)% MOD;
            waysOfWhite = newWhites, waysOfBlack = newBlacks;
        }
    }

    if (isBlack[node]) {
        return {0, waysOfWhite};
    }
    return {waysOfWhite, waysOfBlack};
}

int main() {
    int n;
    cin >> n;
    gr.resize(n);
    for(int i = 1, u; i < n; i++) {
        cin >> u;
        gr[u].push_back(i);
        gr[i].push_back(u);
    }

    isBlack.resize(n);
    for(int i =0, color ; i < n; i++)  {
        cin >> color;
        isBlack[i] = (color == 1);
    }
    cout << dfs(0, -1).second;
}