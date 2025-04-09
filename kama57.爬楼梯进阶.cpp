//* 动态规划（完全背包（求排列数））
//! 求排列数
#include<vector>
#include<iostream>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> dp(n+1, 0);
    
    dp[0] = 1;

    //* 滚动数组求排列数，必须外层遍历背包容量，内层遍历物品
    for (int i = 1; i <= n; i++) {                  //* 遍历背包容量
        for (int j = max(0, i-m); j < i; j++) {     //* 遍历物品
            dp[i] += dp[j];
        }
        /*
         * 以下写法更直观
        for (int j = 1; j <= m; j++) { // 遍历物品
            if (i - j >= 0) dp[i] += dp[i - j];
        }
        */
    }

    cout << dp[n] << endl;

    return dp[n];
}