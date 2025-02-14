/*
 * @lc app=leetcode.cn id=904 lang=cpp
 * 滑动窗口
 * [904] 水果成篮
 */

/*
思路：
让end向右滑动，直到遇到不等于first或second的水果（滑动过程中更新result，
如果写成遇到第三种水果再更新，在只有两种水果时会返回0，如[0,1,0]）

end指向第三种水果后，second = fruits[end]
但是first不能直接取second，要从end位置向前遍历，直到遇到第一个区别于second的水果，否则first可能取错
如[1,0,1,4,1,4,1,2,3]，当end指向第一个4时，second为0，要更新为4。first为1，要更新为1。
first确定取值后，要向前遍历确定begin位置。
*/

// @lc code=start
#include<vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int result = 0, first = fruits[0], second = -1;
        int begin = 0, end = 0;
        for(; end < fruits.size(); end++)
        {
            if(fruits[end] == first || fruits[end] == second)
            // 可以摘的水果，放入篮子
            {
                int subL = end - begin + 1;
                result = (result > subL ? result : subL);
                continue;
            }
            else
            // 新水果，判断第二个篮子是否为空
            {
                if(second == -1)
                // 第二个篮子为空，放入新水果
                {
                    second = fruits[end];
                    int subL = end - begin + 1;
                    result = (result > subL ? result : subL);
                    continue;
                }
                else
                // 第二个篮子不为空
                {
                    second = fruits[end];
                    begin = end - 1;
                    first = fruits[begin];
                    while(begin >= 0 && (fruits[begin - 1] == first || fruits[begin - 1] == second))
                    {
                        begin--;
                    }
                    int subL = end - begin + 1;
                    result = (result > subL ? result : subL);
                }
            }
            
        }
        return result;
    }

    int totalFruitWithHash(vector<int>& fruits) {
        int n = fruits.size();
        unordered_map<int, int> cnt;

        int left = 0, ans = 0;
        for (int right = 0; right < n; ++right) 
        {
            ++cnt[fruits[right]];
            while (cnt.size() > 2)                      // 等效于kinds > 2
            {
                auto it = cnt.find(fruits[left]);       // 返回key为fruits[left]的键值对在哈希桶中的位置
                --it->second;                           // key为fruits[left]的键值对对应值减一
                if (it->second == 0) {                  // 直到key为fruits[left]的键值对对应值为0，即某个篮子空了
                    cnt.erase(it);
                }
                ++left;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
// @lc code=end

