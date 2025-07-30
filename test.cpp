// @lc code=start
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdio.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* rotate(ListNode* preTail, int k) {
        if (!preTail->next) return nullptr;

        ListNode* dummyHead = preTail;
        ListNode* tail = dummyHead->next;

        while (--k && tail->next) {
            ListNode* cur = tail->next;
            tail->next = cur->next;
            cur->next = dummyHead->next;
            dummyHead->next = cur;
        }

        ListNode* cur = preTail->next;
        while (cur) {
            printf("%d ", cur->val);
            cur = cur->next;
        }
        printf("\n");
        printf("k = %d, tail = %d", k, tail->val);
        printf("\n");

        if (k != 0) return nullptr;
        else return tail;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* cur = dummyHead;
        while (cur) {
            ListNode* node = rotate(cur, k);
            if (!node) {
                rotate(cur, k);
            }
            cur = node;
        }

        ListNode* result = dummyHead->next;
        delete dummyHead;

        cur = result;
        while (cur) {
            printf("%d ", cur->val);
            cur = cur->next;
        }

        return result;
    }
};

int main() {
    Solution a;
    ListNode* node5 = new ListNode(5);
    ListNode* node4 = new ListNode(4, node5);
    ListNode* node3 = new ListNode(3, node4);
    ListNode* node2 = new ListNode(2, node3);
    ListNode* node1 = new ListNode(1, node2);

    a.reverseKGroup(node1, 2);

    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;

    return 0;
}
// @lc code=end

