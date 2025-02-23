/*
 * @lc app=leetcode.cn id=28 lang=cpp
 * 字符串，KMP
 * [28] 找出字符串中第一个匹配项的下标
 */

// @lc code=start
#include<string>
#include <vector>
using namespace std;
class Solution {
public:
    int strStr(string haystack, string needle) {
        int len1 = haystack.size() - 1;
        int len2 = needle.size() - 1;
        int pos = -1;
        for (int i = 0; i <= len1; i++) {
            if (haystack[i] == needle[0]) {
                int flag = 1;
                for(int j = 0; j <= len2; j++) {
                    if (haystack[i + j] != needle[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    pos = i;
                    break;
                }
            }
        }
        return pos;
    }

    void getNext(int* next, const string& s) {
        int j = 0;
        next[0] = 0;
        for(int i = 1; i < s.size(); i++) {
            while (j > 0 && s[i] != s[j]) {     // j要保证大于0，因为下面有取j-1作为数组下标的操作
                j = next[j - 1];                // 注意这里，是要找前一位的对应的回退位置了
            }
            if (s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
    }

    int strStrWithKMP(string haystack, string needle) {
        if (needle.size() == 0) {
            return 0;
        }
        vector<int> next(needle.size());
        getNext(&next[0], needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while(j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == needle.size() ) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};
// @lc code=end

