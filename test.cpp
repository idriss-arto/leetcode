/*
 * @lc app=leetcode.cn id=139 lang=cpp
 *
 * [139] 单词拆分
 */

// @lc code=start
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
class Solution {
    public:
        int lengthOfLIS(vector<int>& nums) {
            vector<int> tails(nums.size(), 0);
            int k = 0;
            tails[0] = nums[0];
    
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] > tails[k]) {
                    k++;
                    tails[k] = nums[i];

                    cout << "i=" << i << " " << "tails:";
                    for (int j = 0; j <= k; j++) {
                        cout << tails[j] << " ";
                    }
                    cout << endl;
                }
                else {
                    int left = 0, right = k;
                    int middle;
                    while (left < right) {
                        middle = (left + right) / 2;
                        if (tails[middle] < nums[i]) left = middle + 1;
                        else if (tails[middle] > nums[i]) right = middle;
                        else {
                            left = middle;
                            break;
                        }
                    }
                    tails[left] = nums[i];

                    cout << "i=" << i << " " << "left=" << left << " " << "right=" << right << " " << "tails:";
                    for (int j = 0; j <= k; j++) {
                        cout << tails[j] << " ";
                    }
                    cout << endl;
                }
            }
    
            return k+1;
        }
    };

int main() {
    Solution s;
    vector<int> x = {3,5,6,2,5,4,19,5,6,7,12};
    s.lengthOfLIS(x);
    return 0;
}
// @lc code=end

