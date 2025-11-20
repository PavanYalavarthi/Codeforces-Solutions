/*

Problem Credits: https://codeforces.com/problemset/problem/1324/D

The next lecture in a high school requires two topics to be discussed. The i-th topic is interesting by ai units for the teacher and by bi units for the students.

The pair of topics i and j (i<j) is called good if ai+aj>bi+bj (i.e. it is more interesting for the teacher).

Your task is to find the number of good pairs of topics.

Input
The first line of the input contains one integer n(2<=n<=2.105) - the number of topics.

The second line of the input contains n integers a1,a2,...,an (1<=ai<=10^9), where ai is the interestingness of the i-th topic for the teacher.

The third line of the input contains n integers b1,b2,...,bn(1<=bi<=109), where bi is the interestingness of the i-th topic for the students.

Output
Print one integer - the number of good pairs of topic.

Examples
InputCopy
5
4 8 2 6 2
4 5 4 1 3
OutputCopy
7
InputCopy
4
1 3 2 4
1 3 2 4
OutputCopy
0

#pbds #inversion_count
*/

/*

Solution:

a[i]+ a[j] > b[i] + b[j] = > -(a[i] - b[i]) < (a[j] - b[j])

So using pbds, pushing -(a[i] - b[i]) and getting number of elements less than current index difference(SImilar to inversion count)
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0, temp; i < n; i++)  {
        cin >> temp;
        a[i] -= temp;
    }

    tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> orderedSet; // using less_equal to use it as multiset
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += orderedSet.order_of_key(a[i]);
        orderedSet.insert(-a[i]);
    }
    cout << ans;
}
