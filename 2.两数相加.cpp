/*
 * @lc app=leetcode.cn id=2 lang=cpp
 * 链表
 * [2] 两数相加
 */

/*
 * 不难，注意下连续进位的情况和最后首位进一的情况
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

//* 我的解法，模拟
//* 直接在原来的list1上操作的，思路简单，代码稍显冗余
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carrybit = 0;
        ListNode* dummyHead = new ListNode();
        ListNode* prev = dummyHead;
        while (l1 && l2) {
            prev->next = l1;
            prev = l1;
            if (l1->val + l2->val + carrybit >= 10) {
                l1->val = (l1->val + l2->val + carrybit) % 10;
                carrybit = 1;
            }
            else {
                l1->val = l1->val + l2->val + carrybit;
                carrybit = 0;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        
        //* list1还没遍历完，list2遍历完了
        if (l1) {
            //* 这里加完进位可能搞好等于10，所以需要下一步处理
            l1->val += carrybit;
            while (l1->val >= 10) {
                l1->val %= 10;
                //* 可能最后首位进1
                if (!l1->next) l1->next = new ListNode(0);
                l1 = l1->next;
                l1->val += 1;
            }
        }
        //* list2还没遍历完，list1遍历完了
        else if (l2){
            prev->next = l2;
            //* 这里加完进位可能搞好等于10，所以需要下一步处理
            l2->val += carrybit;
            while (l2->val >= 10) {
                l2->val %= 10;
                //* 可能最后首位进1
                if (!l2->next) l2->next = new ListNode(0);
                l2 = l2->next;
                l2->val += 1;
            }
        }
        //! 剩余情况是两个链表同时到结尾，只用管进位不为0的情况
        else {
            if (carrybit != 0) prev->next = new ListNode(1);
        }

        ListNode* result = dummyHead->next;
        delete dummyHead;   //* 释放虚拟头结点
        return result;
    }
};
// @lc code=end

