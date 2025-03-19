/*
 * @lc app=leetcode.cn id=135 lang=cpp
 * 贪心
 * [135] 分发糖果
 */

// @lc code=start
#include <vector>
#include <climits>
using namespace std;
class Solution {
public:
    /* 
     * 题解的思路：一边之后，再确定另一边，例如比较每一个孩子的左边，然后再比较右边，如果两边一起考虑一定会顾此失彼。
     * 先确定右边评分大于左边的情况（也就是从前向后遍历）
     * 此时局部最优：只要右边评分比左边大，右边的孩子就多一个糖果，
     * 全局最优：相邻的孩子中，评分高的右孩子获得比左边孩子更多的糖果
     * 再确定左孩子大于右孩子的情况（从后向前遍历）
     * 如果当前位置i分数大于右边位置分数
     * 那么candy[i] = max(candy[i], candy[i+1]+1)，保证第i个小孩的糖果数量既大于左边的也大于右边的。
    */
    int candy(vector<int>& ratings) {
        vector<int> candyVec(ratings.size(), 1);
        //* 从前向后
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) candyVec[i] = candyVec[i - 1] + 1;
        }
        //* 从后向前
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1] ) {
                candyVec[i] = max(candyVec[i], candyVec[i + 1] + 1);
            }
        }
        //* 统计结果
        int result = 0;
        for (int i = 0; i < candyVec.size(); i++) result += candyVec[i];
        return result;
    }

    /* 
     * 我的思路，找到评分最低的孩子，向左右两边确认给糖个数
     * 向左右两边确认时，遇到分数更高的，就给比现在多一个，遇到分数更低的，直接重置为1
     * 直接重置的话，可能导致错误，比如分数为[1,4,3,2,1]，按照我上面的想法，给的糖为[1,2,1,1,1]
     * 发现违反规定二
     * 所以做出补充，遇到分数更低的，如果当前给的已经是1了，没法给更少了，只能让当前给2，前面确定的值也要递归修改
     * [1]->[1,2]->[1,2,1]->[1,2,1,1]->[发现错误]->[1,3,2,1]->[1,3,2,1,1]->[发现错误]->[1,4,3,2,1]
     * 递归修改也有易错点
     * 总之这个方法不好
    */
    int myCandy(vector<int>& ratings) {
        vector<int> candy(ratings.size(), 0);
        int minScore = INT_MAX;
        int minPlace = -1;
        for (int i = 0; i < ratings.size(); i++) {
            if (ratings[i] < minScore) {
                minScore = ratings[i];
                minPlace = i;
            }
        }

        int sumCandy = 1;
        candy[minPlace] = 1;
        for (int i = minPlace - 1; i >= 0; i--) {
            if (ratings[i] > ratings[i+1]) {
                candy[i] = candy[i+1] + 1;
                sumCandy += candy[i];
            }
            else {
                if (ratings[i] < ratings[i+1] && candy[i+1] == 1) {
                    candy[i] = 1;
                    int j = i + 1;
                    while (ratings[j] > ratings[j - 1] && candy[j] - candy[j - 1] <= 0) {
                        candy[j] += 1;
                        sumCandy += 1;
                        j++;
                    }
                }
                else candy[i] = 1;
            }
        }
        for (int i = minPlace + 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i-1]) {
                candy[i] = candy[i-1] + 1;
                sumCandy += candy[i];
            }
            else {
                if (ratings[i] < ratings[i-1] && candy[i-1] == 1) {
                    candy[i] = 1;
                    int j = i - 1;
                    while (ratings[j] > ratings[j + 1] && candy[j] - candy[j + 1] <= 0) {
                        candy[j] += 1;
                        sumCandy += 1;
                        j++;
                    }
                }
                else candy[i] = 1;
            }
        }
        return sumCandy;
    }
};
// @lc code=end

