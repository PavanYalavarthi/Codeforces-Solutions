#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll>arr;
int n, k;
 
bool check(ll x) {
    vector<int>dp(n, 1);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) <= x * (i - j)) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return (n - ans) <= k;
}
int main() {
    cin >> n >> k;
    arr.resize(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    int low = 0, high = 2e9+1;
    int ans = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout <<  ans;
}