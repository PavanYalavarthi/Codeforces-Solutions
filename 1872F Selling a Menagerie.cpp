/*

Problem credits: https://codeforces.com/problemset/problem/1872/F

You are the owner of a menagerie consisting of n animals numbered from 1 to n. However, maintaining the menagerie is quite expensive, so you have decided to sell it.

It is known that each animal is afraid of exactly one other animal. More precisely, animal i is afraid of animal a[i] where a[i] != i. Also, the cost of each animal is known; for animal i it is equal to c[i].

You will sell all your animals in some fixed order. Formally, you need to choose a permutation p1, p2, ..., pn, and sell animal p1 first, then animal p2, and so on, selling animal pn last.

When you sell animal i, there are two possible outcomes:

If animal a[i] was sold before animal i, you receive c[i] money for selling animal i.

If animal a[i] was NOT sold before animal i, you receive 2 * c[i] money for selling animal i. (Animals that are currently afraid are more valuable.)

Your task is to choose the order of selling the animals in order to maximize the total profit.

Solution: Use topo sort and in cycle sell the minimum cost one to get maximum profit.
*/


#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int>fears(n+1), cost(n+1), indegree(n+1, 0);
        for(int i =1; i <= n; i++) {
            cin >> fears[i];
            indegree[fears[i]]++;
        }
        
        for(int i =1; i <= n; i++) cin >> cost[i];
        queue<int>q;
        for(int i = 1; i <= n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        vector<int>ans(n);
        int k = 0;
        while(!q.empty()) {
            int ele = q.front();
            q.pop();
            ans[k++] = ele;
            indegree[fears[ele]]--;
            if (indegree[fears[ele]] == 0) {
                q.push(fears[ele]);
            }
        }
        
        for(int i = 1; i <= n; i++) {
            if (indegree[i] != 0) {
                int mini = i, next = fears[i];
                while(next != i) {
                    if (cost[next] < cost[mini]) {
                        mini = next;
                    }
                    next = fears[next];
                }
                int start = fears[mini];
                next = start;
                do {
                    ans[k++] = next;
                    indegree[next] = 0;
                    next = fears[next];
                } while(next != start);
            }
        }
        
        for(int i : ans) {
            cout << i << " ";
        }
        cout << endl;
    }
}
