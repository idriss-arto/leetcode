/*
 * @lc app=leetcode.cn id=77 lang=cpp
 * 回溯（组合），剪枝
 * [77] 组合
 */

/*
 * 思路：
 * 最经典的回溯问题
 * 需要注意由于是求组合数，所以不强调元素顺序，
 * 得有startIndex避免 出现重复的组合
 * 
 * 本题可剪枝
 * 剪枝思路
 * 已经选择的元素个数：path.size();
 * 还需要的元素个数为: k - path.size();
 * 在集合n中至多要从该起始位置 : n - (k - path.size()) + 1，开始遍历
 * 再往后的位置会发现遍历完也凑不够k个元素！
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startIndex) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        /*
         * 剪枝思路
         * 已经选择的元素个数：path.size();
         * 还需要的元素个数为: k - path.size();
         * 在集合n中至多要从该起始位置 : n - (k - path.size()) + 1，开始遍历
         * 再往后的位置会发现遍历完也凑不够k个元素！
        */
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) { //! 剪枝
            path.push_back(i);  //* 处理节点
            backtracking(n, k, i + 1);
            path.pop_back();    //* 回溯，撤销处理的节点
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }
};
// @lc code=end

