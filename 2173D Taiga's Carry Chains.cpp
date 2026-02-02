/*
Problem credits: https://codeforces.com/contest/2173/problem/D/

After classes at Ohashi High School, Ryuuji hands Taiga a positive integer n and sets a simple challenge.

They will play for exactly k moves. In a single move, Taiga chooses a non-negative integer l and sets

n = n + 2^l.

Ryuuji defines the score of one move as the number of binary carries that occur when adding 2^l to the current number in base 2. The total score is the sum of the scores over all k moves.

Taiga wants the total score to be as large as possible after k moves. What is the maximum total score she can achieve?
*/


/*

Solution:
Assume 2^l creates a carry of c and changes old to new => bitcount(new) = bitcount(old) - c + 1 (As carry bits will set 1 to 0, and the next bit will change from 0 to 1)

that results c = bitcount(old) - bitcount(new) + 1, for single step

For k steps => total_c = k + bitcount(old) - bitcount(final_new)

So, our goal is to minimize the final_new bitcount;

If k > zerocount => we can set all zeros to 1 and use extra 1 to convert it to single set bit and keep on getting carry from it. So, finalnew bitcount is 1

So, for k > zerocount, ans is. k + bitcount(old)  - 1

Now, here greedy doesnt work. As, instead of  you keep on seeing getting carry. we can use it to get longest seqence of 1 and use final 1 to get highest score
Even above thing cant be taken greedy because, we can also use bits to consume existing ones to get max score.

So, we use DP.

First we calculate cost of making i .. j as 1s and add extra 1 to get max score. cost[i][j] = #zeros[i..j] + 1.

Now dp[i][k] => max score from i .. 31, by using k operations.
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
void solve()
{
    ll n, k;
    cin >> n >> k; 
    vector<ll>bits;
    for (int i = 31; i >= 0; i--) {
        bits.push_back(((n >> i) & 1));
    }
    int bitcount = __builtin_popcount(n);
    ll zeroCount = 32 - bitcount;
    if (k > zeroCount) {
        cout << k + bitcount - 1 << '\n'; 
        return;
    }
    ll cost[32][32] {}, dp[33][33] {};
    for (int i = 0; i <= 31; i++) {
        ll zeroCount = 0;
        for(int j = i; j <= 31; j++) {
            zeroCount += (bits[j] == 0);
            cost[i][j] = zeroCount + 1;
        }
    }

    for(int i =31; i >= 0; i--) {
        for(int K = 1; K <= k; K++) {
            // We may not use any move at index i (i.e., dp[i][K -1]) or we may take max value from i+1 using k moves (i.e., dp[i+1][K])
            dp[i][K] = max(dp[i][K -1], dp[i+1][K]); 
            for(int j = i; j <= 31; j++) {
                if (cost[i][j] <= K) {
                    // If i to j cost is <= K, then j-i+1 score is received and we pick dp[j+1][k-cost[i][j]]
                    dp[i][K] = max(dp[i][K], (j - i +1) + dp[j+1][K - cost[i][j]]); 
                }
            }
        }
    }
    // Pick max score from 0 to 31, with k moves
    cout << dp[0][k] << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}