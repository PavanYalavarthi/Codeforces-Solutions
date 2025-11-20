/*
Problem credits: https://codeforces.com/problemset/problem/1151/b

Student Dima from Kremland has a matrix a
 of size nxm
 filled with non-negative integers.

He wants to select exactly one integer from each row of the matrix so that the bitwise exclusive OR of the selected integers is strictly greater than zero. Help him!

Formally, he wants to choose an integers sequence c1,c2,...,cn
 (1<=cj<=m
) so that the inequality a1,c1^a2,c2^...^an,cn>0
 holds, where ai,j
 is the matrix element from the i
-th row and the j
-th column.

Here x^y
 denotes the bitwise XOR operation of integers x
 and y
.

Input
The first line contains two integers n
 and m
 (1<=n,m<=500
) - the number of rows and the number of columns in the matrix a
.

Each of the next n
 lines contains m
 integers: the j
-th integer in the i
-th line is the j
-th element of the i
-th row of the matrix a
, i.e. ai,j
 (0<=ai,j<=1023
).

Output
If there is no way to choose one integer from each row so that their bitwise exclusive OR is strictly greater than zero, print "NIE".

Otherwise print "TAK" in the first line, in the next line print n
 integers c1,c2,...cn
 (1<=cj<=m
), so that the inequality a1,c1^a2,c2^...^an,cn>0
 holds.

If there is more than one possible answer, you may output any.

*/

/*
Solution: 
    XOR all the elements in first column. If it is not zero, outpout it

    else check any cell which is not equal to first column of the same row.
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>>arr(n, vector<int>(m));
    vector<int>ans(n, 1);
    int x = 0;
    for(int i =0; i< n; i++) {
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
        x ^= arr[i][0];
    }
    if(x == 0) {
        for(int i = 0; i< n; i++) {
            for(int j = 0; j < m; j++) {
                if(arr[i][j] != arr[i][0]) {
                    ans[i] = j +1;
                    i = n, x = 1;
                    break;
                }
            }
        }
    }
    if (x == 0) cout << "NIE";
    else {
        cout << "TAK\n";
        for(int i = 0; i< n; i++)
            cout << ans[i] << " ";
    }
    return 0;
}