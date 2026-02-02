/*
Problem credits: https://codeforces.com/contest/2173/problem/A/

You have n classes today, numbered 1 to n.

The classes are described by a binary string s of length n.
A class i is important if and only if s[i] = '1'.
For each important class, you must stay awake and listen to it.

You are tired and want to sleep through as many classes as possible.
But falling asleep takes time:

If you listen to an important class i, then you cannot fall asleep for the next k classes.
That means you must also stay awake during classes:
i+1, i+2, .. , i+k (or until the end if fewer remain).

For classes that are not important, you may sleep unless the rule forces you to stay awake.

*/

/*
Solution: Keep track of index till we needed to wake up i.e., i + k and count number of indices that doesnt fall in this range
*/

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int indexTillAwake = -1;
        string s;
        cin >> s;
        int ans = 0;
        for(int i =0, ele; i < n; i++) {
            if (s[i] == '1') {
                indexTillAwake = i + k;
            } else if (i > indexTillAwake) {
                ans++;
            }
        }
        cout << ans << endl;
    }
}