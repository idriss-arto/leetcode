/*
 * @lc app=leetcode.cn id=49 lang=cpp
 * 哈希
 ! [49] 字母异位词分组
 */

/*
 * 思路：
 * 法一：排序后的string作为unordered_map的key，原string作为value。
 * 法二：用对string中字母出现次数的计次结果作为unordered_map的key。
*/

// @lc code=start
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

//* 排序后的string作为unordered_map的key，原string作为value
//* 假设有n个字符串，每个字符串长度为m，时间复杂度为O(m*log(m)*n)
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string& str: strs) {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }

        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        /*
         * 对map的遍历和提取元素也可以这样写
        for (auto& it : map) {
            ans.push_back(it.second);
        }
        */
        return ans;
    }
};

/*
 * 用对string中字母出现次数的计次结果作为unordered_map的key
 * 假设有n个字符串，每个字符串长度为m，时间复杂度为O(m*n)
 * 实际效果不好，因为得把计数结果转为string
 * 要发挥这个方案优势，需要手写vector<int>到string的hash函数
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (string str : strs) {
            //* 对string中字母出现频次计数
            vector<int> cnt(26, 0);
            for (char c : str) {
                cnt[c-'a']++;
            }

            //* 用计数结果当做key，如"aaabbc"转换为key为"32100...00"
            string key = "";
            for (auto p : cnt) {
                key.push_back(p);
            }
            map[key].push_back(str);
        }

        vector<vector<string>> res;
        for(auto& p : map) {
            res.push_back(p.second);
        }

        return res;
    }
};

//* 对上面方法的改良，直接用string放计数结果，就不用从数组转为string
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (string str : strs) {
            //* 对string中字母出现频次计数
            string cnt(26, 0);
            for (char c : str) {
                cnt[c-'a']++;
            }
            map[cnt].push_back(str);
        }

        vector<vector<string>> res;
        for(auto& p : map) {
            res.push_back(p.second);
        }

        return res;
    }
};
// @lc code=end

