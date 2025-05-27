/*
 * @lc app=leetcode.cn id=21 lang=cpp
 * 链表
 * [21] 合并两个有序链表
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

//* 迭代法
//* 时间复杂度O（m+n），空间复杂度O（1）
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummyHead = new ListNode();
        ListNode* prev = dummyHead;
        
        while (list1 && list2) {
            if (list1->val > list2->val) {
                prev->next = list2;
                list2 = list2->next;
            }
            else {
                prev->next = list1;
                list1 = list1->next;
            }
        }

        //* list1还没遍历完，list2遍历完了
        if (list1) {
            prev->next = list1;
        }
        //* list2还没遍历完，list1遍历完了
        else {
            prev->next = list2;
        }

        return dummyHead->next;
    }
};

//* 递归法
//* 时间复杂度O（m+n），空间复杂度O（m+n）
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        } else if (l2 == nullptr) {
            return l1;
        } else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
// @lc code=end

