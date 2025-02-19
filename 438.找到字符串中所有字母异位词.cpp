/*
 * @lc app=leetcode.cn id=438 lang=cpp
 * 滑动窗口，哈希
 * [438] 找到字符串中所有字母异位词
 */

// @lc code=start
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    unordered_map<char, int>cnt1, cnt2;

    bool check() {
        for(auto it : cnt1) {
            if (it.second > cnt2[it.first]) {
                return false;
            }
        }
        return true;
    }



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
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount) {
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

