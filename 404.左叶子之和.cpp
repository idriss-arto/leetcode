/*
 * @lc app=leetcode.cn id=404 lang=cpp
 *
 * [404] 左叶子之和
 */

// @lc code=start
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
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
    // 递归法
    int getLeftSum(TreeNode* root, bool isLeft){
        if (root == nullptr) return 0;
        else if (isLeft && root->left == nullptr && root->right == nullptr) {
             return root->val;
        }
        else {
            return getLeftSum(root->left, true) + getLeftSum(root->right, false);
        }
    }

    int sumOfLeftLeaves(TreeNode* root) {
        return getLeftSum(root->left, true) + getLeftSum(root->right, false);
    }

    // 迭代法
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) return 0;
        int result = 0;
        stack<TreeNode*> sta;
        sta.emplace(root);
        while (!sta.empty()) {
            TreeNode* cur = sta.top();
            sta.pop();
            if (cur != nullptr) {
                if (cur->right) sta.emplace(cur->right);
                if (cur->left) sta.emplace(cur->left);
                sta.emplace(cur);
                sta.emplace(nullptr);
            }
            else {
                cur = sta.top();
                sta.pop();
                if (cur->left != nullptr && cur->left->left == nullptr && cur->left->right == nullptr) {
                    result += cur->left->val;
                }
            }
        }
        return result;
    }
};
// @lc code=end

