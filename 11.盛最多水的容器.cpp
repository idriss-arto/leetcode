/*
 * @lc app=leetcode.cn id=11 lang=cpp
 * 双指针
 ! [11] 盛最多水的容器
 */

// @lc code=start
#include <vector>
using namespace std;

/*
 * 官方题解，思路： 
 * 双指针代表的是 可以作为容器边界的所有位置的范围。
 * 在一开始，双指针指向数组的左右边界，表示 数组中所有的位置都可以作为容器的边界，
 * 因为我们还没有进行过任何尝试。
 * 在这之后，我们每次将 对应的数字较小的那个指针 往 另一个指针 的方向移动一个位置，
 * 就表示我们认为 这个指针不可能再作为容器的边界了。
 * 
 * 为什么移动对应数字较小的那个指针呢？
 ! 这是因为，容纳的水量是由 两个指针指向的数字中较小值∗指针之间的距离 决定的。
 * 如果我们移动对应数字较大的那个指针，
 * 那么前者「两个指针指向的数字中较小值」不会增加，后者「指针之间的距离」会减小，那么这个乘积会减小。
 * 因此，我们移动对应数字较大的那个指针是不合理的。因此，我们移动对应数字较小的那个指针。
*/
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int ans = 0;
        while (left < right) {
            int area = min(height[left], height[right]) * (right - left);
            ans = max(ans, area);
            if (height[left] <= height[right]) {
                ++left;
            }
            else {
                --right;
            }
        }
        return ans;
    }
};

//* 我的思路，记录左侧最高的板子
//! 错了！！当前板子和左侧最高不一定构成最大容器，例如[1,2,1]
class Solution {
public:
    int maxArea(vector<int>& height) {
        int leftMaxIndex = 0, right = 1, result = 0;

        while (right < height.size()) {
            result = max(result, min(height[leftMaxIndex], height[right]) * (right - leftMaxIndex));
            if (height[right] > height[leftMaxIndex]) leftMaxIndex = right;
            right++;
        }

        return result;
    }
};
// @lc code=end

