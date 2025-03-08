/*
 * @lc app=leetcode.cn id=669 lang=cpp
 *
 * [669] 修剪二叉搜索树
 */

// @lc code=start
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <unordered_map>
using namespace std;
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    //* 递归法
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == nullptr) return root;
        if (root->val < low) {
            return trimBST(root->right, low, high);
        }
        if (root->val > high) {
            return trimBST(root->left, low, high);
        }
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }

    //* 迭代法
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if (!root) return nullptr;

        //* 处理头结点，让root移动到[L, R] 范围内，注意是左闭右闭
        while (root != nullptr && (root->val < L || root->val > R)) {
            if (root->val < L) root = root->right; // 小于L往右走
            else root = root->left; // 大于R往左走
        }
        
        TreeNode *cur = root;
        //* 此时root已经在[L, R] 范围内，处理左孩子元素小于L的情况
        while (cur != nullptr) {
            while (cur->left && cur->left->val < L) {
                cur->left = cur->left->right;
            }
            cur = cur->left;
        }

        cur = root;
        //* 此时root已经在[L, R] 范围内，处理右孩子大于R的情况
        while (cur != nullptr) {
            while (cur->right && cur->right->val > R) {
                cur->right = cur->right->left;
            }
            cur = cur->right;
        }
        return root;
    }
};
// @lc code=end

