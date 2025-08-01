/*
 * @lc app=leetcode.cn id=47 lang=cpp
 * 回溯(排列)
 ! [47] 全排列 II
 */

/*
 * 排列问题的不同：
 * 每层都是从0开始搜索而不是startIndex
 * 需要used数组记录path里都放了哪些元素了(树枝去重)
 * 
 * 因为没有index了，每次进入下一层都是从0开始遍历，
 * 同时同一元素（注意不是同一数字）在一个全排列中不会被多次使用，
 ! 所以需要使用used数组记录元素使用情况进行树枝去重。
 *
 * 注意，本题使用 set 去重的话和 90.子集II 有一定差别，90.子集II 中要求必须先排序。
 * 这是因为子集是不讲究顺序的，如果数组为[1,2,1]，不排序使用set的话，
 * 求子集过程会出现[1,2]和[2,1]，而他们是同一个子集。
 * 
 * 而本题求全排列，即数组为[1,2,1]时，[1,2]和[2,1]本来就都应该在答案中。
 * 
 * 同时，因为数组有重复元素，又要求求的全排列没有重复的，所以要树层去重
 * 树层去重思路：
 * 一：排序+startIndex判断是同一树枝还是同一树层（本题用不了）
 * 二：排序+used数组判断是同一树枝还是同一树层
 * 三：排序+每层定义一个set记录哪些数用过
*/

// @lc code=start
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

//* used数组判断进行树层去重
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    vector<int> used;

    void backtracking(const vector<int>& nums) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if ((used[i]) == 1) continue;                                   //* 同枝去重
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;      //* 同层去重
            used[i] = 1;            //* 记录这个元素在本枝用过了，本枝后面不能再用了
            path.push_back(nums[i]);
            backtracking(nums);
            used[i] = 0;            //* 准备进入同层下一个节点了，必须有这步回溯，不然每个元素在树中只能用一次，最后全排列只有一个
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        used.resize(nums.size(), 0);
        backtracking(nums);
        return result;
    }
};

//* set去重进行树层去重
//* 因为本题是全排序问题，没有startindex，
//* 需要用used数组记录每个元素有没有使用来进行树枝去重
class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;

    void traversal(vector<int>& nums) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return ;
        }
        unordered_set<int> uset;
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] || uset.count(nums[i])) {
                continue;
            }

            used[i] = true;
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            traversal(nums);
            path.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if (nums.size() == 0) {
            return {};
        }

        sort(nums.begin(), nums.end());     //* 排列问题使用set去重可以不排序
        used.resize(nums.size(), false);

        traversal(nums);
        return result;
    }
};
// @lc code=end

