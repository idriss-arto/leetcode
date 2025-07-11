/*
 * @lc app=leetcode.cn id=23 lang=cpp
 * 链表，优先队列，归并排序
 ! [23] 合并 K 个升序链表
 */

// @lc code=start
#include <vector>
#include <queue>
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
 * 官方解法二，优先队列：
 * 和我的解法大致思路相同，但使用优先队列优化了时间复杂度。
 * 每次比较完k个链表的表头后，其实k-1个链表的表头是不会变的，
 * 如果又从头比较k个链表，浪费了时间，所以用优先队列优化了这个过程。
 * 
 * 时间复杂度：
 * 考虑优先队列中的元素不超过 k 个，那么插入和删除的时间代价为 O(logk)，
 * 这里最多有 kn 个点，对于每个点都被插入删除各一次，故总的时间代价即渐进时间复杂度为 O(kn×logk)。
 * 
 * 空间复杂度：
 * 这里用了优先队列，优先队列中的元素不超过 k 个，故渐进空间复杂度为 O(k)。
*/
class Solution {
public:
    struct comp {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    priority_queue<ListNode*, vector<ListNode*>, comp> q;

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        for (auto node: lists) {
            if (node) q.push(node);
        }
        ListNode* dummyHead = new ListNode();
        ListNode* tail = dummyHead;
        while (!q.empty()) {
            ListNode* node = q.top();
            q.pop();
            tail->next = node; 
            tail = tail->next;
            if (node->next) q.push(node->next);
        }
        return dummyHead->next;
    }
};

/*
 * 官方题解解法一，分支合并：
 * 将k个链表两两分组进行合并，合并完得到k/2个链表，
 * 同理，k/2个链表两两分组进行合并得到k/4个链表,
 * 依次类推，最终得到目标链表。
 * 
 * 时间复杂度：
 * 考虑递归「向上回升」的过程——第一轮合并k/2组链表，每一组的时间代价是 O(2n)；
 * 第二轮合并k/4组链表，每一组的时间代价是 O(4n).....
 * 所以渐进时间复杂度为 O(kn×logk)。
 * 
 * 空间复杂度：
 * 递归会使用到 O(logk) 空间代价的栈空间。
*/
class Solution {
public:
    ListNode* mergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            } else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* merge(vector <ListNode*> &lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return nullptr;
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};

/*
 * 我的解法：
 * 仿照合并两个链表，每次考虑k个链表的表头，
 * 将最小值插入新链表。
 * 时间复杂度： O(n * k^2)。空间复杂度：O(1)
*/
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;
        
        while (1) {
            int flag = 0;
            int index = -1;
            int minNum = 10005;

            for (int i = 0; i < lists.size(); i++) {
                if (lists[i] == nullptr) {
                    continue;
                }
                else {
                    flag = 1;
                    if (lists[i]->val < minNum) {
                        index = i;
                        minNum = lists[i]->val;
                    }
                }
            }

            if (flag == 0) break;

            cur->next = lists[index];
            cur = cur->next;
            lists[index] = lists[index]->next;
        }

        return dummy->next;
    }
};
// @lc code=end

