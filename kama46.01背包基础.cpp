//* 动态规划

/*
 * 给定背包容量，装满背包的最大价值是多少
*/

/*
 * 1.确定dp数组（dp table）以及下标的含义
 * dp[i][j] 表示从下标为[0-i]的物品里任意取，放进容量为j的背包，价值总和最大是多少。
 * 
 ! 2.确定递推公式
 * 不放物品i：背包容量为j，里面不放物品i的最大价值是dp[i - 1][j]。
 * 放物品i：背包空出物品i的容量后，背包容量为j - weight[i]，dp[i - 1][j - weight[i]] 为背包容量为j - weight[i]且不放物品i的最大价值，
 * 那么dp[i - 1][j - weight[i]] + value[i] （物品i的价值），就是背包放物品i得到的最大价值
 * 递归公式： dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
 * 
 * 3.dp数组如何初始化
 * 如果背包容量j为0的话，即dp[i][0]，无论是选取哪些物品，背包价值总和一定为0。
 * 从状态转移方程可以看出，i 是由 i-1 推导出来，那么i为0的时候就一定要初始化。
 * 当 j < weight[0] 的时候，dp[0][j] 应该是 0，因为背包容量比编号0的物品重量还小。
 * 当 j >= weight[0] 时，dp[0][j] 应该是value[0]，因为背包容量放足够放编号0物品。
 *
 * 4.确定遍历顺序
 * dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]); 
 * 递归公式中可以看出dp[i][j]是靠dp[i-1][j]和dp[i - 1][j - weight[i]]推导出来的。
 * dp[i-1][j]和dp[i - 1][j - weight[i]] 都在dp[i][j]的左上角方向（包括正上方向）
 * 
 * 5.举例推导dp数组
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, bagweight;               //* bagweight代表行李箱空间

    cin >> n >> bagweight;

    vector<int> weight(n, 0);       //* 存储每件物品所占空间
    vector<int> value(n, 0);        //* 存储每件物品价值

    for(int i = 0; i < n; ++i) {
        cin >> weight[i];
    }
    for(int j = 0; j < n; ++j) {
        cin >> value[j];
    }
    //* dp数组, dp[i][j]代表行李箱空间为j的情况下,从下标为[0, i]的物品里面任意取,能达到的最大价值
    vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

    //* 初始化, 因为需要用到dp[i - 1]的值
    //* j < weight[0]已在上方被初始化为0
    //* j >= weight[0]的值就初始化为value[0]
    for (int j = weight[0]; j <= bagweight; j++) {
        dp[0][j] = value[0];
    }

    for(int i = 1; i < weight.size(); i++) {        //* 遍历科研物品
        for(int j = 0; j <= bagweight; j++) {       //* 遍历行李箱容量
            if (j < weight[i]) dp[i][j] = dp[i - 1][j];     //! 如果装不下这个物品,那么就继承dp[i - 1][j]的值
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
            }
        }
    }
    cout << dp[n - 1][bagweight] << endl;

    return 0;
}

/*
 * 滚动数组
 * int main() {
 *    // 读取 M 和 N
 *    int M, N;
 *    cin >> M >> N;

 *    vector<int> costs(M);
 *    vector<int> values(M);

 *    for (int i = 0; i < M; i++) {
 *        cin >> costs[i];
 *    }
 *    for (int j = 0; j < M; j++) {
 *        cin >> values[j];
 *    }

 *    // 创建一个动态规划数组dp，初始值为0
 *    vector<int> dp(N + 1, 0);

 !    两层循环不能互换位置
 *    // 外层循环遍历每个类型的研究材料
 *    for (int i = 0; i < M; ++i) {
 !        // 内层循环从 N 空间逐渐减少到当前研究材料所占空间
 *        for (int j = N; j >= costs[i]; --j) {
 *            // 考虑当前研究材料选择和不选择的情况，选择最大值
 *            dp[j] = max(dp[j], dp[j - costs[i]] + values[i]);
 *        }
 *    }

 *    // 输出dp[N]，即在给定 N 行李空间可以携带的研究材料最大价值
 *    cout << dp[N] << endl;

 *    return 0;
 * }
*/