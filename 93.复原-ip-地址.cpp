/*
 * @lc app=leetcode.cn id=93 lang=cpp
 * 回溯(分割)
 * [93] 复原 IP 地址
 */

/*
 * 思路：
 * 从index位置试着切割，最多试到index+2（因为字段最多为三位数）
 * 如果切割的结果符合要求：0，大于0且非0开头且小于255
 * 则递归处理剩下的数字
 * 数字处理完时，如果刚好得到四个字段，说明成功找到一种可能
*/

// @lc code=start
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    vector<string> result;
    vector<int> path;

    void backtracking(string s, int index) {
        if (index > s.length() - 1 && path.size() == 4) {
            string a;
            for (int i = 0; i <= 3; i++) {
                a += to_string(path[i]);
                if (i != 3) a += '.';
            }
            result.push_back(a);
            return;
        }
        for (int i = index; i <= s.length() - 1 && i <= index + 2; i++) {
            string cur = s.substr(index, i - index + 1);
            if (cur.size() > 1 && cur[0] == '0') return;
            int num = stoi(cur);
            if (num >= 0 && num <= 255) {
                path.push_back(num);
                backtracking(s, i + 1);
                path.pop_back();
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        backtracking(s, 0);
        return result;
    }
};
// @lc code=end

