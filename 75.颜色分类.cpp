/*
 * @lc app=leetcode.cn id=75 lang=cpp
 * 双指针
 ! [75] 颜色分类
 */

// @lc code=start
#include <vector>
using namespace std;

/*
 * 灵茶的题解，核心原理可以这样理解：
 * 它通过一次遍历，同时维护了三个区域的边界（尽管代码中只显式用了两个指针 p0 和 p1，但 i 隐式地构成了第三个边界）。
 * 其实就相当于在计数，有 p0 个 0，有 p1 - p0 个 1，有 i - p1 个 2。
 */ 
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0 = 0, p1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            nums[i] = 2;
            if (x <= 1) {
                nums[p1++] = 1;
            }
            if (x == 0) {
                nums[p0++] = 0;
            }
        }
    }
};

//* 排序0和1
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0 = 0, p1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) {
                swap(nums[i], nums[p1]);
                p1++;
            }
            else if (nums[i] == 0) {
                swap(nums[i], nums[p0]);
                if (p0 < p1) {              //* 这种情况下换出的nums[p0]是1，需要再换一次放在p1
                    swap(nums[i], nums[p1]);
                }
                p0++;
                p1++;
            }
        }
        
    }
};

//* 排序0和2
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0 = 0, p2 = nums.size() - 1;
        for (int i = 0; i <= p2; i++) {
            while (i <= p2 && nums[i] == 2) {   //* 换出的p2可能也是2，需要循环判断nums[i]是否为2
                swap(nums[i], nums[p2]);
                p2--;
            }
            if (nums[i] == 0) {
                swap(nums[i], nums[p0]);
                p0++;
            }
        }
        
    }
};
// @lc code=end

