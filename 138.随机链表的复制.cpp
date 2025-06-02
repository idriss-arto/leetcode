/*
 * @lc app=leetcode.cn id=138 lang=cpp
 * 链表，哈希
 ! [138] 随机链表的复制
 */

/*
 * 官方题解一：哈希
 * 用哈希表记录每一个节点对应新节点。
 * 第一次遍历，将原节点和对应的复制节点插入哈希表。
 * 第二次遍历，设置复制节点的next和random。
 * 
 * 官方题解二：迭代+节点拆分
 * 将给定链表中每一个节点拆分为两个相连的节点，
 * 例如对于链表 A→B→C，
 * 我们可以将其拆分为 A→A′→B→B′→C→C′。
 * 此时对于任意一个原节点 S，其拷贝节点 S′ 即为其后继节点。
 * 这样，我们可以直接找到每一个拷贝节点 S′ 的随机指针应当指向的节点，
 * 即为其原节点 S 的随机指针指向的节点 T 的后继节点 T′。
 * 注意特殊情况：随机指针指向null
*/

// @lc code=start
#include <unordered_map>
using namespace std;

//* Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

/*
 * 官方题解一：哈希
 * 用哈希表记录每一个节点对应新节点。
 * 第一次遍历，将原节点和对应的复制节点插入哈希表。
 * 第二次遍历，设置复制节点的next和random。
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node *, Node *> mp;

        //* 第一次遍历，将原节点和对应的复制节点插入哈希表
        Node *p = head;
        while (p) {
            Node *temp = new Node(p->val);
            //* 注意这里insert的是{p, temp}
            mp.insert({p, temp});
            p = p->next;
        }

        //* 第二次遍历，设置复制节点的next和random
        p = head;
        while (p) {
            mp[p]->next = mp[p->next];
            mp[p]->random = mp[p->random];
            p = p->next;
        }
        return mp[head];
    }
};

/*
 * 官方题解二：迭代+节点拆分
 * 将给定链表中每一个节点拆分为两个相连的节点，
 * 例如对于链表 A→B→C，
 * 我们可以将其拆分为 A→A′→B→B′→C→C′。
 * 此时对于任意一个原节点 S，其拷贝节点 S′ 即为其后继节点。
 * 这样，我们可以直接找到每一个拷贝节点 S′ 的随机指针应当指向的节点，
 * 即为其原节点 S 的随机指针指向的节点 T 的后继节点 T′。
 * 注意特殊情况：随机指针指向null
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        //! 注意三次遍历中node节点分别是怎么移动的
        //* 第一次遍历，向原链表中插入拷贝节点
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = new Node(node->val);
            nodeNew->next = node->next;
            node->next = nodeNew;
        }
        //* 第二次遍历，处理拷贝节点的随机指针
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = node->next;
            nodeNew->random = (node->random != nullptr) ? node->random->next : nullptr;
        }
        //* 第三次遍历，将拷贝节点从原链表中拆出，同时处理拷贝节点的next指针
        Node* headNew = head->next;
        for (Node* node = head; node != nullptr; node = node->next) {
            Node* nodeNew = node->next;
            node->next = node->next->next;
            nodeNew->next = (nodeNew->next != nullptr) ? nodeNew->next->next : nullptr;
        }
        return headNew;
    }
};
// @lc code=end

