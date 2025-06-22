/*
 * @lc app=leetcode.cn id=45 lang=cpp
 * 贪心
 * [45] 跳跃游戏 II
 */

/*
 * 贪心
 * 一：
 * 新建一个result数组，result[i]表示走到下标i需要的最少步数。
 * 首先遍历一步能覆盖的范围，得到二步能覆盖的范围，
 * 用二步范围减一步范围，就是至少2步才能到达的范围。以此类推
 * 
 * 二：
 * 用ans记录当前走了多少跳
 * 一步一步走，同时更新下一跳覆盖范围为最大值。
 * 当走到当前覆盖范围边界的时候，步数加一，将覆盖范围换成下一跳覆盖范围
 * 注意：
 * 第一次走之前，在下标0的时候，是第一次走到覆盖范围边界
 * 覆盖范围更新后如果大于等于数组最后一个下标，即可退出
*/

// @lc code=start
#include <vector>
#include <climits>
using namespace std;

/*
 * 我的贪心解法
 * 这题只能用覆盖范围写，像55题里我的方法不适合这题，只适合看最远走到哪
 * 我的思路是新建一个result数组，result[i]表示走到下标i需要的最少步数
 * 首先遍历一步能覆盖的范围，得到二步能覆盖的范围，
 * 用二步范围减一步范围，就是至少2步才能到达的范围。以此类推
*/ 
class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> result(nums.size(), -1);
        result[0] = 0;
        int preCover = -1;
        int cover = nums[0];
        
        //! 注意这里cover可能已经大于等于nums.size()了，不加上后半部分判断条件的话会越界
        for (int i = 1; i <= cover && i < nums.size(); i++) {                   
            result[i] = 1;
        }

        for (int i = 1; i <= cover && cover < nums.size(); i++) {
            if (i + nums[i] > cover) {
                preCover = cover;
                cover = i + nums[i];
                //! 同上
                for (int j = preCover + 1; j <= cover && j < nums.size(); j++) {
                    result[j] = result[i] + 1;
                }
            }
        }

        return result.back();
    }
};

/*
 * Carl的贪心解法
 * 用ans记录当前走了多少跳
 * 一步一步走，同时更新下一跳覆盖范围为最大值。
 * 当走到当前覆盖范围边界的时候，步数加一，将覆盖范围换成下一跳覆盖范围
 * 注意：
 ! 第一次走之前，在下标0的时候，是第一次走到覆盖范围边界
 * 覆盖范围更新后如果大于等于数组最后一个下标，即可退出
*/
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int curDistance = 0;        //* 当前覆盖最远距离下标
        int ans = 0;                //* 记录走的最大步数
        int nextDistance = 0;       //* 下一跳覆盖最远距离下标
        for (int i = 0; i < nums.size(); i++) {
            nextDistance = max(i + nums[i], nextDistance);      //* 先更新下一跳覆盖最远距离下标
            if (i == curDistance) {                             //* 遇到当前覆盖最远距离下标
                ans++;                                          //* 需要下一跳，到下一个覆盖范围
                curDistance = nextDistance;                     //* 更新当前覆盖最远距离下标（相当于加油了）
                if (nextDistance >= nums.size() - 1) break;     //* 当前覆盖最远距到达集合终点，不用做ans++操作了，直接结束
            }
        }
        return ans;
    }
};
// @lc code=end

