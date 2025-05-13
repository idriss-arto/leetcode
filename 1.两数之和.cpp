/*
 * @lc app=leetcode.cn id=1 lang=cpp
 * 哈希
 ! [1] 两数之和
 */

/*
 * 思路：
 * 因为需要返回下标，所以不能排序改变顺序
 * 因为数据边界不确定（不能用vector或数组），并且需要同时存储元素和位置下标（不能用set），所以用map
 * 用map，用{nums[i],i}作为键值对，即数组里数的值为key，数的位置为value
 * 可能存在一个问题，就是数的值出现重复，然而map里key不允许重复
 * 我的思路全插完再搜，题解的思路搜完再插
 * 我的思路里，出现重复的key，直接忽略，但可能是需要留下的，比如target=6时，[3,3]和[1,1,2,4]处理不一样
 * 题解的思路可以避免这个问题
*/

// @lc code=start
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    //! 边插边搜，同时处理map不能出现同样的键的问题
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map <int,int> map;
        for(int i = 0; i < nums.size(); i++) {
            //* 遍历当前元素，并在map中寻找是否有匹配的key
            auto iter = map.find(target - nums[i]); 
            if(iter != map.end()) {
                return {iter->second, i};
            }

            //* 避免target = 6，输入为[1,1,2,4]时key重复为1的情况
            //* 也可以用if (mp.count(nums[i]))，但不能用if (mp[nums[i]])
            if (map.find(nums[i]) != map.end()) {
                continue;
            }
            //* 如果没找到匹配对，就把访问过的元素和下标加入到map中
            map.insert(pair<int, int>(nums[i], i)); 

            /*
             * 上述对map的find操作可换为count，代码如下
            if (map.count(target - nums[i]) > 0) {
                return {map[target-nums[i]], i};
            }
            else {
                map[nums[i]] = i;
            }
            */
        }
        return {};
    }

    //! 插完再搜，有误
    vector<int> myTwoSum(vector<int>& nums, int target) {
        vector<int> res;
        unordered_map <int, int> place;

        /* 
         * 这样写i不是下标，是元素
         * for (int i : nums) {
         *     place[nums[i]] = i;
         * }
        */

        for (int i = 0; i < nums.size(); i++) {
            place[nums[i]] = i;
        }

        for (int i = 0; i <= nums.size() / 2; i++) {
            if ((nums[i] + nums[i] != target) && (place.count(target - nums[i]))) {
                res.push_back(i);
                res.push_back(place[target - nums[i]]);
                break;
            }
        }

        return res;
    }
};
// @lc code=end

