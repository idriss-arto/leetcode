/*
 * @lc app=leetcode.cn id=438 lang=cpp
 * 滑动窗口，哈希
 ! [438] 找到字符串中所有字母异位词
 */

/*
 * 思路:
 * 滑动窗口加哈希
 ! (因为确定只用小写字母作为key，所以直接用数组模拟hash即可，不用unordered_map)
 * 滑动窗口移动时，左边出界的字母对应计数减一，右边新入界的字母对应计数加一
 ! 注意，两个vector可以直接用"=="来判断是否相等
 * 但效率不高，更进一步的优化思路是引入diff避免对两个数组的对比，详见下方代码
*/

// @lc code=start
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

//* 引入diff避免对两个数组的对比
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        //* pc 对字符串p中字母计次
        vector<int> pc(26);
        //* sc 对s的子串中字母计次
        vector<int> sc(26);
        for (int i = 0; i < p.length(); i++) {
            pc[p[i]-'a']++;
        }
        
        //* diff 记录当前s子串中还有几种字母与p不匹配
        int diff = 0;
        for (int i = 0; i < 26; i++) {
            if (pc[i] > 0) diff++;
        }

        //* left 指向子串开头，right 指向子串结尾
        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            
            sc[s[right]-'a']++;
            
            if (sc[s[right]-'a'] == pc[s[right]-'a']) diff--;

            if (right - left + 1 == p.length()) {
                if (diff == 0) res.push_back(left);

                int l = s[left] - 'a';
                sc[l]--;
                if (sc[l] == pc[l] - 1) diff++;
                left++;
            }
        }

        return res;
    }
};

//* 常规解法，滑动窗口加哈希
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; ++i) {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {
            --sCount[s[i] - 'a'];
            //* 如果SCount和pCount用的是unordered_map，需要加下面一行代码
            //* if (sCount[s[i]] == 0) sCount.erase(s[i]);
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount) {
                //! 此时s中子串开头位置为i + 1
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};

int main() {
    string s = "cbaebabacd", p = "abc";
    Solution a;
    vector<int> res(a.findAnagrams(s, p));
    return 0;
}
// @lc code=end

