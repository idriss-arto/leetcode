/*
 * @lc app=leetcode.cn id=491 lang=cpp
 * 回溯(子序列)
 * [491] 非递减子序列
 */

/* 
 ! 同层去重特殊情况，不能排序
 * 思路：因为要求不能有重复的非递减子序列，所以需要树层去重
 * 如[4,4,7]，不去重的话，答案里会有两个[4,7]
 * 同时，这题特殊情况不能排序，所以只能用一个数据结构记录本层使用了哪些元素
 * 注意，这个数据结构只能在回溯函数中定义，不能定义为全局参数
 * 
 * 注意，本题和 90.子集II 有一定差别，90.子集II 要求排序
 * 这是因为子集是不讲究顺序的，如果数组为[1,2,1]，求子集过程会出现[1,2]和[2,1]，而他们是同一个子集
 * 而本题求递增子序列，自带一个逻辑，即数组为[1,2,1]时，只会出现[1,2]，不会出现[2,1]
*/

// @lc code=start
#include <vector>
using namespace std;
class Solution {
    private:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(vector<int>& nums, int startIndex) {
            if (path.size() > 1) {
                result.push_back(path);
            }
            int used[201] = {0};            //* 这里使用数组来进行去重操作，题目说数值范围[-100, 100]
                                            //! 不能定义为全局变量，因为只记录本层
            for (int i = startIndex; i < nums.size(); i++) {
                if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1) {
                        continue;
                }
                used[nums[i] + 100] = 1;    //* 记录这个元素在本层用过了，本层后面不能再用了
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            }
        }
    public:
        vector<vector<int>> findSubsequences(vector<int>& nums) {
            result.clear();
            path.clear();
            backtracking(nums, 0);
            return result;
        }
    };
// @lc code=end

