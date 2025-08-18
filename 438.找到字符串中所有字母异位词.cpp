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
        vector<int> result;
        if (s.size() < p.size()) {
            return result;
        }

        //* cnt 记录每个字母在 s 和 p 中出现的次数差
        vector<int> cnt(26, 0);
        for (int i = 0; i < p.size(); i++) {
            cnt[s[i] - 'a']++;
            cnt[p[i] - 'a']--;
        }

        //* differ 记录 s子串 和 p 中出现频次不同的字母的个数
        int differ = 0;
        for (const int & num : cnt) {
            if (num != 0) differ++;
        }

        //* differ 为 0 时，说明 s子串 和 p 是异位词
        if (differ == 0) {
            result.push_back(0);
        }
        
        for (int i = p.size(); i < s.size(); i++) {
            if (cnt[s[i-p.size()] - 'a'] == 0) {
                differ++;
            }
            cnt[s[i-p.size()] - 'a']--;     //* 左边出界的字母对应计数减一，减前减后都要进行判断，对应 differ 不同变化
            if (cnt[s[i-p.size()] - 'a'] == 0) {
                differ--;
            }

            if (cnt[s[i] - 'a'] == 0) {
                differ++;
            }
            cnt[s[i] - 'a']++;              //* 右边新入界的字母对应计数加一，加前加后都要进行判断，对应 differ 不同变化
            if (cnt[s[i] - 'a'] == 0) {
                differ--;
            }

            if (differ == 0) {              //* differ 为 0 时，说明 s子串 和 p 是异位词
                result.push_back(i - p.size() + 1);
            }
        }

        return result;
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

