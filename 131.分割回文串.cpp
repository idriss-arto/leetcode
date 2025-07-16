/*
 * @lc app=leetcode.cn id=131 lang=cpp
 * 回溯(分割)
 * [131] 分割回文串
 */

/*
 * 思路大致差不多
 * 都是找能生成回文串的切割位置，再递归进入剩下串的处理
 * 
 * 区别在于判断回文串的方法
 * 法一：临时传入串，通过双指针判断传入串是否为回文串。有很多重复计算
 * 法二：用动态规划预处理整个串，记录从i到j是否是回文串（i、j变化）
*/ 

// @lc code=start
#include <vector>
#include <string>
using namespace std;

//* 动态规划预处理，判断回文串
class Solution {
private:
    vector<vector<string>> result;
    vector<string> path;    //* 放已经回文的子串
    vector<vector<bool>> isPalindrome;  //* 放事先计算好的是否回文子串的结果

    //* 动态规划预处理判断子串是否为回文串
    //* isPalindrome[i][j] 代表 s[i:j](闭区间)是否是回文字串 
    //* isPalindrome[i][j] 由 isPalindrome[i+1][j-1] 推出
    void computePalindrome(const string& s) {
        isPalindrome.resize(s.size(), vector<bool>(s.size(), false));   //* 根据字符串s, 刷新布尔矩阵的大小

        for (int i = s.size() - 1; i >= 0; i--) { 
            //* 需要倒序计算, 保证在i行时, i+1行已经计算好了
            for (int j = i; j < s.size(); j++) {
                if (j == i) {
                    isPalindrome[i][j] = true;
                }
                else if (j - i == 1) {
                    isPalindrome[i][j] = (s[i] == s[j]);
                }
                else {
                    //* 从此处状态转移方程可以看出，求isPalindrome[i][j]时要求isPalindrome[i+1][j-1]已算好
                    //* 即i从大往小遍历，j从小往大遍历
                    isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i+1][j-1]);
                }
            }
        }
    }

    //* 回溯函数，进行分割
    void backtracking (const string& s, int startIndex) {
        //* 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
        if (startIndex >= s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isPalindrome[startIndex][i]) {      //* 是回文子串
                //* 获取[startIndex,i]在s中的子串
                string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
                backtracking(s, i + 1); //* 寻找i+1为起始位置的子串
                path.pop_back();        //* 回溯过程，弹出本次已经添加的子串
            }
            else {                                //* 不是回文，跳过
                continue;
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        result.clear();
        path.clear();
        computePalindrome(s);
        backtracking(s, 0);
        return result;
    }
};

//* 双指针判断回文串，有重复计算
class Solution {
private:
    vector<vector<string>> result;
    vector<string> path;    //* 放已经回文的子串

    //* 双指针判断输入的s从start到end的子串是否为回文串
    bool isPalindrome(const string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }

    //* 回溯函数，进行分割
    void backtracking (const string& s, int startIndex) {
        //* 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
        if (startIndex >= s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (!isPalindrome(s, startIndex, i)) {  //* 不是回文，跳过                                
                continue;
            }
            //* 是回文子串
            //* 获取[startIndex,i]在s中的子串
            string str = s.substr(startIndex, i - startIndex + 1);
            path.push_back(str);
            backtracking(s, i + 1);                 //* 寻找i+1为起始位置的子串
            path.pop_back();                        //* 回溯过程，弹出本次已经添加的子串
        }
    }
    
public:
    vector<vector<string>> partition(string s) {
        result.clear();
        path.clear();
        backtracking(s, 0);
        return result;
    }
};
// @lc code=end

