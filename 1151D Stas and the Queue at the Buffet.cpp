/*
Solution: expression boils down to j(ai - bi) - ai + n*bi

so, max value of  ai-bi needed to be at min j. greedy
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int>arr(n);
    long long sum = 0;
    for(int i =0, a, b; i < n; i++) {
        cin >> a >> b;
        arr[i] = a - b;
        sum += n * b - a;
    }
    sort(arr.begin(), arr.end(), greater<int>());
    for(int i = 1; i <= n; i++) {
        sum += i * arr[i-1];
    }
    cout << sum;
}
