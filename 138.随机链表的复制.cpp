/*
 * @lc app=leetcode.cn id=138 lang=cpp
 * 链表，回溯+哈希
 ! [138] 随机链表的复制
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
 * 官方题解一：回溯+哈希
 * 用哈希表记录每一个节点对应新节点的创建情况。
 * 递归遍历该链表的过程中，我们用哈希表检查「当前节点的后继节点」和「当前节点的随机指针指向的节点」的创建情况。
 * 如果这两个节点中的任何一个节点的新节点没有被创建，我们都立刻递归地进行创建。
 * 当我们拷贝完成，回溯到当前层时，我们即可完成当前节点的指针赋值。
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node *, Node *> mp;
        Node *p = head;
        while (p) {
            Node *temp = new Node(p->val);
            mp.insert({p, temp});
            p = p->next;
        }
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

