/*
 * @lc app=leetcode.cn id=22 lang=cpp
 * 回溯
 ! [22] 括号生成
 */

/*
 * 思路一：
 * 跟踪到目前为止放置的左括号和右括号的数目来判断序列是否仍然保持有效，
 * 在判断是否可以加左括号或者有括号。
 * 
 * 思路二：
 * 根据第一个左括号和对应右括号中间的括号对数i（0 <= i < n）来将问题划分为子问题。
*/

// @lc code=start
#include <vector>
#include <string>
#include <memory>
using namespace std;

/*
 * 题解思路一：
 * 在序列仍然保持有效时才添加 ‘(’ 或 ‘)’。
 * 通过跟踪到目前为止放置的左括号和右括号的数目来做到这一点
 * 如果左括号数量不大于 n，可以放一个左括号。
 * 如果右括号数量小于左括号的数量，可以放一个右括号。
*/
class Solution {
private:
    vector<string> result;
    string path = "";

    void backtracking(int left, int right, int n) {
        if (left == n && right == n) {
            result.push_back(path);
            return;
        }

        if (left < n) {
            path.push_back('(');
            backtracking(left+1, right, n);
            path.pop_back();
        }

        if (right < left) {
            path.push_back(')');
            backtracking(left, right+1, n);
            path.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        backtracking(0, 0, n);
        return result;
    }
};

/*
 * 题解思路二：
 * 任何一个括号序列都一定是由 ‘(’ 开头，并且第一个 ‘(’ 一定有一个唯一与之对应的 ‘)’。
 * 这样一来，每一个括号序列可以用 (a)b 来表示，其中 a 与 b 分别是一个合法的括号序列（可以为空）。
 * 那么，要生成所有长度为 2n 的括号序列，我们定义一个函数 generate(n) 来返回所有可能的括号序列。
 * 
 * 那么在函数 generate(n) 的过程中：
 * 我们需要枚举与第一个 ‘(’ 对应的 ‘)’ 的位置 2i+1（0 <= i < n，即a这个括号序列有几对括号）；
 * 递归调用 generate(i) 即可计算 a 的所有可能性；
 * 递归调用 generate(n−i−1) 即可计算 b 的所有可能性；
 * 遍历 a 与 b 的所有可能性并拼接，即可得到所有长度为 2n 的括号序列。
 * 
 * 为节省计算时间，在每次 generate(i) 函数返回之前，把返回值存储起来，
 * 下次再调用 generate(i) 时可以直接返回，不需要再递归计算。
*/
class Solution {
    shared_ptr<vector<string>> cache[100] = {nullptr};
public:
    shared_ptr<vector<string>> generate(int n) {
        if (cache[n] != nullptr)
            return cache[n];
        if (n == 0) {
            cache[0] = shared_ptr<vector<string>>(new vector<string>{""});
        } else {
            auto result = shared_ptr<vector<string>>(new vector<string>);
            for (int i = 0; i != n; ++i) {
                auto lefts = generate(i);
                auto rights = generate(n - 1 - i);
                //* 注意这里范围for遍历的是*lefts和*rights
                for (const string& left : *lefts)
                    for (const string& right : *rights)
                        result -> push_back("(" + left + ")" + right);
            }
            cache[n] = result;
        }
        return cache[n];
    }
    vector<string> generateParenthesis(int n) {
        return *generate(n);
    }
};
// @lc code=end

