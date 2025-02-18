// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    public:
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            int lenA = 0, lenB = 0;
            ListNode* curA = headA;
            ListNode* curB = headB;

            // 算出长度差
            while (curA) {
                lenA++;
                curA = curA->next;
            }
            while (curB) {
                curB++;
                curB = curB->next;
            }

            curA = headA;
            curB = headB;
            if (lenA >= lenB) {
                int diff = lenA - lenB;
                while (diff--) {
                    curA = curA->next;
                }
            }
            else {
                int diff = lenB - lenA;
                while (diff--) {
                    curB = curB->next;
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