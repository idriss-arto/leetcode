/*
 * @lc app=leetcode.cn id=25 lang=cpp
 * 链表
 ! [25] K 个一组翻转链表
 */

/*
 * 我的解法：
 * 记录要翻转的k个节点之前的最后一个节点，
 * 同时将要翻转的k个节点（不能为空）和下一次翻转的头结点（可以为空）记录进一个数组。
 * 通过数组下标实现节点翻转。
 * 时间复杂度O(N)，空间复杂度O(K)
 * 
 * 官方题解解法：
 * 大致思路相同，但翻转k个节点是用头插法依次插在prev后面以实现翻转
 * 时间复杂度O(N)，空间复杂度O(1)
*/

// @lc code=start
#include <vector>
using namespace std;

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
 * 我的解法：
 * 记录要翻转的k个节点之前的最后一个节点，
 * 同时将要翻转的k个节点（不能为空）和下一次翻转的头结点（可以为空）记录进一个数组。
 * 通过数组下标实现节点翻转。
 * 时间复杂度O(N)，空间复杂度O(K)
*/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummyHead = new ListNode(0);      //* 设置一个虚拟头结点
        dummyHead->next = head;                     //* 将虚拟头结点指向head，这样方便后面做翻转操作

        ListNode* cur = dummyHead;                  //! cur指向的是要翻转的k个节点之前的一个节点
        while(cur) {
            bool quit = false;
            ListNode* node = cur->next;
            vector<ListNode*> tmp(k+1);             //* 记录要翻转位置的k个节点，和下一次翻转的第一个节点。一共k+1个节点

            for (int i = 0; i < k; i++) {
                //* 要翻转的k个节点不能为空，为空的话说明前面的多次翻转后，现在剩下的节点不够k个
                if (node) {
                    tmp[i] = node;
                    node = node->next;
                }
                else {
                    quit = true;
                    break;
                }
            }
            //* 下一次翻转的第一个节点可能为空，因为链表节点个数可能刚好是k的整数倍
            tmp[k] = node;

            if (quit) break;

            cur->next = tmp[k-1];
            for (int i = k-1; i >= 1; i--) {
                tmp[i]->next = tmp[i-1];
            }
            tmp[0]->next = tmp[k];            

            cur = tmp[0];                  //* cur移动位置，准备下一轮翻转
        }

        ListNode* result = dummyHead->next;
        delete dummyHead;
        
        return result;
    }
};

/* 
 * 官方题解解法：
 * 大致思路相同，但翻转k个节点是用头插法依次插在prev后面以实现翻转
 * 时间复杂度O(N)，空间复杂度O(1)
*/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* pre = dummyHead;
        while (pre->next != nullptr) {
            ListNode* nextPre = rotate(pre, k);
            //* 最后一次翻转节点数不足k，需要调换回来
            if (nextPre == nullptr) {
                rotate(pre, k);
                break;
            } 
            else {
                pre = nextPre;
            }
        }
        return dummyHead->next;
    }

    //* 传入的第一个参数是要翻转的k个节点之前的最后一个节点，
    //* 第二个参数是要翻转的节点数k。
    ListNode* rotate(ListNode* pre, int k) {
        ListNode* tail = pre->next;         //* tail是本次翻转里已经翻转部分的尾节点
       
        int i = 1;
        //* tail为nullptr说明链表节点数刚好是k的倍数
        //* tail->next为nullptr说明此次翻转节点数不足k
        //* 最后一次循环，i=k-1，tail->next此时是此次翻转范围里的原最后一个节点
        for (; i < k && tail != nullptr && tail->next != nullptr; i++) {
            ListNode* cur = tail->next;     //* cur是要从未翻转部分挪到翻转部分的节点
            tail->next = cur->next;
            cur->next = pre->next;          //* cur插入pre和当前已翻转部分头结点之间，成为新的头结点
            pre->next = cur;
        }
        return i == k ? tail : nullptr;
    }
};
// @lc code=end

