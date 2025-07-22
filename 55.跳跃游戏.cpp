/*
 * @lc app=leetcode.cn id=55 lang=cpp
 * 贪心
 * [55] 跳跃游戏
 */

/*
 * 贪心思路：
 * 一：
 * 记录剩余跳动次数，即当前还能跳多少次，然后一步一步跳。
 * 在剩余跳动次数变为0之前，都能往后跳，
 * 如果当前位置的数大于剩余跳动次数，就把剩余跳动次数更新为当前位置的数。
 * 
 * 二：
 * 也是一步一步跳，但是是在覆盖范围里一步一步跳，
 * 同时每一次跳更新覆盖范围，
 * 覆盖范围大于等于最后一个位置，就可以退出了
*/

// @lc code=start
#include <vector>
#include <climits>
using namespace std;

/*
 * Carl贪心
 * 思路：
 * 也是一步一步跳，但是是在覆盖范围里一步一步跳，
 * 同时每一次跳更新覆盖范围，
 * 覆盖范围大于等于最后一个位置，就可以退出了
*/
class Solution {
public:  
    bool canJump(vector<int>& nums) {
        //* 最好cover初始化为0，下面i从0开始遍历
        //* 如果cover初始化为nums[0]，下面i从1开始遍历，特殊情况[0]会判断错
        int cover = 0;
        if (nums.size() == 1) return true;  //* 只有一个元素，就是能达到
        for (int i = 0; i <= cover; i++) {  //* 注意这里是小于等于cover
            cover = max(i + nums[i], cover);
            if (cover >= nums.size() - 1) return true;  //* 说明可以覆盖到终点了
        }
        return false;
    }
};

/*
 * 我的贪心
 * 思路：
 * 记录剩余跳动次数，即当前还能跳多少次，然后一步一步跳。
 * 在剩余跳动次数变为0之前，都能往后跳。
 * 如果当前位置的数大于剩余跳动次数，就把剩余跳动次数更新为当前位置的数。 
*/
class Solution {
public:
    bool CanJump(vector<int>& nums) {
        int cnt = nums[0];
        int i = 1;
        for (; cnt > 0 && i < nums.size(); i++) {
            cnt--;
            if (nums[i] > cnt) cnt = nums[i];
        }
        if (i == nums.size()) return true;
        else return false;
    }
};
// @lc code=end

