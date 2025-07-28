/*
 * @lc app=leetcode.cn id=5 lang=cpp
 * 动态规划，双指针（中心扩展），Manacher算法
 * [5] 最长回文子串
 */

/*
 * 动态规划思路：
 * 如果将dp[i]定义为下标i结尾的字符串最长回文子串长度的话，我们会发现dp[i] 和 dp[i-1] ，dp[i + 1] 看上去都没啥关系。
 * 所以考虑到回文串性质，判断一个子字符串（字符串下标范围[i,j]）是否回文，依赖于子字符串（下标范围[i + 1, j - 1]））是否是回文。
 * 所以为了明确这种递归关系，我们的dp数组是要定义成一个二维dp数组。
 ! dp[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串。
 * 时间复杂度O（N^2）
 * 
 * 双指针（中心扩展）思路：
 * 首先确定回文串，就是找中心然后向两边扩散看是不是对称的就可以了。
 * 在遍历中心点的时候，要注意中心点有两种情况。
 ! 一个元素可以作为中心点，两个元素也可以作为中心点。
 * 因为是要找最长回文子串，所以需要扩展时返回左边界和右边界
 * 时间复杂度O（N^2）
 * 
 * Manacher算法:
 * 简单来说就是利用之前中心扩展的结果
 ! Manacher算法只适合处理长度为奇数的回文子串，所以需要对原字符串进行处理
 * 时间复杂度O（N）
*/

// @lc code=start
#include <string>
#include <vector>
#include <utility>
using namespace std;

/* 
 * 动态规划思路：
 * 如果将dp[i]定义为下标i结尾的字符串最长回文子串长度的话，我们会发现dp[i] 和 dp[i-1] ，dp[i + 1] 看上去都没啥关系。
 * 所以考虑到回文串性质，判断一个子字符串（字符串下标范围[i,j]）是否回文，依赖于子字符串（下标范围[i + 1, j - 1]））是否是回文。
 * 所以为了明确这种递归关系，我们的dp数组是要定义成一位二维dp数组。
 * dp[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串 
 * 
 * 确定状态转移方程：
 * 当s[i]与s[j]不相等，那没啥好说的了，dp[i][j]一定是false。
 * 当s[i]与s[j]相等时，这就复杂一些了，有如下三种情况
 * 情况一：下标i 与 j相同，同一个字符例如a，当然是回文子串
 * 情况二：下标i 与 j相差为1，例如aa，也是回文子串
 * 情况三：下标i 与 j相差大于1的时候，例如cabac，此时s[i]与s[j]已经相同了，我们看i到j区间是不是回文子串就看aba是不是回文就可以了，
 * 即 i+1 与 j-1区间，这个区间是不是回文就看dp[i + 1][j - 1]是否为true。
 * 
 * 遍历顺序：
 * 由状态转移方程，可看出需要从下到上，从左到右遍历，同时j一定大于等于i
 * 
 * 时间复杂度O（N^2）
*/
class Solution {
public:
    string longestPalindrome(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int maxLen = 1;
        int left = -1;

        //! 注意这里外层遍历顺序是从下往上
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j] && (j - i <= 1 || dp[i+1][j-1])) {
                    dp[i][j] = true;
                    if (j - i + 1 >= maxLen) {
                        maxLen = j - i + 1;
                        left = i;
                    }
                }
            }
        }

        return s.substr(left, maxLen);
    }
};

/* 
 * 双指针（中心扩展）思路：
 * 首先确定回文串，就是找中心然后向两边扩散看是不是对称的就可以了。
 * 在遍历中心点的时候，要注意中心点有两种情况。
 * 一个元素可以作为中心点，两个元素也可以作为中心点。
 * 因为是要找最长回文子串，所以需要扩展时返回左边界和右边界。
 * 时间复杂度O（N^2）
*/
class Solution {
public:
    pair<int, int> expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return {left + 1, right - 1};
    }

    string longestPalindrome(string s) {
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            pair<int, int> result1 = expandAroundCenter(s, i, i);
            int left1 = result1.first;
            int right1 = result1.second;

            pair<int, int> result2 = expandAroundCenter(s, i, i + 1);
            int left2 = result2.first;
            int right2 = result2.second;

            if (right1 - left1 > end - start) {
                start = left1;
                end = right1;
            }
            if (right2 - left2 > end - start) {
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end - start + 1);
    }
};

/*
 * Manacher算法，时间复杂度只有O(n)，上面两个都是O(n^2)
 * 简单来说就是利用之前中心扩展的结果
 ! Manacher算法只适合处理长度为奇数的回文子串，所以需要对原字符串进行处理
 * 详情见官方题解，图示见647
*/
class Solution {
public:
    int expand(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return (right - left - 2) / 2;
    }

    string longestPalindrome(string s) {
        int start = 0, end = -1;

        //* Manacher算法只适合处理长度为奇数的回文子串，所以需要对原字符串进行处理
        string t = "#";
        for (char c: s) {
            t += c;
            t += '#';
        }
        s = t;

        //* 这里的臂长没包括中心元素
        //* 如aba，臂长为1。
        vector<int> arm_len;
        int right = -1, j = -1;
        for (int i = 0; i < s.size(); ++i) {
            int cur_arm_len;
            if (right >= i) {
                int i_sym = j * 2 - i;
                int min_arm_len = min(arm_len[i_sym], right - i);
                cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
            }
            else {
                cur_arm_len = expand(s, i, i);
            }
            
            arm_len.push_back(cur_arm_len);
            
            if (i + cur_arm_len > right) {
                j = i;
                right = i + cur_arm_len;
            }
            if (cur_arm_len * 2 + 1 > end - start) {
                start = i - cur_arm_len;
                end = i + cur_arm_len;
            }
        }

        string ans;
        for (int i = start; i <= end; ++i) {
            if (s[i] != '#') {
                ans += s[i];
            }
        }
        return ans;
    }
};
// @lc code=end

