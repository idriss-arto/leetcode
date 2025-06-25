/*
 * @lc app=leetcode.cn id=169 lang=cpp
 * 哈希，技巧
 * [169] 多数元素
 */

// @lc code=start
#include <vector>
#include <unordered_map>
using namespace std;

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
        int result = -1;
        int count = 0;
        for (int& num : nums) {
            if (num == result) {
                count++;
            }
            else {
                count--;
                if (count < 0) {
                    result = num;
                    count = 0;
                }
            }
        }
        return result;
    }
};
// @lc code=end

