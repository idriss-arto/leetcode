/*
 * @lc app=leetcode.cn id=19 lang=cpp
 * 快慢指针
 * [19] 删除链表的倒数第 N 个结点
 */

/*
 * 思路：
 * 快慢指针解题，快慢指针一开始都指向头结点
 * 然后让快指针比慢指针先走n步，
 * 这样快指针指向链表之后的nullptr时，慢指针指向要删除的节点
 * 因为是要删除节点，所以让快指针再多走一步，
 * 即快指针指向链表之后的nullptr时，慢指针指向要删除的节点前一个节点，
 * 但n为链表长度时，头结点没有前一个节点，所以需要用虚拟头结点，fast和slow一开始都指向虚拟头结点
 * （或者fast指向最后一个节点时跳出循环，但此时也需要注意特殊情况，即n为链表长度）
 * 链表删除节点需注意释放内存
*/

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
    //* 使用虚拟头结点
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* slow = dummyHead;
        ListNode* fast = dummyHead;
        while(n-- && fast != nullptr) {
            fast = fast->next;
        }
        fast = fast->next;              //! fast再提前走一步，因为需要让fast指向空时，slow指向删除节点的上一个节点
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }   
        
        ListNode *tmp = slow->next;     //* C++释放内存的逻辑
        slow->next = tmp->next;
        delete tmp;
        
        return dummyHead->next;
    }

    ListNode* myRemoveNthFromEnd(ListNode* head, int n) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (n--) {
            fast = fast->next;
        }
        
        if (fast) {
            //* fast指向最后一个结点时跳出循环，此时slow也指向要删除位置的前一个节点
            while (fast && fast->next) {
                fast = fast->next;
                slow = slow->next;
            }
            ListNode* p = slow->next;
            slow->next = p->next;
            delete p;
            return head;
        }
        //* 特殊情况，如[1,2,3], n=3; [1], n=1
        else {
            ListNode* p = slow->next;
            delete slow;
            return p;
        }
    }
};
// @lc code=end

