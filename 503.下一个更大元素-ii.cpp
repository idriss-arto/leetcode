/*
 * @lc app=leetcode.cn id=503 lang=cpp
 * 单调栈
 * [503] 下一个更大元素 II
 */

/*
 * 思路：
 * 两种做法
 * 一：把两个原数组拼接在一起，然后使用单调栈求下一个最大值，最后将result数组resize
 * 二：不扩充nums，而是在遍历的过程中通过取模操作模拟走了两边nums。
*/

// @lc code=start
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        //* 拼接一个新的nums
        vector<int> nums1(nums.begin(), nums.end());
        nums.insert(nums.end(), nums1.begin(), nums1.end());
        //* 用新的nums大小来初始化result
        vector<int> result(nums.size(), -1);
        if (nums.size() == 0) return result;

        //* 开始单调栈
        stack<int> st;
        st.push(0);
        for (int i = 1; i < nums.size(); i++) { 
            //* 显然这里三种情况可以一起写，这里为了看得清楚分开写
            if (nums[i] < nums[st.top()]) {
                st.push(i);
            } 
            else if (nums[i] == nums[st.top()]) {
                st.push(i);
            }
            else { 
                while (!st.empty() && nums[i] > nums[st.top()]) {
                    result[st.top()] = nums[i];
                    st.pop();
                }
                st.push(i);
            }
        }
        //* 最后再把结果集即result数组resize到原数组大小
        result.resize(nums.size() / 2);
        return result;
    }
};

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> result(nums.size(), -1);
        
        if (nums.size() == 0) return result;        //* 不要这句也可以

        stack<int> st;
        st.push(0);
        for (int i = 1; i < nums.size() * 2; i++) { 
            //* 模拟遍历两边nums，注意一下都是用i % nums.size()来操作
            //* 显然这里三种情况可以一起写，这里为了看得清楚分开写
            if (nums[i % nums.size()] < nums[st.top()]) {
                st.push(i % nums.size());
            }
            else if (nums[i % nums.size()] == nums[st.top()]) {
                st.push(i % nums.size());
            } 
            else {
                while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                    result[st.top()] = nums[i % nums.size()];
                    st.pop();
                }
                //* 别忘了处理完之前的下标后将当前下标入栈
                st.push(i % nums.size());
            }
        }
        return result;
    }
};
// @lc code=end

