/*
 * @lc app=leetcode.cn id=647 lang=cpp
 * 动态规划，双指针（中心扩展），Manacher算法
 ! [647] 回文子串
 */

/*
 * 动态规划思路：
 * 如果将dp[i]定义为下标i结尾的字符串有 dp[i]个回文串的话，我们会发现dp[i] 和 dp[i-1] ，dp[i + 1] 看上去都没啥关系。
 * 所以考虑到回文串性质，判断一个子字符串（字符串下标范围[i,j]）是否回文，依赖于子字符串（下标范围[i + 1, j - 1]））是否是回文。
 * 所以为了明确这种递归关系，我们的dp数组是要定义成一位二维dp数组。
 ! dp[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串。
 * 时间复杂度O（N^2）
 * 
 * 双指针（中心扩展）思路：
 * 首先确定回文串，就是找中心然后向两边扩散看是不是对称的就可以了。
 * 在遍历中心点的时候，要注意中心点有两种情况。
 ! 一个元素可以作为中心点，两个元素也可以作为中心点。
 * 时间复杂度O（N^2）
 * 
 * Manacher算法思路：
 * Manacher算法是求最长回文子串的算法。
 ! Manacher算法只适合处理长度为奇数的回文子串，所以需要对原字符串进行处理.
 * 在求最长回文子串的过程中，如果求得s中对应最长回文子串长度为k，
 * 则整个字符串的回文子串个数增加 (k+1)/2  （即k/2向上取整）
 * 时间复杂度O（N）
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
 ! 情况一：下标i 与 j相同，同一个字符例如a，当然是回文子串
 ! 情况二：下标i 与 j相差为1，例如aa，也是回文子串
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
    int countSubstrings(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int result = 0;

        //! 注意这里外层遍历顺序是从下往上
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                //* 这里是简略写法，或符号之前是情况一和二，或符号之后是情况三
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
 * 时间复杂度O（N^2）
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

/*
 * Manacher算法，求最长回文子串的算法。
 ! Manacher算法只适合处理长度为奇数的回文子串，所以需要对原字符串进行处理
 * 在求最长回文子串的过程中，如果求得s中对应最长回文子串长度为k，
 * 则整个字符串的回文子串个数增加 (k+1)/2  （即k/2向上取整）
 * 是对中心扩展算法进行了改进，时间复杂度只有O（N）。
*/
class Solution {
public:
    int countSubstrings(string s) {
        //* 对字符串s进行处理，目标有两个。
        //* 假设处理后字符串命名为t，
        //* 1. 忽略s的长度，让t的长度一定是奇数
        //* 2. 让t开头和结尾的两个字符不相等，避免中心扩展时下标越界
        int n = s.size();
        string t = "$#";
        for (const char &c: s) {
            t += c;
            t += '#';
        }
        n = t.size();
        t += '!';

        auto f = vector<int> (n);
        int iMax = 0, rMax = 0, ans = 0;
        for (int i = 1; i < n; ++i) {
            //* 初始化 f[i]，
            //* f[i]表示在 t 中以 i 为中心的最大回文半径，
            //* 即从 i 到边界的元素个数（算上 i 和边界）。
            f[i] = (i <= rMax) ? min(rMax - i + 1, f[2 * iMax - i]) : 1;

            //* 中心拓展
            while (t[i + f[i]] == t[i - f[i]]) {
                ++f[i];
            }

            //* 动态维护 iMax 和 rMax
            if (i + f[i] - 1 > rMax) {
                iMax = i;
                rMax = i + f[i] - 1;
            }
            //* 用 f[i] 来表示以 t 的第 i 位为回文中心，可以拓展出的最大回文半径。
            //* 那么 f[i]−1 就是原字符串 s 当中
            //* 以 t[i] 为中心（t[i]不为#） 或者以 t[i] 两侧字母为中心（t[i]为#）
            //* 的最大回文串长度。
            //* 统计答案, 当前贡献为 (f[i] - 1) / 2 上取整
            ans += (f[i] / 2);
        }

        return ans;
    }
};
// @lc code=end

