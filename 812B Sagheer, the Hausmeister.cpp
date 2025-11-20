/*

Problem credits: https://codeforces.com/problemset/problem/812/b

Some people leave the lights at their workplaces on when they leave that is a waste of resources. As a hausmeister of DHBW, Sagheer waits till all students and professors leave the university building, then goes and turns all the lights off.

The building consists of n floors with stairs at the left and the right sides. Each floor has m rooms on the same line with a corridor that connects the left and right stairs passing by all the rooms. In other words, the building can be represented as a rectangle with n rows and m + 2 columns, where the first and the last columns represent the stairs, and the m columns in the middle represent rooms.

Sagheer is standing at the ground floor at the left stairs. He wants to turn all the lights off in such a way that he will not go upstairs until all lights in the floor he is standing at are off. Of course, Sagheer must visit a room to turn the light there off. It takes one minute for Sagheer to go to the next floor using stairs or to move from the current room/stairs to a neighboring room/stairs on the same floor. It takes no time for him to switch the light off in the room he is currently standing in. Help Sagheer find the minimum total time to turn off all the lights.

Note that Sagheer does not have to go back to his starting position, and he does not have to visit rooms where the light is already switched off.

Input
The first line contains two integers n and m (1 <= n <= 15 and 1 <= m <= 100) - the number of floors and the number of rooms in each floor, respectively.

The next n lines contains the building description. Each line contains a binary string of length m + 2 representing a floor (the left stairs, then m rooms, then the right stairs) where 0 indicates that the light is off and 1 indicates that the light is on. The floors are listed from top to bottom, so that the last line represents the ground floor.

The first and last characters of each string represent the left and the right stairs, respectively, so they are always 0.

Output
Print a single integer - the minimum total time needed to turn off all the lights.

#bit_manipulation
*/
/*
Solution:
    Need to store the left most and right most set cell in each row.

    We are trying all combinations of left and right for each row, 
    So, looping 0 -> 2 ^ (n - 1) where ith bit says Sagheer moves to 
        0 -> left on (i+1)th floor
        1 -> right on (i+1)th floor
    And get minimum of all combinations
*/

#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int>leftMost(n, m+1), rightMost(n, 0);
    int lastFloor = -1;
    string floorValue;
    for(int i = n-1, val; i >= 0; i--) {
        cin >> floorValue;
        for(int j = 0; j < floorValue.size(); j++) {
            if (floorValue[j] == '1') {
                rightMost[i] = j;
                leftMost[i] = min(leftMost[i], j);
                if(lastFloor == -1) lastFloor = i;
            }
        }
    }

    int ans = INT_MAX;
    for(int stairs = 0; stairs < 1 << (n - 1); stairs++) {
        int cur = 0, room = 0;
        for(int floor = 0; floor <= lastFloor; floor++) {
            if(room == 0) {
                room = rightMost[floor];
                cur += room;
            } else {
                room = leftMost[floor];
                cur += m + 1 - room;
            }
            if (floor == lastFloor) break;
            int nextRoom = (stairs & (1 << floor)) == 0 ? 0 : m +1;
            cur += abs(room - nextRoom) + 1;
            room = nextRoom;
        }
        ans = min(ans, cur);
    }
    cout << ans;
}