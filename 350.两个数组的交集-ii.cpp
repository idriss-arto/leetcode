/*
 * @lc app=leetcode.cn id=350 lang=cpp
 * 哈希
 * [350] 两个数组的交集 II
 */

// @lc code=start
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    vector<int> intersectWithHash(vector<int>& nums1, vector<int>& nums2) {
        // 确保用长度小的数组建立hash表
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

    // 适用于数据有边界的情况，运行更快，因为不用做hash运算
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector <int> res;
        int hash[1005] = {0};                                               // 默认数值为0
        for (int num : nums1) {                                             // nums1中出现的字母在hash数组中做记录
            hash[num] += 1;
        }
        for (int num : nums2) {                                             // nums2中出现的话，result记录
            if (hash[num] >= 1) {
                res.push_back(num);
                hash[num]--;
            }
        }
        return res;
    }
};

// @lc code=end

