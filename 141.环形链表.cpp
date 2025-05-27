/*
 * @lc app=leetcode.cn id=141 lang=cpp
 * 链表
 * [141] 环形链表
 */

// @lc code=start
#include <unordered_set>
using namespace std;

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
 
//* 思路一：使用哈希表记录走过的节点
//* 时间复杂度O（n），空间复杂度O（n）
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> set;
        
        while (head) {
            if (set.count(head)) return true;
            else {
                set.insert(head);
                head = head->next;
            }
        }

        return false;
    }
};

//* 思路二：快慢指针
//* 时间复杂度O（n），空间复杂度O（1）
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head || !head->next) return false;
        ListNode* slow = head->next;
        ListNode* fast = head->next->next;
        
        while (fast && slow) {
            if (fast == slow) return true;
            else {
                //* 注意此处判断
                if (!fast->next) return false;
                slow = slow->next;
                fast = fast->next->next;
            }
        }

        return false;
    }
};
// @lc code=end

