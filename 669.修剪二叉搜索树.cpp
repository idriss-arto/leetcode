/*
 * @lc app=leetcode.cn id=669 lang=cpp
 * 二叉搜索树
 * [669] 修剪二叉搜索树
 */

/*
 * 递归法思路：
 * 关键步骤：如果当前节点不满足，但左子树或右子树中有满足的节点，如何处理
 *
 * 迭代法思路：
 * 将root移动到[L, R] 范围内，注意是左闭右闭区间
 * 剪枝左子树
 * 剪枝右子树
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

//* 递归法
class Solution {
public:
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
};

//* 迭代法
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if (!root) return nullptr;

        //* 处理头结点，让root移动到[L, R] 范围内，注意是左闭右闭
        while (root != nullptr && (root->val < L || root->val > R)) {
            if (root->val < L) root = root->right;  //* 小于L往右走
            else root = root->left;                 //* 大于R往左走
        }
        
        TreeNode *cur = root;
        //* 此时root已经在[L, R] 范围内，处理左孩子小于L的元素
        while (cur != nullptr) {
            while (cur->left && cur->left->val < L) {
                cur->left = cur->left->right;
            }
            cur = cur->left;
        }

        cur = root;
        //* 此时root已经在[L, R] 范围内，处理右孩子中大于R的元素
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

