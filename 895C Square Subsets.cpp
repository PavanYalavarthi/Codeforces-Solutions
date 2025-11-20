/*
Problem credits: https://codeforces.com/problemset/problem/895/c

Petya was late for the lesson too. The teacher gave him an additional task. For some array a Petya should find the number of different ways to select non-empty subset of elements from it in such a way that their product is equal to a square of some integer.

Two ways are considered different if sets of indexes of elements chosen by these ways are different.

Since the answer can be very large, you should find the answer modulo 10^9 + 7.

Input
First line contains one integer n (1 <= n <= 10^5) - the number of elements in the array.

Second line contains n integers ai (1 <= ai <= 70) - the elements of the array.

Output
Print one integer - the number of different ways to choose some elements so that their product is a square of a certain integer modulo 10^9 + 7.

*/

/*
Solution:
    we maintain msk[i] => set jth bit, if jth prime is odd power else unset, which helps us to say whether number is square number

    Now, we store freq of each element.

    We can pick even number of times nC0 + nc2+ .. = 2^(n-1) and mask doesnt change as we are picking even times

    or

    We can pick odd times, which is also 2^(n-1) possibilities and mask chnages to mask ^(msk[i])

    Basic case is, mask to be 0 to be a perfect square

*/

#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
vector<int>pow2(100001);
vector<int>primes({2, 3});
vector<int>msk(71);
unordered_map<int, int> freq;
vector<vector<int>> dp;
void isPrime(int i){
    for(int prime: primes) {
        if (i % prime == 0)
            return;
    }
    primes.push_back(i);
}
 
 
int helper(int index, int mask){
    if(index == 71) return (mask == 0);
    if(dp[index][mask] != -1) return dp[index][mask];
    int frequency = freq[index];
    if(frequency == 0) return helper(index + 1, mask);
    long long pickingEvenTimes = (1LL * pow2[frequency - 1] * helper(index + 1, mask)) % MOD; 
    long long pickingOddTimes = (1LL * pow2[frequency - 1] * helper(index + 1, mask ^ msk[index])) % MOD; 
    return dp[index][mask] = (pickingEvenTimes + pickingOddTimes) % MOD;
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    pow2[0] = 1;
    for (int i = 1; i < 100001; ++i)
        pow2[i] = (pow2[i - 1] * 2LL) % MOD;
    for(int i = 5; i <= 70; i+=6) {
        isPrime(i);
        isPrime(i+2);
    }
    msk[1] = 0;
    for(int i = 2; i < 71; i++) {
        for(int j = 0; j < primes.size(); j++) {
            if(i % primes[j] == 0) {
                msk[i] = (1 << j) ^ msk[i / primes[j]];
                break;
            }
        }
    }
    int n;
    cin >> n;
    for(int i =0, temp; i< n; i++) {
        cin >> temp;
        freq[temp]++;
    }
    dp.assign(71, vector<int>(1<<primes.size(), -1));
    cout << helper(1, 0) - 1;
    return 0;
}