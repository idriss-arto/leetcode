/*
 * @lc app=leetcode.cn id=239 lang=cpp
 * 单调队列
 ! [239] 滑动窗口最大值
 */

/*
 * 思路：
 * 不能用优先级队列（堆），因为如果离开滑动窗口的值不是最大值，无法从大顶堆中删去对应元素
 * 
 * 但如果存入优先级队列的元素是<数据, 数据下标>，
 * 可以用下标判断当前最大值是否离开滑动窗口范围，
 * 直到找到滑动窗口内的最大值
 * 
 * 此外可以使用自定义单调队列来实现，
 * 插入时传入要插入的值，将队列尾小于该值的元素全部弹出，再在队尾插入该值
 * 弹出时传入要弹出的值，判断是否等于队头元素，等于的话再弹出队头
 * 因为队头队尾都可能弹出元素，所以用deque来实现单调队列
*/

// @lc code=start
#include <queue>
#include <set>
using namespace std;

//* 单调队列，时间复杂度O(n)，空间复杂度O(k)
//* 执行用时45ms
class Solution {
private:
    class MyQueue {     //* 单调队列（从大到小）
    public:
        deque<int> que; //! 使用deque来实现单调队列

        //* 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
        //* 同时pop之前判断队列当前是否为空。
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }

        //* 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
        //* 这样就保持了队列里的数值是单调从大到小的了。
        void push(int value) {
            while (!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);

        }
        
        //* 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
        int front() {
            return que.front();
        }
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result;
        for (int i = 0; i < k; i++) {       //* 先将前k个元素放进队列
            que.push(nums[i]);
        }
        result.push_back(que.front());      //* result 记录前k个元素的最大值
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]);           //* 滑动窗口移除最前面元素
            que.push(nums[i]);              //* 滑动窗口前加入最后面的元素
            result.push_back(que.front());  //* 记录对应的最大值
        }
        return result;
    }
};

//* multiset实现单调队列
//* 执行用时450ms
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //! multiset底层是红黑树，默认用less比较器，升序
        multiset<int> set;
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            //! 关键步骤，滑动窗口移除最前面元素
            if (i >= k) set.erase(set.find(nums[i - k]));

            //* 滑动窗口前加入最后面的元素
            set.insert(nums[i]);

            //* 注意这里加入ans的是rbegin，即set的末尾
            if (i >= k - 1) ans.push_back(*set.rbegin());
        }
        return ans;
    }
};

//* 优先队列，时间复杂度O(nlogn)，空间复杂度O(n)
//* 执行用时130ms
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        //! priority_queue底层是堆，默认用less比较器，降序
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < k; ++i) {
            q.emplace(nums[i], i);
        }
        //* 存第一个最大值
        vector<int> ans = {q.top().first};
        for (int i = k; i < n; ++i) {
            //! 必须先插入再删除，否则下面的删除可能删到q为空
            q.emplace(nums[i], i);
            //! 删除已经离开滑动窗口范围的值
            while (q.top().second <= i - k) {
                q.pop();
            }
            ans.push_back(q.top().first);
        }
        return ans;
    }
};
// @lc code=end

