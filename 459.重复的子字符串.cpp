/*
 * @lc app=leetcode.cn id=459 lang=cpp
 * 字符串，KMP
 * [459] 重复的子字符串
 */

/*
 * 思路：
 * 找由重复子字符串构成的字符串特有的性质
 * 发现如果是满足要求的s  <=>  s+s中去掉首字符和尾字符，还能找到s
 * =>:
 *      重复部分为abc，s为abcabc
 *      s+s中（去除首尾字符）拿前面那个s后面的abc，和后面那个s前面的abc，可构成一个s
 * <=:
 *      1234512345
 *      0012345000
 *      由上可以推出，3=1=4=2=5，其他例子同理
 * 
 * 所以问题转为找s+s中（去除首尾字符）的s
 * 
 * 字符串s是由重复子串组成  <=>  最长相等前后缀不包含的子串是字符串s的最小重复子串。
 * =>:
 * 
 * <=:
 *      最长相等前后缀不包含的子串已经是字符串s的最小重复子串，那么字符串s一定由重复子串组成，这个不需要证明了。
 *      关键是要证明：最长相等前后缀不包含的子串什么时候才是字符串s的最小重复子串呢。
 *      情况一：不包含的子串长度大于s一半
 *      情况二：不包含的子串长度能被s长度整除
 *      情况三：不包含的子串长度不能被s长度整除
*/

// @lc code=start
#include<string>
using namespace std;
class Solution {
public:
    void getNext (int* next, const string& s){
        next[0] = 0;
        int j = 0;
        for(int i = 1;i < s.size(); i++){
            while(j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            }
            if(s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern (string s) {
        if (s.size() == 0) {
            return false;
        }
        int next[s.size()];
        getNext(next, s);
        int len = s.size();
        //! 当最长相等前后缀不包含的子串的长度,可以被字符串s的长度整除，那么不包含的子串就是s的最小重复子串。
        if (next[len - 1] != 0 && len % (len - (next[len - 1] )) == 0) {
            return true;
        }
        return false;
    }
};
// @lc code=end

