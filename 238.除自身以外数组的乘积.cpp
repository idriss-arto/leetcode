/*
 * @lc app=leetcode.cn id=238 lang=cpp
 * 动态规划，前缀乘积、后缀乘积
 ! [238] 除自身以外数组的乘积
 */

// @lc code=start
#include <vector>
using namespace std;

/*
 * 思路：
 * 使用动态规划，对于下标i的元素，计算它之前所有元素的乘积，和之后所有元素的乘积
 * 令L[i] 代表 i 左侧所有数字的乘积，R[i] 代表 i 右侧所有数字的乘积
*/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        vector<int> L(n, 0);
        L[0] = 1;
        for (int i = 1; i < n; i++) {
            L[i] = L[i-1] * nums[i-1];
            if (L[i] == 0) break;
        }

        vector<int> R(n, 0);
        R[n-1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            R[i] = R[i+1] * nums[i+1];
            if (R[i] == 0) break;
        }

        for (int i = 0; i < n; i++) {
            nums[i] = L[i] * R[i];
        }

        return nums;
    }
};

//* 空间优化版本
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int length = nums.size();
        vector<int> answer(length);

        //* answer[i] 表示索引 i 左侧所有元素的乘积
        //* 因为索引为 '0' 的元素左侧没有元素， 所以 answer[0] = 1
        answer[0] = 1;
        for (int i = 1; i < length; i++) {
            answer[i] = nums[i - 1] * answer[i - 1];
        }

        //* R 为右侧所有元素的乘积
        //* 刚开始右边没有元素，所以 R = 1
        int R = 1;
        for (int i = length - 1; i >= 0; i--) {
            //* 对于索引 i，左边的乘积为 answer[i]，右边的乘积为 R
            answer[i] = answer[i] * R;
            //* R 需要包含右边所有的乘积，所以为了计算下一个结果需要将当前值乘到 R 上
            R *= nums[i];
        }
        return answer;
    }
};

//* 别人的题解，
//* 时间复杂度同样是常数级，但减少了遍历次数
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> answer(nums.size(), 1);
        //* 左指针和右指针
        int left = 0, right = nums.size() - 1;
        //* 前缀乘积和后缀乘积
        int lp = 1, rp = 1;

        while (right >= 0 && left < nums.size()) {
            answer[right] *= rp;
            answer[left] *= lp;
            lp *= nums[left++];
            rp *= nums[right--];
        }

        return answer;
    }
};
// @lc code=end

