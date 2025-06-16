/*
 * @lc app=leetcode.cn id=739 lang=cpp
 * 单调栈，动态规划
 * [739] 每日温度
 */

/*
 * 思路：
 * 求取每个位置右边第一个比自己大的值（或者说位置），考虑到用单调栈
 * 使用单调栈需考虑以下几个问题
 * 1.单调栈里存放的元素是什么？
 * 单调栈里只需要存放元素的下标i就可以了，如果需要使用对应的元素，直接T[i]就可以获取。
 * 
 * 2.单调栈里元素是递增呢？ 还是递减呢？
 * 这里我们需要从栈顶到栈底单调递增（即任何时刻栈底的值是最大的），因为栈里要加入一个元素i的时候，
 * 我们需要递归判断i是否是栈顶元素在数组中右面第一个比栈顶元素大的元素
 * 
 * 例如：   1
 *          4   在遇到5之后变成     5
 *          7                       7
 * 即：如果求一个元素右边第一个更大元素，单调栈就是递增的，如果求一个元素右边第一个更小元素，单调栈就是递减的。
*/

// @lc code=start
#include <vector>
#include <stack>
using namespace std;

//* 单调栈，完整写法
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        //* 递增栈
        stack<int> st;
        vector<int> result(T.size(), 0);
        st.push(0);
        for (int i = 1; i < T.size(); i++) {
            //* 显然以下三种情况可以合并，这里为了显示得清楚分开写
            if (T[i] < T[st.top()]) {                       //* 情况一
                st.push(i);
            } 
            else if (T[i] == T[st.top()]) {                 //* 情况二
                st.push(i);
            } 
            else {
                while (!st.empty() && T[i] > T[st.top()]) { //* 情况三
                    result[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};

//* 单调栈，简略写法
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        //* 递增栈
        stack<int> st;
        vector<int> result(T.size(), 0);
        st.push(0);
        for (int i = 1; i < T.size(); i++) {
            //* 三种情况合并写法
            while (!st.empty() && T[i] > T[st.top()]) {
                result[st.top()] = i - st.top();
                st.pop();
            }
            //* 别忘了处理完之前的下标后将当前下标入栈
            st.push(i);
        }
        return result;
    }
};

//* 别人的解法，动态规划
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ans(temperatures.size(),0);
        int n = temperatures.size();
        for (int i = n - 2; i >= 0; i--){
            int next = i + 1;
            while ( next < n && temperatures[next] <= temperatures[i]){
                if (ans[next] == 0) {   //* 当前下标next之后没有更大的值了
                    next = n;
                }
                else {                  //* next切换到右边第一个值大于自己的下标
                    next += ans[next];
                }
            }
            if (next < n) ans[i] = next - i;
        }
        return ans;
    }
};
// @lc code=end

