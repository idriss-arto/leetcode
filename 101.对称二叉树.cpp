/*
 * @lc app=leetcode.cn id=101 lang=cpp
 * 二叉树
 * [101] 对称二叉树
 */

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

//* 递归法
class Solution {
public:
    bool compare(TreeNode* left, TreeNode* right) {
        //* 首先排除空节点的情况
        if (left == nullptr && right != nullptr) return false;
        else if (left != nullptr && right == nullptr) return false;
        else if (left == nullptr && right == nullptr) return true;
        //* 排除了空节点，再排除数值不相同的情况
        else if (left->val != right->val) return false;

        //* 此时就是：左右节点都不为空，且数值相同的情况
        //* 此时才做递归，做下一层的判断
        bool outside = compare(left->left, right->right);   //* 左子树：左、 右子树：右
        bool inside = compare(left->right, right->left);    //* 左子树：右、 右子树：左
        bool isSame = outside && inside;                    //* 左子树：中、 右子树：中 （逻辑处理）
        return isSame;

    }

    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return compare(root->left, root->right);
    }
};

//* 迭代法
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        queue<TreeNode*> que;
        que.push(root->left);   //* 将左子树头结点加入队列
        que.push(root->right);  //* 将右子树头结点加入队列
        
        while (!que.empty()) {  //* 接下来就要判断这两个树是否相互翻转
            TreeNode* leftNode = que.front(); que.pop();
            TreeNode* rightNode = que.front(); que.pop();
            if (!leftNode && !rightNode) {  //* 左节点为空、右节点为空，此时说明是对称的
                continue;
            }

            //* 左右一个节点不为空，或者都不为空但数值不相同，返回false
            if ((!leftNode || !rightNode || (leftNode->val != rightNode->val))) {
                return false;
            }
            que.push(leftNode->left);   //* 加入左节点左孩子
            que.push(rightNode->right); //* 加入右节点右孩子
            que.push(leftNode->right);  //* 加入左节点右孩子
            que.push(rightNode->left);  //* 加入右节点左孩子
        }
        return true;
    }
};
// @lc code=end

