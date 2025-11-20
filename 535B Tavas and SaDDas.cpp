/*

Problem credits: https://codeforces.com/problemset/problem/535/B

Once again Tavas started eating coffee mix without water! Keione told him that it smells awful, but he didn't stop doing that. That's why Keione told his smart friend, SaDDas to punish him! SaDDas took Tavas' headphones and told him: "If you solve the following problem, I'll return it to you."


The problem is:

You are given a lucky number n. Lucky numbers are the positive integers whose decimal representations contain only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

If we sort all lucky numbers in increasing order, what's the 1-based index of n?

Tavas is not as smart as SaDDas, so he asked you to do him a favor and solve this problem so he can have his headphones back.

Input
The first and only line of input contains a lucky number n (1 <= n <= 109).

Output
Print the index of n among all lucky numbers.

Examples
InputCopy
4
OutputCopy
1
InputCopy
7
OutputCopy
2
InputCopy
77
OutputCopy
6

#bit_manipulation

*/

/*

Solution: 
    1. All numbers of size < len = 2 + 2^2 + 2^3 + .. + 2^(len -1) = 2^len - 2
    2. If the value is 7 at ith index, we need to take all combinations from i + 1 index to last as we have minimum numbers with 4 at ith index
*/

#include<bits/stdc++.h>
using namespace std;

int main() {
    string n;
    cin >> n;
    int len = n.size();
    int ans = (1 << len) - 2; // All numbers of size < len = 2 + 2^2 + 2^3 + .. + 2^(len -1) = 2^len - 2
    for(int i = 0;  i < len; i++) {
        // If the value is 7 at ith index, we need to take all combinations from i + 1 index to last as we have minimum numbers with 4 at ith index
        if (n[i] == '7') {
            ans += (1 << (len - i - 1));
        }
    }
    cout << ans + 1; // As rank is 1 based
}