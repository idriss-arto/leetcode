/*
 * @lc app=leetcode.cn id=17 lang=cpp
 * 回溯
 * [17] 电话号码的字母组合
 */

// @lc code=start
#include <vector>
#include <string>
using namespace std;
class Solution {
private:
    vector<string> result;      // 存放结果集
    string path;                // 一条路径
    const vector<vector <char>> dig{{'0'}, {'0'}, {'a','b','c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}
                            , {'j', 'k', 'l'}, {'m', 'n', 'o'}, {'p', 'q', 'r', 's'}
                            , {'t', 'u', 'v'}, {'w', 'x', 'y', 'z'}};
    /*
     * 也可以这样定义
    const string letterMap[10] = {
        "", // 0
        "", // 1
        "abc", // 2
        "def", // 3
        "ghi", // 4
        "jkl", // 5
        "mno", // 6
        "pqrs", // 7
        "tuv", // 8
        "wxyz", // 9
    };
    */
    void backtracking(string digits, int startIndex) {
        if (startIndex == digits.length()) {
            result.push_back(path);
            return ;
        }

        int i = digits[startIndex] - '0';
        for (char c : dig[i]) {
            path.push_back(c);
            backtracking(digits, startIndex + 1);
            path.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        result.clear(); // 可以不加
        path.clear();   // 可以不加
        if (digits.length() != 0) backtracking(digits, 0);
        return result;
    }
};
// @lc code=end

