/*
 * @lc app=leetcode.cn id=148 lang=cpp
 * 链表
 ! [148] 排序链表
 */

// @lc code=start
#include <vector>
#include <algorithm>
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
 * 官方题解，归并排序（自顶向下）
 * 时间复杂度：O(nlogn)，其中 n 是链表的长度。
 * 空间复杂度：O(logn)，其中 n 是链表的长度。空间复杂度主要取决于递归调用的栈空间。
*/
class Solution {
public:
    //* 876. 链表的中间结点（快慢指针）
    ListNode* middleNode(ListNode* head) {
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* slow = dummyHead;
        ListNode* fast = dummyHead;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* head2 = slow->next;
        slow->next = nullptr;    //* 断开 slow 和后面节点的连接
        return head2;
    }

    //* 21. 合并两个有序链表（双指针）
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;             //* 用哨兵节点简化代码逻辑
        ListNode* cur = &dummy;     //* cur 指向新链表的末尾
        while (list1 && list2) {
            if (list1->val < list2->val) {
                cur->next = list1;  //* 把 list1 加到新链表中
                list1 = list1->next;
            }
            //* 注：相等的情况加哪个节点都是可以的
            else {
                cur->next = list2;  //* 把 list2 加到新链表中
                list2 = list2->next;
            }
            cur = cur->next;
        }
        cur->next = list1 ? list1 : list2;  //* 拼接剩余链表
        return dummy.next;
    }

    ListNode* sortList(ListNode* head) {
        //* 如果链表为空或者只有一个节点，无需排序
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        //* 找到中间节点 head2，并断开 head2 与其前一个节点的连接
        //* 比如 head=[4,2,1,3]，那么 middleNode 调用结束后 head=[4,2] head2=[1,3]
        ListNode* head2 = middleNode(head);
        //* 分治
        head = sortList(head);
        head2 = sortList(head2);
        //* 合并
        return mergeTwoLists(head, head2);
    }
};

/*
 * 官方题解，归并排序（自底向上）
 * 时间复杂度：O(nlogn)，其中 n 是链表的长度。
 * 空间复杂度：O(1)。
*/
class Solution {
    //* 获取链表长度
    int getListLength(ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }

    //* 分割链表
    //* 如果链表长度 <= size，不做任何操作，返回空节点
    //* 如果链表长度 > size，把链表的前 size 个节点分割出来（断开连接），并返回剩余链表的头节点
    ListNode* splitList(ListNode* head, int size) {
        //* 先找到 next_head 的前一个节点
        ListNode* cur = head;
        for (int i = 0; i < size - 1 && cur; i++) {
            cur = cur->next;
        }

        //* 如果链表长度 <= size
        if (cur == nullptr || cur->next == nullptr) {
            return nullptr; //* 不做任何操作，返回空节点
        }

        ListNode* next_head = cur->next;
        cur->next = nullptr; //* 断开 next_head 的前一个节点和 next_head 的连接
        return next_head;
    }

    //* 21. 合并两个有序链表（双指针）
    //* 返回合并后的链表的头节点和尾节点
    pair<ListNode*, ListNode*> mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;             //* 用哨兵节点简化代码逻辑
        ListNode* cur = &dummy;     //* cur 指向新链表的末尾
        while (list1 && list2) {
            if (list1->val < list2->val) {
                cur->next = list1;  //* 把 list1 加到新链表中
                list1 = list1->next;
            }
            //* 注：相等的情况加哪个节点都是可以的
            else { 
                cur->next = list2;  //* 把 list2 加到新链表中
                list2 = list2->next;
            }
            cur = cur->next;
        }
        cur->next = list1 ? list1 : list2;  //* 拼接剩余链表
        while (cur->next) {
            cur = cur->next;
        }
        //* 循环结束后，cur 是合并后的链表的尾节点
        return {dummy.next, cur};
    }

public:
    ListNode* sortList(ListNode* head) {
        int length = getListLength(head);   //* 获取链表长度
        ListNode dummy(0, head);            //* 用哨兵节点简化代码逻辑
        //* step 为步长，即参与合并的链表长度
        for (int step = 1; step < length; step *= 2) {
            ListNode* new_list_tail = &dummy;   //* 新链表的末尾
            ListNode* cur = dummy.next;         //* 每轮循环的起始节点
            while (cur) {
                //* 从 cur 开始，分割出两段长为 step 的链表，头节点分别为 head1 和 head2
                ListNode* head1 = cur;
                ListNode* head2 = splitList(head1, step);
                cur = splitList(head2, step);   //* 下一轮循环的起始节点

                //* 合并两段长为 step 的链表
                ListNode* head;
                ListNode* tail;
                pair<ListNode*, ListNode*>(head, tail) = mergeTwoLists(head1, head2);
                //* 合并后的头节点 head，插到 new_list_tail 的后面
                new_list_tail->next = head;
                new_list_tail = tail;   //* tail 现在是新链表的末尾
            }
        }
        return dummy.next;
    }
};

//* 思路一，将链表转换为数组，排序后再转换回链表
//* 时间复杂度O（N*log(N)），空间复杂度O（N）
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head) return nullptr;

        vector<int> nums;

        while (head) {
            nums.push_back(head->val);
            head = head->next;
        }

        sort(nums.begin(), nums.end());

        ListNode* cur;
        ListNode* next;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (i == nums.size() - 1) {
                cur = new ListNode(nums[i]);
            }
            else {
                cur = new ListNode(nums[i], next);
            }
            next = cur;
        }

        return cur;
    }
};

/*
 * 很慢，险些超时
 * 思路二：
 * 用虚拟头结点指向当前链表，
 * 遍历节点，如果节点递增，继续遍历。
 * 如果出现节点比前一个节点小，则将该节点从虚拟头结点下一个位置开始找到合适位置。
 * 时间复杂度O（N^2），空间复杂度O（1）
*/
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head) return nullptr;

        ListNode* dummyHead = new ListNode(0, head);
        while (head->next) {
            if (head->val <= head->next->val) head = head->next;
            else {
                ListNode* cur = head->next;
                head->next = cur->next;

                ListNode* newpos = dummyHead;
                while (newpos->next && newpos->next->val < cur->val) {
                    newpos = newpos->next;
                }
                ListNode* tmp = newpos->next;
                newpos->next = cur;
                cur->next = tmp;
            }
        }

        return dummyHead->next;
    }
};

//! 错误，最后一个用例超时
//* 思路二：
//* 遍历节点，将节点插入以虚拟头结点为头结点的新链表中的正确位置
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head) return nullptr;

        ListNode* dummyHead = new ListNode(0);
        while (head) {
            ListNode* next = head->next;

            ListNode* newpos = dummyHead;
            while (newpos->next && newpos->next->val < head->val) {
                newpos = newpos->next;
            }
            ListNode* tmp = newpos->next;
            newpos->next = head;
            head->next = tmp;

            head = next;
        }

        return dummyHead->next;
    }
};
// @lc code=end

