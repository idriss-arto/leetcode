/*
 * @lc app=leetcode.cn id=55 lang=cpp
 * 贪心
 * [55] 跳跃游戏
 */

// @lc code=start
#include <vector>
#include <climits>
using namespace std;
//* 贪心
class Solution {
public:
    /*
     * 我的贪心解法
     * 记录剩余跳动次数，即当前还能跳多少次，然后一步一步跳
     * 在剩余跳动次数变为0之前，都能往后跳
     * 如果当前位置的数大于剩余跳动次数，就把剩余跳动次数更新为当前位置的数
    */
    bool myCanJump(vector<int>& nums) {
        int cnt = nums[0];
        int i = 1;
        for (; cnt > 0 && i < nums.size(); i++) {
            cnt--;
            if (nums[i] > cnt) cnt = nums[i];
        }
        if (i == nums.size()) return true;
        else return false;
    }

    /*
     * 题解的贪心解法
     * 也是一步一步跳，但是是在覆盖范围里一步一步跳，
     * 同时每一次跳更新覆盖范围，
     * 覆盖范围大于等于最后一个位置，就可以退出了
    */
    bool canJump(vector<int>& nums) {
        int cover = 0;
        if (nums.size() == 1) return true;  //* 只有一个元素，就是能达到
        for (int i = 0; i <= cover; i++) {  //* 注意这里是小于等于cover
            cover = max(i + nums[i], cover);
            if (cover >= nums.size() - 1) return true;  //* 说明可以覆盖到终点了
        }
        return false;
    }
};
// @lc code=end

