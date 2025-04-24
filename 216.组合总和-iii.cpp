/*
 * @lc app=leetcode.cn id=216 lang=cpp
 * 回溯（组合），剪枝
 * [216] 组合总和 III
 */

/*
 * 注意由于是求组合数，所以不强调元素顺序，
 * 我的思路：
 * 加k-1次不同数，最后一次看sum离target还差多少，以及差的这个数target-sum能否取
 * 
 * 题解思路：
 * 加k次，看sum是否刚好等于target
 * 
 * 本题可剪枝
 * 剪枝思路：
 * 一：sum大于target时可直接return
 * 二：可推得i上限为9 - (k - path.size()) + 1（推理过程见下方代码）
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
private:
    vector<vector<int>> result;     //* 存放结果集
    vector<int> path;               //* 符合条件的结果
    int sum = 0;                    //* 当前路径的和
    void backtracking(int targetSum, int k, int startIndex) {
        if (sum > targetSum) {      //* 剪枝操作
            return; 
        }
        if (path.size() == k - 1 && startIndex <= targetSum - sum && targetSum - sum <= 9) {
            path.push_back(targetSum - sum);
            result.push_back(path);
            path.pop_back();
            return;
        }

        /*
         * 剪枝思路
         * 已经选择的元素个数：path.size();
         * 还需要的元素个数为: k - path.size();
         * 在集合n中至多要从该起始位置 : n - (k - path.size()) + 1，开始遍历
         * 再往后的位置会发现遍历完也凑不够k个元素！
        */
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) { //* 剪枝
            sum += i;           //* 处理
            path.push_back(i);  //* 处理
            backtracking(targetSum, k, i + 1);  //* 注意i+1调整startIndex
            sum -= i;           //* 回溯
            path.pop_back();    //* 回溯
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        result.clear(); //* 可以不加
        path.clear();   //* 可以不加
        backtracking(n, k, 1);
        return result;
    }
};
// @lc code=end

