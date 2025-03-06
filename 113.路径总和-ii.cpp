/*
 * @lc app=leetcode.cn id=113 lang=cpp
 *
 * [113] 路径总和 II
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
    vector<int> path;
    vector<vector<int>> result;
    void traversal(TreeNode* root, int targetSum) {
        if (!root->left && !root->right && root->val == targetSum) {
            path.emplace_back(root->val);
            result.emplace_back(path);
            path.pop_back();
            return;
        }
        if (!root->left && !root->right) {
            return;
        }
        path.emplace_back(root->val);
        if (root->left) {
            traversal(root->left, targetSum - root->val);
        }
        if (root->right) {
            traversal(root->right, targetSum - root->val);
        }
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (!root) return result;
        traversal(root, targetSum);
        return result;
    }
};
// @lc code=end

