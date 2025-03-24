/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
 */

/*
 * 思路：
 * 先用快慢指针确定是否有环
 * 在通过数学计算，算出相遇点和头指针同时开始遍历，碰上的地方就是环的入口
 * 假设从头结点到环形入口节点的节点数为x。 
 * 环形入口节点到fast指针与slow指针相遇节点,节点数为y。 
 * 从相遇节点再到环形入口节点,节点数为 z。
 * (x + y) * 2 = x + y + n * (y + z)
 * x = (n - 1) (y + z) + z
*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            ListNode* fast = head;
            ListNode* slow = head;
            while(fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;
                //* 快慢指针相遇，此时从head 和 相遇点，同时查找直至相遇
                if (slow == fast) {
                    ListNode* index1 = fast;
                    ListNode* index2 = head;
                    while (index1 != index2) {
                        index1 = index1->next;
                        index2 = index2->next;
                    }
                    return index2; //* 返回环的入口
                }
            }
            return nullptr;
        }
};
// @lc code=end

