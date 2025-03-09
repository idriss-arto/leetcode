/*
 * @lc app=leetcode.cn id=15 lang=cpp
 * 哈希，或者双指针（一定要排序）
 * [15] 三数之和
 */

// @lc code=start
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;
class Solution {
public:
    //* 双指针
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                if (nums[i] + nums[left] + nums[right] == 0) {
                    //* 找到一个三元组后，去重相同的b和c
                    if (right < nums.size() - 1 
                        && nums[left] == nums[left - 1] 
                        && nums[right] == nums[right + 1]) {
                        left++;
                        right--;
                        continue;
                    }
                    result.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;
                }
                else if (nums[i] + nums[left] + nums[right] < 0) {
                    left++;
                }
                else {
                    right--;
                }
            }
            /*
            while的另一种写法
            while (right > left) {
                去重复逻辑如果放在这里，0，0，0 的情况，可能直接导致 right<=left 了，从而漏掉了 0,0,0 这种三元组
                //* while (right > left && nums[right] == nums[right - 1]) right--;
                //* while (right > left && nums[left] == nums[left + 1]) left++;
                if (nums[i] + nums[left] + nums[right] > 0) right--;
                else if (nums[i] + nums[left] + nums[right] < 0) left++;
                else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    //* 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;

                    找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
            }
            */
        }
        return result;
    }

    //* 可以用hash，但去重很麻烦
    //* 在一个数组中找到3个数形成的三元组，它们的和为0，不能重复使用（三数下标互不相同），且三元组不能重复。
    //* b（存储）== 0-(a+c)（检索）
    vector<vector<int>> threeSumWithHash(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size(); i++) {
            //* 如果a是正数，a<b<c，不可能形成和为0的三元组
            if (nums[i] > 0) {
                break;
            }
            
            //* [a, a, ...] 如果本轮a和上轮a相同，那么找到的b，c也是相同的，所以去重a
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            //* 这个set的作用是存储b
            unordered_set<int> set;
            
            for (int k = i + 1; k < nums.size(); k++) {
                //* 去重
                //* 如果只判断(k>i+1 && nums[k]==nums[k-1])的话，会错过a+b+c等于0，但b=c的特殊情况
                //* 多判断一次，当a固定，b=c=d时，不管a+b+c是否为0，在循环到c时都已记录，显然不应该记录a+b+d
                if (k > i + 2 && nums[k] == nums[k - 1] && nums[k - 1] == nums[k - 2]) {
                    continue;
                }
                
                //* a+b+c=0 <=> b=0-(a+c)
                int target = 0 - (nums[i] + nums[k]);
                if (set.find(target) != set.end()) {
                    result.push_back({nums[i], target, nums[k]});   //* nums[k]成为c
                    set.erase(target);
                }
                else {
                    set.insert(nums[k]);                            //* nums[k]成为b
                }
            }
        }

        return result;
    }
};
// @lc code=end

