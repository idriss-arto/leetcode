/*
 * @lc app=leetcode.cn id=860 lang=cpp
 * 贪心
 * [860] 柠檬水找零
 */

/*
 * 没什么难度，唯一注意的是遇到账单20时优先拿一个美元10和一个美元5找零，
 * 因为美元10只能给账单20找零，而美元5可以给账单10和账单20找零，美元5更万能
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
                if (cnt10 > 0 && cnt5 > 0) {
                    cnt5--;
                    cnt10--;
                    break;
                }
                if (cnt5 >= 3) {
                    cnt5 -= 3;
                    break;
                }
                return false;
            
            default:
                break;
            }
        } 
        return true;
    }
};
// @lc code=end

