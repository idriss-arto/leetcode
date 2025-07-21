/*
 * @lc app=leetcode.cn id=155 lang=cpp
 * 栈
 * [155] 最小栈
 */

// @lc code=start
#include <stack>
#include <climits>
using namespace std;

//* 我的解法
//* 辅助栈不完全同步
class MinStack {
private:
    stack<int> minSta;
    stack<int> sta;

public:
    MinStack() {
        
    }
    
    //* 压栈时，如果当前值小于等于辅助栈的栈顶，则压入辅助栈
    void push(int val) {
        sta.push(val);
        if (minSta.empty() || val <= minSta.top()) {
            minSta.push(val);
        }    
    }
    
    //* 弹栈时，如果弹出的值等于辅助栈的栈顶，则辅助栈也弹出
    void pop() {
        int x = sta.top();
        sta.pop();
        if (!minSta.empty() && x == minSta.top()) {
            minSta.pop();
        }
    }
    
    int top() {
        return sta.top();
    }
    
    int getMin() {
        return minSta.top();
    }
};

//* 题解解法
//* 辅助栈完全同步
class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(), x));
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

