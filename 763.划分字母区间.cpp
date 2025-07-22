/*
 * @lc app=leetcode.cn id=763 lang=cpp
 * 贪心，区间
 ! [763] 划分字母区间
 */

/*
 * 思路：
 * 题目要求同一字母最多出现在一个片段中，所以需要统计每个字母的出现边界。
 * 在遍历的过程中相当于是根据当前字母的边界更新最远边界，
 * 如果走到之前遍历过的所有字母的最远边界，说明这个边界就是分割点了。
 * 即此时前面出现过的所有字母，最远也就到这个边界了。
 * 
 * 可以分为如下两步：
 * 1.统计每一个字符最后出现的位置。
 * 2.从头遍历字符，并更新字符的最远出现下标，如果找到字符最远出现位置下标和当前下标相等了，则找到了分割点。
 * 
 * 
 * 还有个思路是统计每个字母的左边界和右边界，然后做合并区间（即重叠区间判定+对应操作），但很麻烦。
*/

// @lc code=start
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    vector<int> partitionLabels(string S) {
        int rightBorder[27] = {0};              //* i为字符，rightBorder[i]为字符出现的最后位置
        for (int i = 0; i < S.size(); i++) {    //* 统计每一个字符最后出现的位置
            rightBorder[S[i] - 'a'] = i;
        }

        vector<int> result;
        int left = 0;
        int right = 0;

        for (int i = 0; i < S.size(); i++) {
            right = max(right, rightBorder[S[i] - 'a']);   //* 找到字符出现的最远边界
            if (i == right) {
                result.push_back(right - left + 1);
                left = i + 1;
            }
        }
        
        return result;
    }
};
// @lc code=end

