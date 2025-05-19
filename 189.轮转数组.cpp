/*
 * @lc app=leetcode.cn id=189 lang=cpp
 * 数组
 * [189] 轮转数组
 */

// @lc code=start
#include <vector>
using namespace std;

//* 法一：数组翻转
class Solution {
public:
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);
            start++;
            end--;
        }
    }

    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums, 0, nums.size() - 1 - k);
        reverse(nums, nums.size() - k, nums.size() - 1);
        reverse(nums, 0, nums.size() - 1);
    }
};

//* 法二：使用额外数组
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> newArr(n);
        for (int i = 0; i < n; ++i) {
            newArr[(i + k) % n] = nums[i];
        }
        nums.assign(newArr.begin(), newArr.end());
    }
};

//* 法三：原地环状替换，用temp保存被替换的值
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        int count = 0;
        for (int start = 0; count < n; ++start) {
            int current = start;
            int temp = nums[start];
            while(1) {
                int next = (current + k) % n;
                swap(nums[next], temp);
                count++;
                current = next;
                if (current == start) break;
            }
        }
    }
};
// @lc code=end

