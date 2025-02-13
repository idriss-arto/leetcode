/*
 * @lc app=leetcode.cn id=345 lang=cpp
 * 双指针
 * [345] 反转字符串中的元音字母
 */

// @lc code=start
#include<string>
#include <unordered_set>
using namespace std;
class Solution {
public:
    string reverseVowels(string s) {
        // unordered_set的使用，用来查是否存在某个元素
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        /*
        另一个方案：lambda表达式
        auto isVowel = [vowels = "aeiouAEIOU"s](char ch) {
            return vowels.find(ch) != string::npos;
        };
        auto关键字用于自动推导函数的类型。
        [vowels = "aeiouAEIOU"s]是 lambda 的捕获列表，
        这里采用了拷贝捕获的方式，将字符串"aeiouAEIOU"赋值给vowels，
        使得在 lambda 函数内部可以使用该字符串。
        (char ch)表示函数接受一个字符类型的参数ch。

        "aeiouAEIOU"s最后的s是 C++14 引入的字符串字面量后缀。
        它的作用是将普通字符串字面量转换为std::string类型。
        */
        
        int left = 0, right = s.length();
        while(left <= right)
        {
            while(left <= s.length() && !vowels.count(s[left]))
            {
                left++;
            }
            while(right >= 0 && !vowels.count(s[right]))
            {
                right--;
            }
            if(left >= right)
            {
                break;
            }

            swap(s[left++], s[right--]);
        }
        return s;
    }
};
// @lc code=end


