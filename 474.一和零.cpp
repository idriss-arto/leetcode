/*
 * @lc app=leetcode.cn id=474 lang=cpp
 * 动态规划（多维01背包）
 ! [474] 一和零
 */

/*
 * 给定多维度的背包容量，在满足每个维度都不超出时，装满背包最多有多少个物品
*/

/*
 * 思路：
 * 相当于有两个维度的01背包，
 * 每一个物品在装入时都要考虑m维和n维进行动态规划
 * dp[i][j]表示容量为i个0，j个1时最多能装入的字符串个数
 * 不用滚动数组的话，那就得用三维数组
*/

// @lc code=start
#include <vector>
#include <string>
using namespace std;

//* 滚动数组版本
class Solution {
public:
    vector<int> getMN(string& s) {
        vector<int> mn(2, 0);
        for (char& c : s) {
            if (c == '0') mn[0]++;
            if (c == '1') mn[1]++;
        }
        return mn;
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		//* dp[j][k]表示最多有j个0、k个1的情况下，最多能有几个子串
        
        for (int i = 0; i < strs.size(); i++) {
            vector<int> mn = getMN(strs[i]);
            //! 因为是滚动数组，所以容量只能从后往前遍历
            for (int j = m; j >= mn[0]; j--) {
                for (int k = n; k >= mn[1]; k--) {
                    dp[j][k] = max(dp[j][k], dp[j - mn[0]][k - mn[1]] + 1);
                }
            }
        }
        return dp[m][n];
    }
};

//* 三维数组版本
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int num_of_str = strs.size();

		vector<vector<vector<int>>> dp(num_of_str+1, vector<vector<int>>(m + 1,vector<int>(n + 1, 0)));

		/* 	
         * dp[i][j][k]表示考虑前i件物品（i下标从1开始），在容量为j个0，k个1的情况下，最多能装下的物品数 
		 * 用x[i]表示strs[i]中0的个数
		 * 用y[i]表示strs[i]中1的个数
		 * 则状态转移方程为
         * dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j - x[i]][k - y[i]] + 1)
		*/

		//* num_of_zeros记录每个字符串中0的个数
		//* num_of_ones记录每个字符串中1的个数
		vector<int> num_of_zeros;
		num_of_zeros.push_back(0);
		vector<int> num_of_ones;
		num_of_ones.push_back(0);
		for (auto& str : strs){
			int count_of_zero = 0;
			int count_of_one = 0;
			for (char &c : str){
				if(c == '0') count_of_zero ++;
				else count_of_one ++;
			}
			num_of_zeros.push_back(count_of_zero);
			num_of_ones.push_back(count_of_one);
		}
		
		//* num_of_zeros[i]表示第i个字符串str[i-1]中0的个数
		//* num_of_ones[i]表示第i个字符串str[i-1]中1的个数

		for (int i = 1; i <= num_of_str; i++){
			int count_of_zeros = num_of_zeros[i];
			int count_of_ones = num_of_ones[i]; 
			for (int j = 0; j <= m; j++){
				for (int k = 0; k <= n; k++){
					if (j < count_of_zeros || k < count_of_ones){
						dp[i][j][k] = dp[i-1][j][k];
					}
					else{
						dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j - count_of_zeros][k - count_of_ones] + 1);
					}
				}
			}
		}

		return dp[num_of_str][m][n];

    }
};
// @lc code=end

