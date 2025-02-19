/*
 * @lc app=leetcode.cn id=242 lang=cpp
 * 哈希
 * [242] 有效的字母异位词
 */

// @lc code=start
#include <string>
#include <unordered_map>
using namespace std;
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> cnt;
        for (int i = 0; i < s.length(); i++) {
            cnt[s[i]] += 1; 
        }
        for (int j = 0; j < t.length(); j++) {
            if(cnt[t[j]] > 1) {
                cnt[t[j]] -= 1;
            }
            else if (cnt[t[j]] == 1) {
                cnt.erase(t[j]);
            }
            else {
                return false;
            }
        }
        // 要判断empty必须先erase
        if (cnt.empty()) {
            return true;
        }
        else {
            return false;
        }
    }
};
// @lc code=end

