/*
problem credits: 

You are given a sequence a1,a2,...,an, consisting of integers.

You can apply the following operation to this sequence: choose some integer x and move all elements equal to x either to the beginning, or to the end of a. 
Note that you have to move all these elements in one direction in one operation.

For example, if a=[2,1,3,1,1,3,2], you can get the following sequences in one operation (for convenience, denote elements equal to  as x-elements):

[1,1,1,2,3,3,2] if you move all 1-elements to the beginning;
[2,3,3,2,1,1,1] if you move all 1-elements to the end;
[2,2,1,3,1,1,3] if you move all 2-elements to the beginning;
[1,3,1,1,3,2,2] if you move all 2-elements to the end;
[3,3,2,1,1,1,2] if you move all 3-elements to the beginning;
[2,1,1,1,2,3,3] if you move all 3-elements to the end;

You have to determine the minimum number of such operations so that the sequence a becomes sorted in non-descending order. Non-descending order means that for all i from 2 to n
, the condition ai-1<=ai is satisfied.

Note that you have to answer q independent queries.

SOlution:
    We can observe we can chose the order of numbers to get moved to ends. So, which element at first doesnt matter

    We need to invert problem and see #consective elements that need not be moved.

    Pick max number and lessen from #unique numbers to get the ans
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
	    int n;
	    cin >> n;
	    vector<int>arr(n);
	    for(int i = 0; i < n; i++) cin >> arr[i];
	    vector<int>left(n+1, n), right(n+1, -1);
	    for(int i=0; i < n; i++) {
	        left[arr[i]] = min(left[arr[i]], i);
	        right[arr[i]] = max(right[arr[i]], i);
	    }
	    sort(arr.begin(), arr.end());
	    arr.erase(unique(arr.begin(), arr.end()), arr.end());
	    int sz = arr.size();
	    vector<int>dp(sz);
	    dp[sz-1] = 1;
	    for(int i = sz -2; i >= 0; i--) {
	        if (right[arr[i]] > left[arr[i+1]]) {
                // If right of arr[i] comes after left of arr[i+1], this cant be consective elemnts wthout modification
	            dp[i] = 1;
	        } else {
	            dp[i] = dp[i+1] + 1; //Else we continue the sequence by adding 1
	        }
	    }
	    cout << sz - *max_element(dp.begin(), dp.end()) << endl;
	}
}