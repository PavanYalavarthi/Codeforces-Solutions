/*
You are given a sequence a containing 2n integers. Let f(b) denote the number of distinct elements with an odd number of occurrences in sequence b.

You need to split the given array into two disjoint subsequences p and q, each of size n, such that f(p)+f(q) is maximized. Output the maximum value.


Solution:

If odd freq, it can contriibute only 1

If even freq and in form 4k +2, we can split into two equal 2k+1, to contribute 2;

else i.e., in form 4k, we needed to split 2k+1, 2k-1 to get contribution of 2. 
Above creates difference of 2, which can be compensated by odd or other number in form 4k

So, if #odd != 0 or #(in form 4k) is even => #odd + 2*(in form of 4k + 2) + 2 * (in form of 4k)

else we have penality of -2
*/

#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        unordered_map<int, int>mp;
        for(int i = 0, ele; i < 2 *n; i++) {
            cin >> ele;
            mp[ele]++;
        }

        int odd = 0, even_2mod4 = 0, even_0mod4 = 0;
        for(auto& [_, freq]: mp) {
            if(freq % 2) {
                odd++;
            } else if (freq % 4) {
                even_2mod4++;
            } else {
                even_0mod4++;
            }
        }
        int ans = odd + 2 * (even_2mod4 + even_0mod4);

        if (odd == 0 && even_0mod4 % 2 != 0) ans -= 2;
        cout << ans<< endl;
    }
}