/*
 * @lc app=leetcode.cn id=3 lang=cpp
 * 滑动窗口
 ! [3] 无重复字符的最长子串
 */

/*
 * 滑动窗口，思路：
 * 如果我们依次递增地枚举子串的起始位置，那么子串的结束位置也是递增的！
 * 这里的原因在于，假设我们选择字符串中的第 k 个字符作为起始位置，
 * 并且得到了不包含重复字符的最长子串的结束位置为 r_k。
 * 那么当我们选择第 k+1 个字符作为起始位置时，首先从 k+1 到 r_k 的字符显然是不重复的，
 * 并且由于少了原本的第 k 个字符，我们可以尝试继续增大 r_k ，直到右侧出现了重复字符为止。
*/

// @lc code=start
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//* left指向子串的开头，right指向子串的结尾
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        //* map的key为字符，value为该字符在子串中出现的次数
        unordered_map<char, int> map;
        int res =0;
        for (int left = 0, right = 0; right<s.size(); right++ ){
            map[s[right]]++;
            while (map[s[right]] > 1) {
                //* 这里不会导致map[s[left]]小于0
                map[s[left]]--;
                left++;
            }
            res = max(res, right - left + 1);

        }
        return res;
        
    }
};

//* left指向子串开头，right指向下一步要加入子串的位置
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        //* 哈希集合，记录每个字符是否出现过
        unordered_set<char> set;
        int n = s.size();

        //* 右指针，初始值为 0，相当于我们在字符串的左边界，还没有开始移动
        int right = 0, ans = 0;
        //* 枚举左指针的位置
        for (int left = 0; left < n; ++left) {
            if (left != 0) {
                //* 左指针向右移动一格，移除一个字符
                set.erase(s[left - 1]);
            }
            while (right < n && !set.count(s[right])) {
                //* 不断地移动右指针
                set.insert(s[right]);
                ++right;
            }
            //* 从下标 left 开始的无重复字符子串最长到right前一个字符
            ans = max(ans, right - left);
        }

        return ans;
    }
};
// @lc code=end

