/*
 * @lc app=leetcode.cn id=2 lang=cpp
 * 链表
 ! [2] 两数相加
 */

/*
 * 不难，注意下连续进位的情况和最后首位进一的情况
*/

#include <algorithm>
using namespace std;

// @lc code=start
//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//* 题解解法，模拟
//* 每一位都新建了一个节点，代码简单
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode();
        ListNode* curr = dummy;
        int carry = 0;
        while(l1 || l2 || carry) {
            int a = l1 ? l1->val : 0;
            int b = l2 ? l2->val : 0;
            int sum = a + b + carry;
            carry = sum >= 10 ? 1 : 0;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }

        ListNode* result = dummy->next;
        delete dummy;   //* 释放虚拟头结点
        return result;
    }
};

//* 灵茶的解法，原地修改
class Solution {
public:
    //* l1 和 l2 为当前遍历的节点，carry 为进位
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry = 0) {
        if (l1 == nullptr && l2 == nullptr) {   //* 递归边界
            return carry ? new ListNode(carry) : nullptr;   //* 如果进位了，就额外创建一个节点
        }
        if (l1 == nullptr) {    //* 如果 l1 是空的，那么此时 l2 一定不是空节点
            swap(l1, l2);       //* 交换 l1 与 l2，保证 l1 非空，从而简化代码
        }
        int sum = carry + l1->val + (l2 ? l2->val : 0);     //* 节点值和进位加在一起
        l1->val = sum % 10;     //* 每个节点保存一个数位（直接修改原链表）
        l1->next = addTwoNumbers(l1->next, (l2 ? l2->next : nullptr), sum / 10); //* 处理下一位
        return l1;
    }
};

//* 原地修改，迭代写法
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode();
        dummy->next = l1;
        ListNode* prev = dummy;
        int carry = 0;
        while(l1 || l2 || carry) {
            if (!l1 && !l2) {
                prev->next = new ListNode(carry);
                break;
            }

            if (!l1) swap(l1, l2);

            int sum = l1->val + carry + (l2 ? l2->val : 0);
            carry = sum >= 10 ? 1 : 0;
            
            l1->val = sum % 10;
            prev->next = l1;
            prev = l1;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }

        ListNode* result = dummy->next;
        delete dummy;   //* 释放虚拟头结点
        return result;
    }
};
// @lc code=end

