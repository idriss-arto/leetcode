/*
 * @lc app=leetcode.cn id=169 lang=cpp
 * 哈希，技巧
 ! [169] 多数元素
 */

/*
 * 题解思路一：用哈希表记录元素出现频率
 * 题解思路二：技巧，用cnt记录当前元素出现次数，若遇到不同元素则cnt--，当cnt小于0时更新result为当前元素，重新计数cnt。
*/

// @lc code=start
#include <vector>
#include <unordered_map>
using namespace std;

//* 用哈希表记录元素出现频率
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> count;
        int maxcnt = 0;
        int maxnum = 0;
        for (int& num : nums) {
            count[num]++;
            if (count[num] > maxcnt) {
                maxcnt = count[num];
                maxnum = num;
            }
        }
        return maxnum;
    }
};

//* 技巧
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int result = nums[0];
        int cnt = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == result) {
                cnt++;
            }
            else {
                cnt--;
                if (cnt <= 0) {
                    result = nums[i];
                    cnt = 1;
                }
            }
        }
        return result;
    }
};
// @lc code=end

