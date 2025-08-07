/*
 * @lc app=leetcode.cn id=142 lang=cpp
 * 链表
 ! [142] 环形链表 II
 */

/*
 * 官方题解思路，哈希：
 * 用哈希表记录走过的节点。
 * 有环的话，遍历过程中会遇见存过的节点，此时这个节点就是环的入口。
 * 否则遍历指针会遇见nullptr。
 * 
 * 我的思路：
 * 先用快慢指针确定是否有环
 * 在通过数学计算，算出相遇点和头指针同时开始遍历，碰上的地方就是环的入口
 * 假设从头结点到环形入口节点的节点数为x。 
 * 环形入口节点到fast指针与slow指针相遇节点,节点数为y。 
 * 从相遇节点再到环形入口节点,节点数为 z。
 * 通过fast指针走的步数是slow指针的两倍，可以得到以下方程：
 ! (x + y) * 2 = x + y + n * (y + z)
 * x = (n - 1) (y + z) + z
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

//* 思路一：快慢指针加数学
//* 时间复杂度O(N)，空间复杂度O(1)
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        //* 注意除了fast，还需要判断fast->next是否为空
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            //* 快慢指针相遇，此时从 head 和 相遇点，同时查找直至相遇
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
        //* 从这里退出说明链表无环
        return nullptr;
    }
};

//* 思路二：使用哈希表记录走过的节点
//* 时间复杂度O(N)，空间复杂度O(N)
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode *> visited;
        while (head != nullptr) {
            if (visited.count(head)) {
                return head;
            }
            visited.insert(head);
            head = head->next;
        }
        return nullptr;
    }
};
// @lc code=end

