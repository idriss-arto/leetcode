/*
 * @lc app=leetcode.cn id=234 lang=cpp
 * 链表
 * [234] 回文链表
 */

/*
 * 官方题解一：
 * 复制链表值到数组列表中，然后使用双指针法判断是否为回文。
 * 
 * 别人的解法，用栈。
 * 
 * 以上两种方法空间复杂度均为O(N)。
 * 
 * 官方题解二：
 * 快慢指针找到链表中点，然后反转后半部分链表。
 * 最后比较前半部分和后半部分是否相同。
 * 最后，不管是否回文，都需要将链表还原。
 * 
 * 
 * 先把所有元素压入栈中，然后弹出栈就是“从后往前”读，此时再遍历一遍“从前往后”读，两者一致就是true。
*/

// @lc code=start
#include <vector>
#include <stack>
using namespace std;

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
 * 题解解法：
 * 复制链表值到数组列表中，然后使用双指针法判断是否为回文。
*/
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> vals;
        while (head != nullptr) {
            vals.emplace_back(head->val);
            head = head->next;
        }
        for (int i = 0, j = (int)vals.size() - 1; i < j; ++i, --j) {
            if (vals[i] != vals[j]) {
                return false;
            }
        }
        return true;
    }
};

/*
 * 别人的解法，用栈。
 * 先把所有元素压入栈中，然后弹出栈就是“从后往前”读，此时再遍历一遍“从前往后”读，两者一致就是true。
*/
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<int> stack;

        ListNode* p = head;
        while (p != nullptr) {
            stack.push(p->val);
            p = p->next;
        }

        p = head;
        while (p != nullptr) {
            if (p->val != stack.top())
                return false;
            stack.pop();
            p = p->next;
        }

        return true;
    }
};

/*
 * 题解解法二：
 * 快慢指针找到链表中点，然后反转后半部分链表。
 * 最后比较前半部分和后半部分是否相同。
 * 
 * 注意：需要先反转后半部分链表，然后再比较。
 * 反转后半部分链表时，需要记录下反转前的头结点，最后再将其恢复。
*/
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) {
            return true;
        }

        //* 找到前半部分链表的尾节点并反转后半部分链表
        ListNode* firstHalfEnd = endOfFirstHalf(head);
        ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

        //* 判断是否回文
        ListNode* p1 = head;
        ListNode* p2 = secondHalfStart;
        bool result = true;
        while (result && p2 != nullptr) {
            if (p1->val != p2->val) {
                result = false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }        

        //* 还原链表并返回结果
        firstHalfEnd->next = reverseList(secondHalfStart);
        return result;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }

    ListNode* endOfFirstHalf(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};

/*
 ! 错误
 * 我的解法：
 * 用栈储存链表节点的值，每来一个新节点都与栈顶的值作比较
 * 不同的话压入栈，相同的话弹出栈顶。 
 ! 问题：链表总节点数为奇数时错误
*/
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head->next == nullptr) return true;

        ListNode* cur = head;
        stack<int> sta;

        while (cur) {
            if (sta.empty() || sta.top() != cur->val) {
                sta.push(cur->val);
            }
            else {
                sta.pop();
            }
            cur = cur->next;
        }
        
        if (sta.empty()) return true;
        else return false;
    }
};
// @lc code=end

