/*
 * @lc app=leetcode.cn id=350 lang=cpp
 * 哈希
 ! [350] 两个数组的交集 II
 */

/*
 * 思路：
 * 因为这次交集要求每个元素出现的次数与该元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）
 * 所以不能用set去重，也不能用vector（数据无边界的情况下），因为不能同时记录元素和出现次数
 * 所以使用map，key为元素，value为出现的次数
 * 此外还有一个技巧，就是用较小的数组构建hash表
 * 
 * 注意：
 * 数据有边界，且范围小的情况下，优先用数组模拟hash
*/

// @lc code=start
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    vector<int> intersectWithHash(vector<int>& nums1, vector<int>& nums2) {
        //* 确保用长度小的数组建立hash表
        if (nums1.size() > nums2.size()) {
            return intersectWithHash(nums2, nums1);
        }
        unordered_map <int, int> m;
        for (int num : nums1) {
            ++m[num];
        }
        vector<int> intersection;
        for (int num : nums2) {
            if (m.count(num)) {
                intersection.push_back(num);
                --m[num];
                if (m[num] == 0) {
                    m.erase(num);
                }
            }
        }
        return intersection;
    }

    //* 适用于数据有边界的情况，运行更快，因为不用做hash运算
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector <int> res;
        int hash[1005] = {0};                                               //* 默认数值为0
        for (int num : nums1) {                                             //* nums1中出现的字母在hash数组中做记录
            hash[num] += 1;
        }
        for (int num : nums2) {                                             //* nums2中出现的话，result记录
            if (hash[num] >= 1) {
                res.push_back(num);
                hash[num]--;
            }
        }
        return res;
    }
};

// @lc code=end

