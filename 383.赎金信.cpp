/*
 * @lc app=leetcode.cn id=383 lang=cpp
 * 哈希
 * [383] 赎金信
 */

// @lc code=start
#include <string>
#include <unordered_map>
using namespace std;
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> cnt;
        for (char c : magazine) {
            cnt[c]++;
        }
        for (char c : ransomNote) {
            if (cnt[c] < 1) {
                return false;
            }
            else {
                cnt[c]--;
            }
        }
        return true;
    }
};
// @lc code=end

