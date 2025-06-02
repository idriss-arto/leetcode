/*
 * @lc app=leetcode.cn id=141 lang=cpp
 * 链表
 * [141] 环形链表
 */

/*
 * 我的思路，快慢指针：
 * 从虚拟头结点开始，快指针每次走两步，慢指针每次走一步，
 * 如果有环，二者必定相遇。否则快指针先遇见null。
 * 
 * 官方题解思路，哈希：
 * 用哈希表记录走过的节点。
 * 有环的话，遍历过程中会遇见存过的节点。
 * 否则遍历指针会遇见nullptr。
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

