/*
 * @lc app=leetcode.cn id=206 lang=cpp
 * 链表
 * [206] 反转链表
 */

/*
 * 思路
 * 一：构建一个带虚拟头结点的新链表，将原来的链表元素依次头插入新链表中
 * 二：双指针，调换相邻两节点的指向关系
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

//* 构建一个带虚拟头结点的新链表，将原来的链表元素依次头插入新链表中
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* next;
        while (head != nullptr) {
            //* 记录下一个要插入的节点
            next = head->next;
            //* 将当前节点头插在新链表中
            head->next = dummyHead->next;
            dummyHead->next = head;
            //* 准备好下一个要插入的节点
            head = next;
        }
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};

//* 双指针，调换相邻两节点的指向关系
//* 注意需要让原始头结点的next指向nullptr
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* temp;         //* 保存cur的下一个节点
        ListNode* cur = head;
        //* 注意pre是从null开始，因为要使原来的头结点的next指向null
        ListNode* pre = nullptr;
        while(cur) {
            temp = cur->next;   //* 保存一下 cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre;    //* 翻转操作
            //* 更新pre 和 cur指针
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};
// @lc code=end

