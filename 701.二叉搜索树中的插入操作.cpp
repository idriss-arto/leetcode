/*
 * @lc app=leetcode.cn id=701 lang=cpp
 *
 * [701] 二叉搜索树中的插入操作
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
    TreeNode* parent = nullptr;
    void traversal(TreeNode* root, int val) {
        if (root == nullptr) {
            TreeNode* cur = new TreeNode(val);
            if (parent->val > val) parent->left = cur;
            else parent->right = cur;
        }
        parent = root;
        if (root->val > val) traversal(root->left, val);
        else traversal(root->right, val);
    }

    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == NULL) {
            root = new TreeNode(val);
        }
        else traversal(root, val);
        return root;
    }
    /*
     * 递归代码也可以这样写，利用函数返回值完成父子节点的赋值
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == NULL) {
            TreeNode* node = new TreeNode(val);
            return node;
        }
        if (root->val > val) root->left = insertIntoBST(root->left, val);
        if (root->val < val) root->right = insertIntoBST(root->right, val);
        return root;
    }
    */

    //* 迭代法
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            TreeNode* cur = new TreeNode(val);
            return cur;
        }
        
        TreeNode* cur = root;
        while (cur) {
            if (cur->val < val) {
                if (cur->right == nullptr) {
                    TreeNode* node = new TreeNode(val);
                    cur->right = node;
                    break;
                }
                else cur = cur->right;
            }
            else {
                if (cur->left == nullptr) {
                    TreeNode* node = new TreeNode(val);
                    cur->left = node;
                    break;
                }
                else cur = cur->left;
            }
        }
        return root;
    }
};
// @lc code=end

