/*
 * @lc app=leetcode.cn id=4 lang=cpp
 * 二分查找
 ! [4] 寻找两个正序数组的中位数
 */

// @lc code=start
#include <vector>
#include <climits>
using namespace std;

/*
 * 官方题解一：
 * 要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
 * 这里的 "/" 表示整除
 * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
 * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
 * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
 * 这样 pivot 本身最大也只能是第 k-1 小的元素
 * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
 * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
 ! 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
*/
class Solution {
public:
    //* 找到第 k (k>=1) 小的元素
    int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        int index1 = 0, index2 = 0;

        while (true) {
            //! 边界情况
            if (index1 == m) {
                return nums2[index2 + k - 1];
            }
            if (index2 == n) {
                return nums1[index1 + k - 1];
            }
            if (k == 1) {
                return min(nums1[index1], nums2[index2]);
            }

            //* 正常情况
            int newIndex1 = min(index1 + k / 2 - 1, m - 1);     //* 注意这里有判断是否越界
            int newIndex2 = min(index2 + k / 2 - 1, n - 1);
            int pivot1 = nums1[newIndex1];
            int pivot2 = nums2[newIndex2];
            if (pivot1 <= pivot2) {
                //* nums1中[index1, newIndex1]都可以排除
                k -= newIndex1 - index1 + 1;
                index1 = newIndex1 + 1;
            }
            else {
                //* nums2中[index2, newIndex2]都可以排除
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        if (totalLength % 2 == 1) {
            return getKthElement(nums1, nums2, (totalLength + 1) / 2);
        }
        else {
            return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }
};

/*
 * 官方题解二：
 * 将nums_1划分为n1_left和n1_right两部分，将nums_2划分为n2_left和n2_right两部分。
 * 让n1_left和n2_left的长度和刚好等于n1_right和n2_right的长度和（偶数时可以刚好相等，奇数时让前者大后者一），
 * 且left的最大值小于right的最小值。
 * 此时偶数情况下left的最大值和right的最小值的平均值为中位数，
 * 奇数情况下left的最大值为中位数。
 * 
 * 设n1_left长度为i，n2_left长度为j，显然有i+j = (m+n+1)/2。
 * 即在 [0,m] 中找到 i，使得 B[j−1]≤A[i] 且 A[i−1]≤B[j]。
 * 它等价于：
 * 在 [0,m] 中找到最大的 i，使得 A[i−1]≤B[j]
*/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int m = nums1.size();
        int n = nums2.size();
        int left = 0, right = m;
        //* median1：前一部分的最大值
        //* median2：后一部分的最小值
        int median1 = 0, median2 = 0;

        while (left <= right) {
            //* 前一部分包含 nums1[0 .. i-1] 和 nums2[0 .. j-1]
            //* 后一部分包含 nums1[i .. m-1] 和 nums2[j .. n-1]
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i;

            //* nums_im1, nums_i, nums_jm1, nums_j 分别表示 nums1[i-1], nums1[i], nums2[j-1], nums2[j]
            int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);
            int nums_i = (i == m ? INT_MAX : nums1[i]);
            int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);
            int nums_j = (j == n ? INT_MAX : nums2[j]);

            if (nums_im1 <= nums_j) {
                median1 = max(nums_im1, nums_jm1);
                median2 = min(nums_i, nums_j);
                left = i + 1;
            }
            else {
                right = i - 1;
            }
        }

        return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
    }
};
// @lc code=end

