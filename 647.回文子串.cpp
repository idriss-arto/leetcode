/*
 * @lc app=leetcode.cn id=647 lang=cpp
 * 动态规划，双指针（中心扩展）
 * [647] 回文子串
 */

/*
 * 动态规划思路：
 * 如果将dp[i]定义为下标i结尾的字符串有 dp[i]个回文串的话，我们会发现dp[i] 和 dp[i-1] ，dp[i + 1] 看上去都没啥关系。
 * 所以考虑到回文串性质，判断一个子字符串（字符串下标范围[i,j]）是否回文，依赖于子字符串（下标范围[i + 1, j - 1]））是否是回文。
 * 所以为了明确这种递归关系，我们的dp数组是要定义成一位二维dp数组。
 * dp[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串
 * 
 * 双指针（中心扩展）思路：
 * 首先确定回文串，就是找中心然后向两边扩散看是不是对称的就可以了。
 * 在遍历中心点的时候，要注意中心点有两种情况。
 * 一个元素可以作为中心点，两个元素也可以作为中心点。
*/

// @lc code=start
#include <string>
#include <vector>
using namespace std;

/*
 * 动态规划思路：
 * 如果将dp[i]定义为下标i结尾的字符串有 dp[i]个回文串的话，我们会发现dp[i] 和 dp[i-1] ，dp[i + 1] 看上去都没啥关系。
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
*/
class Solution {
public:
    int countSubstrings(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int result = 0;

        //! 注意这里外层遍历顺序是从下往上
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j] && (j - i <= 1 || dp[i+1][j-1])) {
                    dp[i][j] = true;
                    result++;
                }
            }
        }

        return result;
    }
};

/* 
 * 双指针（中心扩展）思路：
 * 首先确定回文串，就是找中心然后向两边扩散看是不是对称的就可以了。
 * 在遍历中心点的时候，要注意中心点有两种情况。
 * 一个元素可以作为中心点，两个元素也可以作为中心点。
*/
class Solution {
public:
    int countSubstrings(string s) {
        int result = 0;
        for (int i = 0; i < s.size(); i++) {
            result += extend(s, i, i, s.size());        //* 以i为中心
            result += extend(s, i, i + 1, s.size());    //* 以i和i+1为中心
        }
        return result;
    }
    int extend(const string& s, int i, int j, int n) {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j]) {
            i--;
            j++;
            res++;
        }
        return res;
    }
};
// @lc code=end

