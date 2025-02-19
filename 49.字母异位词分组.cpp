/*
 * @lc app=leetcode.cn id=49 lang=cpp
 * 哈希
 * [49] 字母异位词分组
 */

// @lc code=start
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
class Solution {
public:
    // 排序string作为unordered_map的key，原string作为value
    vector<vector<string>> groupAnagramsWithSort(vector<string>& strs) {
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
        return ans;
    }

    // 用对string中字母出现次数的计次结果作为unordered_map的key
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (string str : strs) {
            vector<int> cnt(26, 0);
            for (char c : str) {
                cnt[c-'a']++;
            }
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
// @lc code=end

