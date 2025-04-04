/*
 * @lc app=leetcode.cn id=225 lang=cpp
 * 栈和队列
 * [225] 用队列实现栈
 */

/*
 * 思路：
 * 可以只用一个队列模拟
 * stack.push的时候正常push进队列尾部
 * stack.pop时，记录当前队列中元素个数，然后从队列头拿一个数据，再从队列尾插入回去，直到循环一遍，就能拿到最后stack.push的数据
 * 
 * 两个队列模拟是一样的思路
 * 只不过始终保持一个队列为空
 * stack.push的时候正常push进不为空的队列尾部
 * stack.pop时，从不为空队列头拿一个数据，再从为空队列尾插入回去，直到不为空队列只剩一个元素，就能拿到最后stack.push的数据
*/

// @lc code=start
#include<queue>
using namespace std;
class MyStack {
public:
    queue<int> que;

    MyStack() {

    }

    void push(int x) {
        que.push(x);
    }

    int pop() {
        int size = que.size();
        size--;
        while (size--) {            //* 将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部
            que.push(que.front());
            que.pop();
        }
        int result = que.front();   //* 此时弹出的元素顺序就是栈的顺序了
        que.pop();
        return result;
    }

    int top(){
        int res = this->pop();      //* 直接使用已有的pop函数
        que.push(res);              //* 因为pop函数弹出了元素res，所以再添加回去
        return res;
    }

    bool empty() {
        return que.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// @lc code=end

