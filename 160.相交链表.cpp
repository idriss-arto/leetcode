/*
 * @lc app=leetcode.cn id=160 lang=cpp
 * 链表
 * [160] 相交链表
 */

/*
 * 我的思路：快慢指针
 * 计算两个链表的长度，计算出差值diff，然后让长的链表先从表头向后走diff步。
 * 然后让两个链表的指针同时往后走。
 * 这样，如果两个链表相交的话，一定能同时到达相交点。
 * 不相交的话，同时到达null，退出循环。
 * 
 * 题解思路一：哈希
 * 先从头遍历一遍链表A，同时将节点记入哈希表。
 * 再从头遍历一遍链表B，看链表B中的节点能否在哈希表中找到。
 * 
 * 题解思路二：双指针
 * 当链表 headA 和 headB 都不为空时，创建两个指针 pA 和 pB，
 * 初始时分别指向两个链表的头节点 headA 和 headB，
 * 然后将两个指针依次遍历两个链表的每个节点。具体做法如下：
 * 每步操作需要同时更新指针 pA 和 pB。
 * 如果指针 pA 不为空，则将指针 pA 移到下一个节点；如果指针 pB 不为空，则将指针 pB 移到下一个节点。
 * 如果指针 pA 为空，则将指针 pA 移到链表 headB 的头节点；如果指针 pB 为空，则将指针 pB 移到链表 headA 的头节点。
 * 当指针 pA 和 pB 指向同一个节点或者都为空时，返回它们指向的节点或者 null。
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

/*
 * 题解思路一，哈希
 * 先从头遍历一遍链表A，同时将节点记入哈希表。
 * 再从头遍历一遍链表B，看链表B中的节点能否在哈希表中找到。
*/
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *> visited;
        ListNode *temp = headA;
        while (temp != nullptr) {
            visited.insert(temp);
            temp = temp->next;
        }
        temp = headB;
        while (temp != nullptr) {
            if (visited.count(temp)) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

/*
 * 题解思路二，双指针
 *
 * 
 * 代码写法如下：
 * 当链表 headA 和 headB 都不为空时，创建两个指针 pA 和 pB，
 * 初始时分别指向两个链表的头节点 headA 和 headB，
 * 然后将两个指针依次遍历两个链表的每个节点。具体做法如下：
 * 每步操作需要同时更新指针 pA 和 pB。
 * 如果指针 pA 不为空，则将指针 pA 移到下一个节点；如果指针 pB 不为空，则将指针 pB 移到下一个节点。
 * 如果指针 pA 为空，则将指针 pA 移到链表 headB 的头节点；如果指针 pB 为空，则将指针 pB 移到链表 headA 的头节点。
 * 当指针 pA 和 pB 指向同一个节点或者都为空时，返回它们指向的节点或者 null。
 * 
 * 
 * 证明如下：
 * 情况一：两个链表相交
 * 链表 headA 和 headB 的长度分别是 m 和 n。
 * 假设链表 headA 的不相交部分有 a 个节点，链表 headB 的不相交部分有 b 个节点，
 * 两个链表相交的部分有 c 个节点，则有 a+c=m，b+c=n。
 * 1.
 * 如果 a=b，则两个指针会同时到达两个链表相交的节点，此时返回相交的节点；
 * 2.
 * 如果 a!=b，则指针 pA 会遍历完链表 headA，指针 pB 会遍历完链表 headB，两个指针不会同时到达链表的尾节点，
 * 然后指针 pA 移到链表 headB 的头节点，指针 pB 移到链表 headA 的头节点，然后两个指针继续移动，
 * 在指针 pA 移动了 a+c+b 次、指针 pB 移动了 b+c+a 次之后，两个指针会同时到达两个链表相交的节点，
 * 该节点也是两个指针第一次同时指向的节点，此时返回相交的节点。
 * 
 * 情况二：两个链表不相交
 * 链表 headA 和 headB 的长度分别是 m 和 n。考虑当 m=n 和 m!=n 时，两个指针分别会如何移动：
 * 1.
 * 如果 m=n，则两个指针会同时到达两个链表的尾节点，然后同时变成空值 null，此时返回 null；
 * 2.
 * 如果 m!=n，则由于两个链表没有公共节点，两个指针也不会同时到达两个链表的尾节点，
 * 因此两个指针都会遍历完两个链表，在指针 pA 移动了 m+n 次、指针 pB 移动了 n+m 次之后，
 * 两个指针会同时变成空值 null，此时返回 null。
*/
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode *pA = headA, *pB = headB;
        while (pA != pB) {
            pA = pA == nullptr ? headB : pA->next;
            pB = pB == nullptr ? headA : pB->next;
        }
        return pA;
    }
};

/*
 * 我的解法，思路
 * 计算两个链表的长度，计算出差值diff，然后让长的链表先从表头向后走diff步。
 * 然后让两个链表的指针同时往后走。
 * 这样，如果两个链表相交的话，一定能同时到达相交点。
 * 不相交的话，同时到达null，退出循环。
*/
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA;
        int lenA = 0;
        while (curA) {
            lenA++;
            curA = curA->next;
        }

        ListNode* curB = headB;
        int lenB = 0;
        while (curB) {
            lenB++;
            curB = curB->next;
        } 

        curA = headA;
        curB = headB;
        if (lenA < lenB) { 
            int diff = lenB - lenA;
            while (diff--) {
                curB = curB->next;
            }
        }
        else {
            int diff = lenA - lenB;
            while (diff--) {
                curA = curA->next;
            }
        }

        while (curA && curB) {
            if (curA == curB) {
                return curA;
            }
            else {
                curA = curA->next;
                curB = curB->next;
            }
        }

        return nullptr;
    }
};
// @lc code=end

