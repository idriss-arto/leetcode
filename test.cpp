// @lc code=start
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdio.h>
using namespace std;

void myprint(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(2) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // cout << "n = " << n << endl;

        int offset = 0;

        while (n - 2 * offset >= 2) {
            int cnt = n - 2 * offset - 1;
            // cout << "offset = " << offset << endl;
            // cout << "cnt = " << cnt << endl;
            while (cnt) {
                int nowi = offset;
                int nowj = offset + cnt - 1;
                int nexti = nowj;
                int nextj = n - 1 - nowi;

                int now = matrix[nowi][nowj];
                int tmp;

                for (int i = 1; i <= 4; i++) {
                    tmp = matrix[nexti][nextj];
                    matrix[nexti][nextj] = now;
                    now = tmp;
                    nowi = nexti;
                    nowj = nextj;
                    nexti = nowj;
                    nextj = n - 1 - nowi;

                    cout << "offset = " << offset << " cnt = " << cnt << " i = " << i << endl;
                    myprint(matrix);
                }

                cnt--;
            } 

            offset++;
        }
    }
};

int main() {
    Solution a;
    vector<vector<int>> nums = {{5,1,9,11}, {2,4,8,10}, {13,3,6,7}, {15,14,12,16}};
    myprint(nums);
    a.rotate(nums);
    myprint(nums);
    return 0;
}
// @lc code=end

