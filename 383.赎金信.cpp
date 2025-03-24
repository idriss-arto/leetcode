/*
 * @lc app=leetcode.cn id=383 lang=cpp
 * 哈希
 * [383] 赎金信
 */

/*
 * 思路：
 * 没什么好说的，把杂志里的字母全部统计一遍，再去遍历赎金信，出现字母不够的情况返回false
 * 题目中string只由小写字母组成，可以用数组模拟hash
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

