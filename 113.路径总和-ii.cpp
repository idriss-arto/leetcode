/*
 * @lc app=leetcode.cn id=113 lang=cpp
 * 二叉树，回溯
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

//* 递归法
class Solution {
public:
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

//* 迭代法
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> path;
        vector<vector<int>> result;
        if (root == nullptr) return result;
        int sum = 0;
        stack<TreeNode*> sta;
        sta.emplace(root);
        while (!sta.empty()) {
            TreeNode* cur = sta.top();
            sta.pop();
            if (cur) {
                //* 应该是后序，因为路径和中根节点的值应该是最后减去的
                sta.push(cur);
                sta.push(nullptr);
                path.emplace_back(cur->val);
                sum += cur->val;
                if (cur->right) sta.emplace(cur->right);
                if (cur->left) sta.emplace(cur->left);
            }
            else {
                cur = sta.top();
                sta.pop();
                //* 先判断当前节点是否为叶子节点
                if (!cur->left && !cur->right) {
                    if (sum == targetSum) {
                        result.push_back(path);
                    }
                }
                path.pop_back();
                //* 回溯
                sum -= cur->val;
            }
        }
        return result;
    }
};
// @lc code=end

