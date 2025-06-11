/*
 * @lc app=leetcode.cn id=17 lang=cpp
 * 回溯(不同集合的组合)
 * [17] 电话号码的字母组合
 */

/*
 * 思路：
 * 回溯经典的问题，也可以说是dfs
 * 先确定每个数字能对应的字母集合
 * 在回溯函数里，用index表明现在是digits第几位数字，
 * 再根据现在指向的数字，依次取字母表里的字母，然后dfs进入下一层
 * index超过要处理的范围时，说明得到一个结果，将结果加入结果集，然后返回上一层
*/

// @lc code=start
#include <vector>
#include <string>
using namespace std;
class Solution {
private:
    vector<string> result;      //* 存放结果集
    string path;                //* 一条路径
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

    void backtracking(string digits, int index) {
        if (index == digits.length()) {
            result.push_back(path);
            return ;
        }

        int i = digits[index] - '0';
        for (char c : dig[i]) {
            path.push_back(c);
            backtracking(digits, index + 1);
            path.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        result.clear(); //* 可以不加
        path.clear();   //* 可以不加
        if (digits.length() != 0) backtracking(digits, 0);  //* 必须有这个判断，否则digits长度为0时结果会多一个空串
        return result;
    }
};
// @lc code=end

