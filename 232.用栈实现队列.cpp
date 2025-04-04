/*
 * @lc app=leetcode.cn id=232 lang=cpp
 * 栈和队列
 * [232] 用栈实现队列
 */

/*
 * 思路：
 * 因为栈是先进后出，所以得用两个栈来模拟队列
 * 一个栈专门用来处理queue.push，一个栈专门用来处理queue.pop
 * 在queue.push时，直接装入push栈即可
 * 在queue.pop的时候，如果对应pop栈为空，则从push栈中把所有现有数据挪到pop栈中
*/

// @lc code=start
#include <stack>
using namespace std;
class MyQueue {
public:
    stack<int> stIn;
    stack<int> stOut;
    /** Initialize your data structure here. */
    MyQueue() {

    }
    /** Push element x to the back of queue. */
    void push(int x) {
        stIn.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        //* 只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
        if (stOut.empty()) {
            //* 从stIn导入数据直到stIn为空
            while(!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    /** Get the front element. */
    int peek() {
        int res = this->pop();      //* 直接使用已有的pop函数
        stOut.push(res);            //* 因为pop函数弹出了元素res，所以再添加回去
        return res;
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return stIn.empty() && stOut.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// @lc code=end

