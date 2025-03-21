/*
 * @lc app=leetcode.cn id=134 lang=cpp
 * 贪心
 * [134] 加油站
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    /* 
     * 令rest[i] = gas[i] - cost[i];
     * 显然只有rest[i]>=0的位置才可能成为起点
     * 找到起点后，一步一步向后走，同时用nowGas统计是否有能力到下一站
     * 若到位置j，nowGas小于0，说明[0, j]不可能是起点
     * 如果找到数组末尾，没找到起点，说明没有方案开一圈
     * 到数组末尾时有起点的话，继续向后开看能不能开满一圈
    */
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start = -1;
        int nowGas = 0;
        
        vector<int> rest(gas.size(), 0);
        for (int i = 0; i < gas.size(); i++) {
            rest[i] = gas[i] - cost[i];
            //* 只有rest[i]>=0的位置才可能成为起点，当然前提是之前的起点已经作废
            if (rest[i] >= 0 && start == -1) {
                start = i;
                nowGas = rest[i];
                continue;
            }
            //* 找到起点后，一步一步向后走，同时用nowGas统计是否有能力到下一站
            if (start != -1) {
                nowGas += rest[i];
                //* 没有能力到下一站了，说明0站到目前站中间都没有合适的起点
                if (nowGas < 0) {
                    start = -1;
                    nowGas = 0;
                    continue;
                }
            }
        }
        
        if (start == -1) return start;
        
        //* 注意，上面遍历时已经支付了从start到最后一个站，再到0站的cost
        int cur = 0;
        while (cur != start) {
            nowGas += rest[cur];
            if (nowGas < 0) return -1;
            cur++;
        }
        return start;
    }
};
// @lc code=end

