/*
 * @lc app=leetcode.cn id=347 lang=cpp
 * 小顶堆（优先队列）
 ! [347] 前 K 个高频元素
 */

/* 
 * 思路：
 * 首先都是先用unordered_map计数，
 * 后续输出最大k个，
 * 我是用的map将所有值按频率排序后输出，（需要注意会有频率相同的值）
 * 题解用的priority_queue（小顶堆）只保存出现频率最高的k个
 * 
 * std::map：适用于需要根据键快速查找值，并且需要对元素按照键进行排序的场景，例如存储字典、统计单词出现的频率等。
 * std::priority_queue：适用于需要动态维护元素优先级，并且只关心优先级最高（或最低）元素的场景，例如任务调度、Dijkstra 算法等。
*/

// @lc code=start
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
using namespace std;

//* 我的解法，用map将所有值按频率排序后输出，（需要注意会有频率相同的值）
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //* 数值做key，频次做value
        unordered_map<int, int> cnt;
        for (int i : nums) {
            cnt[i]++;
        }

        //* 频次做key，数值做value（多个相同频次的数字用vector存储）
        //* 给的比较器是greater（即大于），内部是降序
        map<int, vector<int>, greater<int>> m;
        for (const auto& it : cnt) {
            m[it.second].push_back(it.first);
        }

        vector<int> result;
        for (const auto& it : m) {
            for (int num : it.second) {
                result.push_back(num);
                if (result.size() == k) {
                    return result;
                }
            }
        }
        return result;
    }
};

//* 题解解法，用priority_queue（小顶堆）只保存出现频率最高的k个
class Solution {
public:
    //* 小顶堆的比较函数
    class mycomparison {
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
            //! 注意这里是大于
            return lhs.second > rhs.second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        //* 要统计元素出现频率
        unordered_map<int, int> map;    //* map<nums[i], 对应出现的次数>
        for (int i = 0; i < nums.size(); i++) {
            map[nums[i]]++;
        }

        //* 对频率排序
        //* 定义一个小顶堆，大小为k
        //! 给的比较器函数是大于，但是是小顶堆，即堆顶是最小值
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

        //* 用固定大小为k的小顶堆，扫描所有频率的数值
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
            pri_que.push(*it);
            if (pri_que.size() > k) {   //* 如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
                pri_que.pop();
            }
        }

        //* 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--) {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }
        return result;

    }
};
// @lc code=end

