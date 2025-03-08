/*
 * @lc app=leetcode.cn id=235 lang=cpp
 *
 * [235] 二叉搜索树的最近公共祖先
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return root;
        if (p->val >  q->val) {
            TreeNode* tmp = p;
            p = q;
            q = tmp;
        }
        if (p->val <= root->val && q->val >= root->val) return root;
        else if (p->val > root->val) return lowestCommonAncestor(root->right, p, q);
        else return lowestCommonAncestor(root->left, p, q);
    }

    //* 迭代法
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p->val >  q->val) {
            TreeNode* tmp = p;
            p = q;
            q = tmp;
        }
        while (root) {
            if (p->val > root->val) root = root->right;
            else if (q->val < root->val) root = root->left;
            else return root;
        }
        return root;
    }
};
// @lc code=end

