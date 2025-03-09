/*
 * @lc app=leetcode.cn id=24 lang=cpp
 * 链表
 * [24] 两两交换链表中的节点
 */

// @lc code=start
//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);      //* 设置一个虚拟头结点
        dummyHead->next = head;                     //* 将虚拟头结点指向head，这样方便后面做删除操作
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp1 = cur->next;             //* 记录临时节点
            ListNode* tmp2 = cur->next->next->next; //* 记录临时节点
            ListNode* tmp3 = cur->next->next->next; //* 记录临时节点

            cur->next = tmp2;                       //* 步骤一
            cur->next->next = tmp1;                 //* 步骤二
            cur->next->next->next = tmp3;           //* 步骤三

            cur = cur->next->next;                  //* cur移动两位，准备下一轮交换
        }
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};
// @lc code=end

