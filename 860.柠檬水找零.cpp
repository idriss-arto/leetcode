/*
 * @lc app=leetcode.cn id=860 lang=cpp
 * 贪心
 * [860] 柠檬水找零
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int cnt5 = 0;
        int cnt10 = 0;
        for (int i = 0; i < bills.size(); i++) {
            switch (bills[i])
            {
            case 5:
                cnt5 += 1;
                break;
            
            case 10:
                if (cnt5 == 0) return false;
                else {
                    cnt5--;
                    cnt10++;
                }
                break;
            
            case 20:
                if (cnt10 > 0) {
                    if (cnt5 > 0) {
                        cnt5--;
                        cnt10--;
                    }
                    else return false; 
                }
                else {
                    if (cnt5 >= 3) {
                        cnt5 -= 3;
                    }
                    else return false;
                }
                break;
            
            default:
                break;
            }
        } 
        return true;
    }
};
// @lc code=end

