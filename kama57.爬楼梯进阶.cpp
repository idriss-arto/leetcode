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
        //* 这个写法是最后一步之前爬了j层，现在最后一步要从j爬到i，显然j的范围是{max(0,i-m), i-1}
        for (int j = max(0, i-m); j < i; j++) {     //* 遍历物品
            dp[i] += dp[j];
        }
        /*
         * 以下写法更直观
         * 这个写法是确定最后一步爬j层，看前面i-j层怎么爬
        for (int j = 1; j <= m; j++) { // 遍历物品
            if (i - j >= 0) dp[i] += dp[i - j];
        }
        */
    }

    cout << dp[n] << endl;

    return dp[n];
}