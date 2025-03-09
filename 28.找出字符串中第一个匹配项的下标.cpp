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
    //* 题解解法，运用KMP算法(最长公共前后缀思路)，O(m+n)
    //* 假设next[j]=k(k<=j)，这表示在0~j这j+1个字符组成的字符串中，最长公共前后缀的长度为k
    //* 也就是，0~(k-1)这k个字符与(j-k+1)~j这k个字符严格相等
    //* 所以当要匹配的字符与s[j+1]不一样时（s[j]及前面已完成匹配），
    //* 把要匹配的字符与s[k]对比即可
    void getNext(int* next, const string& s) {
        int j = 0;
        next[0] = 0;
        for(int i = 1; i < s.size(); i++) {
            while (j > 0 && s[i] != s[j]) {     //* j要保证大于0，因为下面有取j-1作为数组下标的操作
                j = next[j - 1];                //* 注意这里，是要找前一位的对应的回退位置
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

    //* 我的解法，暴力枚举，O(m*n)
    int myStrStr(string haystack, string needle) {
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
};
// @lc code=end

