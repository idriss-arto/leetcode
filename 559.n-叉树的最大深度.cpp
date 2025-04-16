/*
 * @lc app=leetcode.cn id=559 lang=cpp
 * 树的层次遍历,BFS
 * 节点的高度（后序递归）
 * 节点的深度（前序递归）
 * [559] N 叉树的最大深度
 */

//* 节点的深度：指从根节点到该节点的最长简单路径边的条数或者节点数（取决于深度从0开始还是从1开始）
//* 节点的高度：指从该节点到叶子节点的最长简单路径边的条数或者节点数（取决于高度从0开始还是从1开始）

//* 迭代法：层序遍历（BFS，广度优先遍历），使用队列
//* 递归法：节点的高度（后序递归），节点的深度（前序递归）

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

//* 迭代法
class Solution {
public:
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
};

//* 递归法一
//* 求树的最大深度，即求根节点的最大高度
//* 求高度可用后序遍历
//! 注意，不能用后序遍历的迭代法，因为不知道当前栈顶的节点是哪一层
class Solution {
public:
    int maxDepth(Node* root) {
        if (root == 0) return 0;
        int depth = 0;
        for (int i = 0; i < root->children.size(); i++) {
            depth = max (depth, maxDepth(root->children[i]));
        }
        return depth + 1;
    }
};

//* 递归法二
//* 直接求二叉树的最大深度
//* 求深度可用前序遍历（根左右）
class Solution {
public:
    int result;
    void getdepth(Node* node, int depth) {
        result = depth > result ? depth : result;   //* 中

        if (node->children.empty()) return ;

        for (Node* it : node->children) {           //* 遍历每一个孩子
            depth++;        //* 深度+1
            getdepth(it, depth);
            depth--;        //* 回溯，深度-1
        }
        return ;
    }
    int maxDepth(Node* root) {
        result = 0;
        if (root == NULL) return result;
        getdepth(root, 1);
        return result;
    }
};
// @lc code=end

