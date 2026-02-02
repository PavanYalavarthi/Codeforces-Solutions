/*

Problem credits: https://codeforces.com/contest/2173/problem/B

Niko is playing a game. Her score is denoted by an integer k which is 0 initially.

The game has n turns. On the i-th turn, Niko is given a red card with an integer a_i on it, as well as a blue card with an integer b_i on it. She must choose exactly one of the cards and update her score according to her choice:

If she chooses the red card, her score becomes k - a_i, where k is her score before the turn.

If she chooses the blue card, her score becomes b_i - k, where k is her score before the turn.

After this, the game proceeds to the next turn, or ends if it is the n-th turn.

Your task is to find the maximum possible score Niko can obtain at the end of the game.

*/

/*
Solution :
As we can also negate the score in future, we keep track of minimum and maximum possible score, and return max finally
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
 
int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int>r(n), b(n);
        for(int i =0; i< n; i++) cin >> r[i];
        for(int i =0; i < n; i++) cin >> b[i];
        int min_val = 0, max_value = 0;
        for(int i = 0; i < n; i++) {
            int temp_max = max(b[i] - min_val, max_value - r[i]);
            min_val = min(b[i] - max_value, min_val - r[i]);
            max_value = temp_max;
        }
        cout << max_value << endl;
    }
}