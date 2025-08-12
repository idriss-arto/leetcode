/*
 * @lc app=leetcode.cn id=287 lang=cpp
 * 技巧
 ! [287] 寻找重复数
 */

// @lc code=start
#include <vector>
using namespace std;

/*
 * 二分查找
 * 定义 cnt[i] 表示 nums 数组中小于等于 i 的数有多少个，假设我们重复的数是 target，
 * 那么 [1,target−1]里的所有数满足 cnt[i]≤i，
 * [target,n] 里的所有数满足 cnt[i]>i，具有单调性。
 * 此时问题转换为找到第一个满足 cnt[i]>i 的 i 值，其就为目标值target。
 * 
 * 以[1,3,4,2,2]为例，我们列出每个数字的 cnt 值：
 * nums	    1	2	3	4
 * cnt	    1	3	4	5
 * 示例中重复的整数是 2，我们可以看到 [1,1] 中的数满足 cnt[i]≤i，[2,4] 中的数满足 cnt[i]>i 。
 * 
 * 时间复杂度：O(nlogn)
 * 空间复杂度：O(1)
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r) / 2;
            int cnt = 0;
            for (int& num : nums) {
                if (num <= mid) {
                    cnt++;
                }
            }
            if (cnt <= mid) {
                l = mid + 1;
            }
            else r = mid;
        }
        return l;
    }
};

/*
 * 快慢指针寻找环入口
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
// @lc code=end

