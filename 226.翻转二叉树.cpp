/*
 * @lc app=leetcode.cn id=226 lang=cpp
 * 二叉树
 * [226] 翻转二叉树
 */

//* 层序遍历（BFS）和前序或后序（DFS）都可以
//! 中序不行

// @lc code=start
#include <vector>
#include <queue>
using namespace std;

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//* 层序遍历
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return root;
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
        //! 这里没定义size，是因为不用按照层次序列访问节点，只需保证所有节点左右孩子交换即可
            TreeNode* cur = que.front();
            que.pop();
            TreeNode* tmp = cur->left;
            cur->left = cur->right;
            cur->right = tmp;
            if (cur->left) que.push(cur->left);
            if (cur->right) que.push(cur->right);
        }
        return root;
    }
};

//* 前序遍历
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

//* 后序遍历
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        invertTree(root->left);
        invertTree(root->right);
        swap(root->left, root->right);
        return root;
    }
};
// @lc code=end

