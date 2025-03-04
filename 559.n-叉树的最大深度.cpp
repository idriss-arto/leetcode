/*
 * @lc app=leetcode.cn id=559 lang=cpp
 *
 * [559] N 叉树的最大深度
 */

// @lc code=start
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    // 迭代法
    int maxDepth(Node* root) {
        if (root == nullptr) return 0;
        queue<Node*> que;
        que.push(root);
        int depth = 0;
        while (!que.empty()) {
            depth++;
            int size = que.size();
            for (int i = 0; i < size; i++) {
                Node* cur = que.front();
                que.pop();
                for (Node* it : cur->children) {
                    que.push(it);
                }
            }
        }
        return depth;
    }

    // 递归法
    int maxDepth(Node* root) {
        if (root == 0) return 0;
        int depth = 0;
        for (int i = 0; i < root->children.size(); i++) {
            depth = max (depth, maxDepth(root->children[i]));
        }
        return depth + 1;
    }
};
// @lc code=end

