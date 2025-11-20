/*

Problem description: https://codeforces.com/problemset/problem/455/a

Alex doesn't like boredom. That's why whenever he gets bored, he comes up with games. One long winter evening he came up with a game and decided to play it.

Given a sequence a consisting of n integers. The player can make several steps. In a single step he can choose an element of the sequence (let's denote it ak) and delete it, at that all elements equal to ak + 1 and ak - 1 also must be deleted from the sequence. That step brings ak points to the player.

Alex is a perfectionist, so he decided to get as many points as possible. Help him.

Input
The first line contains integer n (1<=n<=105) that shows how many numbers are in Alex's sequence.

The second line contains n integers a1, a2, ..., an (1<=ai<=105).

Output
Print a single integer - the maximum number of points that Alex can earn.
*/

/*

Solution:
Get freq of each element,

and keep max of(
    key * freq + prev2,  if key -1 present
    else key * freq + prev1
)
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<uint64_t, uint64_t> mp;
    uint64_t temp;
    for(int i=0; i< n; i++) {
        cin >> temp;
        mp[temp]++;
    }
    uint64_t ans = 0, prev1 =0, prev2 =0;
    for(auto &[key, freq] : mp) {
        if (mp.count(key -1) != 0)
            temp = max(key * freq + prev2, prev1);
        else
            temp = key * freq + prev1;
        prev2 = prev1;
        prev1 = temp;
    }
    cout << prev1;
    return 0;
}