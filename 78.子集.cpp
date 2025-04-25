/*
 * @lc app=leetcode.cn id=78 lang=cpp
 * 回溯(子集)
 * [78] 子集
 */

/*
 * 子集问题和组合问题、分割问题的的区别：
 * 子集是收集树形结构中树的所有节点的结果。
 * 而组合问题、分割问题是收集树形结构中叶子节点的结果。
 * 
 * 
 * 我的思路：找长度为0的子集，再找长度为1的子集，再找长度为2的子集，以此类推
 * 题解思路：找到第一个长度为1的子集时，顺便把包含第一个子集的长度为2的子集求了，以此类推
 * 例子：[1,2,3]
 * 我的解法：[], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]
 * 题解解法：[], [1], [1,2], [1,2,3], [1,3], [2], [2,3], [3]
*/

// @lc code=start
#include <vector>
using namespace std;

//* 我的解法
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;

    void backtracking(vector<int>& nums, int cnt, int index) {
        if (cnt == 0) result.push_back(path);
        if (index >= nums.size()) return;
        for (int i = index; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtracking(nums, cnt - 1, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        result.push_back(nums);
        for (int i = 0; i <= nums.size() - 1; i++) {
            path.clear();
            //* 传入的i表示求大小为i的子集，传入的0表示从下标0开始
            backtracking(nums, i, 0);
        }
        return result;
    }
};

//* Carl解法
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);             //* 收集子集，要放在终止添加的上面，否则会漏掉自己
        if (startIndex >= nums.size()) {    //* 终止条件可以不加
            return;
        }
        for (int i = startIndex; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
};
// @lc code=end

