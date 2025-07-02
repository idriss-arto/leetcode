/*
 * @lc app=leetcode.cn id=169 lang=cpp
 * 哈希，技巧
 * [169] 多数元素
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

