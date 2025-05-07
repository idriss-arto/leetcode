/*
 * @lc app=leetcode.cn id=496 lang=cpp
 * 单调栈
 * [496] 下一个更大元素 I
 */

/*
 * 思路：
 * 求右边第一个大于自己的值，还是用单调栈
 * 注意的是，这里是求nums1中元素在nums2中右边第一个大于自己的值
 * 所以result数组大小为nums1大小，用nums2做单调栈，得出结果时先判断元素是否在nums1中
 * 也可以result数组大小为nums2大小，正常用nums2做单调栈，得出所有结果后用nums1去nums2中对应找
*/

// @lc code=start
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> result(nums1.size(), -1);
        if (nums1.size() == 0) return result;

        unordered_map<int, int> umap;   //* key:下标元素，value：下标
        for (int i = 0; i < nums1.size(); i++) {
            umap[nums1[i]] = i;
        }
        st.push(0);
        for (int i = 1; i < nums2.size(); i++) {
            if (nums2[i] < nums2[st.top()]) {           //* 情况一
                st.push(i);
            } else if (nums2[i] == nums2[st.top()]) {   //* 情况二
                st.push(i);
            } else {                                    //* 情况三
                while (!st.empty() && nums2[i] > nums2[st.top()]) {
                    if (umap.count(nums2[st.top()]) > 0) {  //* 看map里是否存在这个元素
                        int index = umap[nums2[st.top()]];  //* 根据map找到nums2[st.top()] 在 nums1中的下标
                        result[index] = nums2[i];
                    }
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};
// @lc code=end

