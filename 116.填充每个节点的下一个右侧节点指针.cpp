/*
 * @lc app=leetcode.cn id=116 lang=cpp
 * 树的层次遍历,BFS
 * [116] 填充每个节点的下一个右侧节点指针
 */

//* 层序遍历（BFS，广度优先遍历），使用队列

// @lc code=start
#include <queue>
using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) return root;
        queue<Node*> que;
        que.push(root);
        while (!que.empty()) {
            int size = que.size();
            Node* cur, * nextNode;
            for (int i = 0; i< size; i++) {
                cur = que.front();
                que.pop();
                if (i < (size - 1)) {
                    nextNode = que.front();
                    cur->next = nextNode;
                }
                if (cur->left) que.push(cur->left);
                if (cur->right) que.push(cur->right);
            }
        }
        return root;
    }
};
// @lc code=end

