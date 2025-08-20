/*
 * @lc app=leetcode.cn id=738 lang=cpp
 * 贪心
 ! [738] 单调递增的数字
 */

/*
 * 思路：
 * 先将输入的数字 N 转换为字符串 strNum ，便于处理。
 * 一旦出现strNum[i - 1] > strNum[i]的情况（非单调递增），
 * 首先先让strNum[i - 1]减一，strNum[i]和后面的位赋值9。
 ! 注意，只能从后往前处理，332->329->299，4436->4399->3999
 * 从前往后的话，strNum[i - 1]减一后可能小于strNum[i - 2]，之前判断通过的位置现在不行了，如332->329
*/

// @lc code=start
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        //* 转换为字符串更好处理
        string strNum = to_string(N);

        //* flag用来标记赋值9从哪里开始
        //* 设置为这个默认值，为了防止第二个for循环在flag没有被赋值的情况下执行
        int flag = strNum.size();

        for (int i = strNum.size() - 1; i > 0; i--) {
            if (strNum[i - 1] > strNum[i] ) {
                flag = i;
                strNum[i - 1]--;
            }
        }

        //* 如果之前的遍历里出现过非单调递增的情况，则将flag及之后的位置为9
        for (int i = flag; i < strNum.size(); i++) {
            strNum[i] = '9';
        }
        return stoi(strNum);
    }
};
// @lc code=end

