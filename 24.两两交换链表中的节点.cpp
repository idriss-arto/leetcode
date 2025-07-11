/*
 * @lc app=leetcode.cn id=24 lang=cpp
 * 链表
 * [24] 两两交换链表中的节点
 */

/*
 * 迭代思路：
 * 必须使用虚拟头结点才好做
 * 需要预先用临时指针存储所有需要处理的节点，否则next变化后就乱了
 * 最后记得内存回收虚拟头结点
 * 
 * 递归思路：
 * 用 head 表示原始链表的头节点，新的链表的第二个节点，
 * 用 newHead 表示新的链表的头节点，原始链表的第二个节点，
 * 则原始链表中的其余节点的头节点是 newHead.next。
 * 令 head.next = swapPairs(newHead.next)，表示将其余节点进行两两交换，
 * 交换后的新的头节点为 head 的下一个节点。
 * 然后令 newHead.next = head，即完成了所有节点的交换。最后返回新的链表的头节点 newHead。
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

//* 官方解法一，迭代
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);      //* 设置一个虚拟头结点
        dummyHead->next = head;                     //* 将虚拟头结点指向head，这样方便后面做交换操作

        ListNode* cur = dummyHead;                  //! cur指向的是要交换的两个节点之前的一个节点
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp1 = cur->next;             //* 记录临时节点
            ListNode* tmp2 = cur->next->next;       //* 记录临时节点
            ListNode* tmp3 = cur->next->next->next; //* 记录临时节点

            cur->next = tmp2;                       //* 步骤一
            tmp2->next = tmp1;                      //* 步骤二
            tmp1->next = tmp3;                      //* 步骤三

            cur = cur->next->next;                  //* cur移动两位，准备下一轮交换
        }

        ListNode* result = dummyHead->next;
        delete dummyHead;

        return result;
    }
};

//* 官方解法二：递归
class Solution {
public:
    //* 传入的head是两两相交的第一个节点 
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* newHead = head->next;
        head->next = swapPairs(newHead->next);
        newHead->next = head;
        return newHead;
    }
};
// @lc code=end

