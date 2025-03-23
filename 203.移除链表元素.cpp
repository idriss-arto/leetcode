/*
 * @lc app=leetcode.cn id=203 lang=cpp
 * 链表基础
 * [203] 移除链表元素
 */

/*
 * 思路：还是用一个虚拟头结点比较方便，不然删除头结点的情况需要单独处理
 * 注意：养成习惯，自定义类型删除后清理内存空间
*/

// @lc code=start

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        //* 删除值为val的头结点
        while (head != nullptr && head->val == val) {
            ListNode* p = head;
            head = head->next;
            delete p; 
        }

        //* 删除非头结点
        ListNode* cur = head;
        while (cur != nullptr && cur->next != nullptr) {
            if (cur->next->val == val) {
                ListNode* p = cur->next;
                cur->next = cur->next->next;
                delete p;
            }
            else {
                cur = cur->next;
            }
        }
        return head;
    }
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode();
        dummyHead->next = head;

        ListNode* cur = dummyHead;
        while (cur != nullptr && cur->next != nullptr) {
            if (cur->next->val == val) {
                ListNode* p = cur->next;
                cur->next = cur->next->next;
                delete p;
            }
            else {
                cur = cur->next;
            }
        }
        return dummyHead->next;
    }
};
// @lc code=end

