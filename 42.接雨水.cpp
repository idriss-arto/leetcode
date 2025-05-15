/*
 * @lc app=leetcode.cn id=42 lang=cpp
 * 单调栈，动态规划，双指针
 ! [42] 接雨水
 */

// @lc code=start
#include <vector>
#include <stack>
using namespace std;

//* 暴力解法，列方向记录雨水量
//* 时间复杂度O（n^2）
class Solution {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        for (int i = 0; i < height.size(); i++) {
            //* 第一个柱子和最后一个柱子不接雨水
            if (i == 0 || i == height.size() - 1) continue;

            int rHeight = height[i];    //* 记录右边柱子的最高高度
            int lHeight = height[i];    //* 记录左边柱子的最高高度
            for (int r = i + 1; r < height.size(); r++) {
                if (height[r] > rHeight) rHeight = height[r];
            }
            for (int l = i - 1; l >= 0; l--) {
                if (height[l] > lHeight) lHeight = height[l];
            }
            int h = min(lHeight, rHeight) - height[i];
            if (h > 0) sum += h;
        }
        return sum;
    }
};

//* 动态规划预处理，列方向记录雨水量
//* 以上暴力解法中有许多重复计算
//* 用两个数组分别记录每一个位置的左边最高高度和右边最高高度，避免重复计算
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() <= 2) return 0;
        
        //* 记录每个柱子及左边柱子最大高度
        vector<int> maxLeft(height.size(), 0);
        //* 记录每个柱子及右边柱子最大高度
        vector<int> maxRight(height.size(), 0);
        int size = height.size();

        maxLeft[0] = height[0];
        for (int i = 1; i < size; i++) {
            maxLeft[i] = max(height[i], maxLeft[i - 1]);
        }
        
        maxRight[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            maxRight[i] = max(height[i], maxRight[i + 1]);
        }
        //* 求和
        int sum = 0;
        for (int i = 0; i < size; i++) {
            int count = min(maxLeft[i], maxRight[i]) - height[i];
            //* 这里不判断count大小也可以，因为count最小为0
            if (count > 0) sum += count;
        }
        return sum;
    }
};

/*
 * 单调栈，行方向
 * 思路：
 * 从栈头（元素从栈头弹出）到栈底的顺序应该是从小到大的顺序。
 * 因为一旦发现添加的柱子高度大于栈头元素了，此时就出现凹槽了，
 * 栈头元素就是凹槽底部的柱子，栈头第二个元素就是凹槽左边的柱子，而添加的元素就是凹槽右边的柱子。
 * 
 * 遇到相同的元素，更新栈内下标，就是将栈里元素（旧下标）弹出，将新元素（新下标）加入栈中。
 * 例如 5 5 1 3 这种情况。如果添加第二个5的时候就应该将第一个5的下标弹出，把第二个5添加到栈中。
 * 因为我们要求宽度的时候 如果遇到相同高度的柱子，需要使用最右边的柱子来计算宽度。
*/
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() <= 2) return 0;   //* 可以不加
        stack<int> st;                      //* 存下标，计算的时候用下标去找对应的柱子高度
        st.push(0);
        int sum = 0;
        for (int i = 1; i < height.size(); i++) {
            if (height[i] < height[st.top()]) {             //* 情况一
                st.push(i);
            } else if (height[i] == height[st.top()]) {     //* 情况二
                st.pop();                           //* 其实这一句可以不加，结果是一样的，但处理高度相同的情况的思路却变了。
                st.push(i);
            } else {                                        //* 情况三
                while (!st.empty() && height[i] > height[st.top()]) {   //* 注意这里是while
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {              //! 注意这里需要判断栈stack是否为空
                        int h = min(height[st.top()], height[i]) - height[mid];
                        int w = i - st.top() - 1;   //! 注意减一，只求中间宽度
                        sum += h * w;
                    }
                }
                st.push(i);
            }
        }
        return sum;
    }
};

/*
 * 双指针，列方向记录雨水量
 * 下标 i 处能接的雨水量由 leftMax[i] 和 rightMax[i] 中的最小值决定。
 * 由于数组 leftMax 是从左往右计算，数组 rightMax 是从右往左计算，因此可以使用双指针和两个变量代替两个数组。
 * 比较left和right指向的值，并移动其中值较小的指针，
 * 这个操作保证了left和right中至少有一个指向局部的最大值，也就是说，
 * 比较大的指针指向的height位置就一定是当前的局部（左指针及其左侧位置，右指针及其右侧位置）的最大值。
 * 
 * 例如：5 7 ？ ？ ？ 4 6
 * 一开始left指向5，right指向6，leftMax是5，rightMax是6，ans += 0
 * 下一步left指向7，right指向6，leftMax是7，rightMax是6，ans += 0
 * 下一步left指向7，right指向4，leftMax是7，rightMax是6，ans += 2
 *      此时，对于4来说，不管中间的几个？是什么值，这一列可以接的雨水量已经确定为2了
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (leftMax < rightMax) {
                ans += min(leftMax, rightMax) - height[left];
                left++;
            }
            else {
                ans += min(leftMax, rightMax) - height[right];
                right--;
            }
        }
        return ans;
    }
};
// @lc code=end

