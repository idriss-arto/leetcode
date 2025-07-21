/*
 * @lc app=leetcode.cn id=84 lang=cpp
 * 单调栈
 ! [84] 柱状图中最大的矩形
 */

/*
 * 思路：
 * 要想到求整个数组最大矩形，可以拆成分别求包含下标i的最大矩形，再比较出最大值
 * 包含下标i的最大矩形，是以 i 为中心，
 * 向左找第一个小于 heights[i] 的位置 left_i；
 * 向右找第一个小于 heights[i] 的位置 right_i，
 * 即包含下标i最大面积为 heights[i] * (right_i - left_i -1)
*/

// @lc code=start
#include <vector>
#include <stack>
using namespace std;

//* 暴力解，会超时
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int sum = 0;
        for (int i = 0; i < heights.size(); i++) {
            int left = i;
            int right = i;
            //* 找左边第一个高度小于自己的下标
            for (; left >= 0; left--) {
                if (heights[left] < heights[i]) break;
            }
            //* 找右边第一个高度小于自己的下标
            for (; right < heights.size(); right++) {
                if (heights[right] < heights[i]) break;
            }
            int w = right - left - 1;
            int h = heights[i];
            sum = max(sum, w * h);
        }
        return sum;
    }
};

/*
 * 动态规划预处理
 * 思路：
 * 对于每个位置，要分别找到左边和右边第一个小于自己高度的下标
 * 如果在每个位置分别向两边挨个遍历比较大小，会有很多重复操作
 * 用动态规划思路，保存中间结果，即分别保存每个位置左边和右边第一个小于自己高度的下标
 * 这需要两次遍历，分别是从头到尾和从尾到头
 * 
 * 
 * 以从头到尾为例，当我们遍历到下标i时，我们已知前面的下标的左边第一个小于自己高度的下标
 * 1.
 * 如果下标i-1高度小于下标i，则minLeftIndex[i] = i-1;
 * 2.
 ! 否则，即下标i-1高度大于下标i，那么在i-1左侧的高度大于i-1的也不用考虑了，
 ! 直接考虑i-1左侧第一个小于i-1高度的下标，即minLeftIndex[i-1]，
 * 后续也是这样递归处理，直到找到一个小于i高度的下标或到达下标0
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> minLeftIndex(heights.size());
        vector<int> minRightIndex(heights.size());
        int size = heights.size();

        //* 记录每个柱子 左边第一个小于该柱子的下标
        minLeftIndex[0] = -1;               //! 注意这里初始化，防止下面while死循环
        for (int i = 1; i < size; i++) {
            int t = i - 1;
            //* 这里不是用if，而是不断向左寻找的过程
            while (t >= 0 && heights[t] >= heights[i]) {
                t = minLeftIndex[t];
            }
            minLeftIndex[i] = t;
        }

        //* 记录每个柱子 右边第一个小于该柱子的下标
        minRightIndex[size - 1] = size;     //! 注意这里初始化，防止下面while死循环
        for (int i = size - 2; i >= 0; i--) {
            int t = i + 1;
            //* 这里不是用if，而是不断向右寻找的过程
            while (t < size && heights[t] >= heights[i]) {
                t = minRightIndex[t];
            }
            minRightIndex[i] = t;
        }

        //* 求和
        int result = 0;
        for (int i = 0; i < size; i++) {
            int sum = heights[i] * (minRightIndex[i] - minLeftIndex[i] - 1);    //* 注意这里减一，因为是求中间宽度
            result = max(sum, result);
        }
        return result;
    }
};

//* 单调栈
//* 和接雨水思路大致相同，只是从找左右第一个大于自己变成找左右第一个小于自己
//! 注意要在数组头尾都加上0，避免特殊情况（数组为递增或递减）
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        stack<int> st;

        heights.insert(heights.begin(), 0); //! 数组头部加入元素0
        heights.push_back(0);               //! 数组尾部加入元素0

        st.push(0);

        //* 第一个元素已经入栈，从下标1开始
        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) {           //* 情况一
                st.push(i);
            } 
            else if (heights[i] == heights[st.top()]) {     //* 情况二
                st.pop();   //* 这个可以加，可以不加，结果一样，思路不同
                st.push(i);
            } 
            else {                                          //* 情况三
                while (!st.empty() && heights[i] < heights[st.top()]) {     //! 注意是while
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {              //* 找左边第一个小于自己的下标时先判断栈不为空
                        int left = st.top();
                        int right = i;
                        int w = right - left - 1;
                        int h = heights[mid];
                        result = max(result, w * h);
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};
// @lc code=end

