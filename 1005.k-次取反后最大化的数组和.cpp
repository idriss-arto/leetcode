/*
 * @lc app=leetcode.cn id=1005 lang=cpp
 * 贪心
 * [1005] K 次取反后最大化的数组和
 */

/*
 * 贪心思路：
 * 先处理绝对值大的负数（排序可以按绝对值从大到小排，或者直接按升序排）
 * 如果处理完所有负数还有翻转次数，且剩余次数为奇数
 * 则找到现在的最小值（即所有非负数的最小值），翻转一次
*/

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 我的贪心
 * 先处理负数，如果处理完所有负数还有翻转次数，且剩余次数为奇数
 * 则找到现在的最小值（即所有非负数的最小值），翻转一次
 */
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        //* 首先把所有负数转为正数
        int i = 0;
        for (; i < nums.size() && k > 0; i++) {
            if (nums[i] < 0) {
                nums[i] = -nums[i];
                k--;
            }
            else {
                break;
            }
        }

        /*
        //* 如果翻转次数没用完并且剩余次数为奇数
        //* 那么重新排序
        //* 找到现在的最小非负数
        if (k != 0 && k % 2 != 0) {
            //* sort(nums.begin(), nums.end());
            //* 可优化为以下式子，因为最小正数一定在原来的负数和原来的第一个非负数之间
            if (i != nums.size()) sort(nums.begin(), nums.begin() + i);
            else sort(nums.begin(), nums.end());
            nums[0] = -nums[0];
            k = 0;
        }
        */

        /*
         * 其实不用重新排序，

         * 因为i如果没越界的话，则指向原来的第一个非负数
         * 所以现在最小的非负数数就在nums[i]和nums[i-1]之间
        
         * i如果越界，说明原数组全为负数，则现在nums[i-1]就是最小非负数
        */ 
        if (k != 0 && k % 2 != 0) {
            if (i == nums.size()) nums[i-1] = -nums[i-1];
            else {
                //* 需要考虑原数组全为非负数的情况
                if (i == 0 || nums[i] < nums[i-1]) nums[i] = -nums[i];
                else nums[i-1] = -nums[i-1];
            }
        }

        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        return sum;
    }
};

/*
 * Carl贪心
 * 将数组按绝对值从大到小排序，并优先翻转绝对值大的负数，
 * 如果遍历完还有奇数次翻转次数，则翻转绝对值最小的数字即可（即现在数组尾的元素）
*/
class Solution {
    static bool cmp(int a, int b) {
        return abs(a) > abs(b);
    }
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(), A.end(), cmp);       //* 按绝对值从大到小排序
        for (int i = 0; i < A.size(); i++) { //* 优先翻转绝对值大的负数
            if (A[i] < 0 && K > 0) {
                A[i] *= -1;
                K--;
            }
        }
        if (K % 2 == 1) A[A.size() - 1] *= -1;  //* 翻转绝对值最小的数字
        int result = 0;
        for (int a : A) result += a;            //* 求和
        return result;
    }
};
// @lc code=end

