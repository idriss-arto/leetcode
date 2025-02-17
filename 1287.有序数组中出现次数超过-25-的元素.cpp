/*
 * @lc app=leetcode.cn id=1287 lang=cpp
 * 二分查找
 * [1287] 有序数组中出现次数超过25%的元素
 */

/*
思路：
满足条件的整数 x 至少在数组 arr 中出现了 span = arr.length / 4 + 1 次，
那么我们可以断定：数组 arr 中的元素 arr[0], arr[span], arr[span * 2], ... 一定包含 x。

我们可以使用反证法证明上述的结论。假设 arr[0], arr[span], arr[span * 2], ... 均不为 x，
由于数组 arr 已经有序，
那么 x 只会连续地出现在 arr[0], arr[span], arr[span * 2], ... 中某两个相邻元素的间隔中，
因此其出现的次数最多为 span - 1 次，这与它至少出现 span 次相矛盾。

有了上述的结论，我们就可以依次枚举 arr[0], arr[span], arr[span * 2], ... 中的元素，
并将每个元素在数组 arr 上进行二分查找，得到其在 arr 中出现的位置区间。
如果该区间的长度至少为 span，那么我们就得到了答案。
*/

// @lc code=start
#include <vector>
#include <algorithm>
using std::vector;
class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size();
        int span = n / 4 + 1;
        for (int i = 0; i < n; i += span) {
            auto iter_l = lower_bound(arr.begin(), arr.end(), arr[i]);
            auto iter_r = upper_bound(arr.begin(), arr.end(), arr[i]);
            if (iter_r - iter_l >= span) {
                return arr[i];
            }
        }
        return -1;
    }
};
// @lc code=end

