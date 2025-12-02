/*

A game is being played which initially consists of n
 players. On fouls, the referee is allowed to award yellow and red cards. The total number of yellow cards y
 and red cards r
 awarded to players is known for the game.

There are 2
 ways a player can be suspended:

Receiving a red card.
Receiving 2
 yellow cards.
Once a player is suspended, they are removed from the game and can't receive any more cards. Determine the maximum number of players suspended from the game possible.


*/

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int t;
    cin >> t;
    while(t--) {
        int n, y, r;
        cin >> n >> y >> r;
        cout << min(n, y / 2 + r) << '\n';
    }
}