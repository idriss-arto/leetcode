/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] 反转链表
 */

// @lc code=start

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        while (head != nullptr) {
            ListNode* next = head->next;
            head->next = dummyHead->next;
            dummyHead->next = head;
            head = next;
        }
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }

    /*
    双指针法
    ListNode* reverseList(ListNode* head) {
        ListNode* temp;         // 保存cur的下一个节点
        ListNode* cur = head;
        ListNode* pre = NULL;
        while(cur) {
            temp = cur->next;   // 保存一下 cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre;    // 翻转操作
            // 更新pre 和 cur指针
            pre = cur;
            cur = temp;
        }
        return pre;
    }
    */
};
// @lc code=end

