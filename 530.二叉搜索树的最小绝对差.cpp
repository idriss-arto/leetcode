/*
 * @lc app=leetcode.cn id=530 lang=cpp
 *
 * [530] 二叉搜索树的最小绝对差
 */

// @lc code=start
#include <vector>
#include <queue>
#include <stack>
#include <climits>
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
    //* 迭代法
    int getMinimumDifference(TreeNode* root) {
        int min = INT_MAX;
        stack<TreeNode*> sta;
        sta.push(root);
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        while (!sta.empty()) {
            cur = sta.top();
            sta.pop();
            if (cur != nullptr) {
                if (cur->right) sta.push(cur->right);

                sta.push(cur);
                sta.push(nullptr);

                if (cur->left) sta.push(cur->left);
            }
            else {
                cur = sta.top();
                sta.pop();
                if (pre == nullptr) {
                    pre = cur;
                    continue;
                }
                else {
                    int x = cur->val - pre->val;
                    min = min < x ? min : x;
                    pre = cur;
                }
            }
        }
        return min;
    }

    //* 递归法
    int result = INT_MAX;
    TreeNode* pre = NULL;
    void traversal(TreeNode* cur) {
        if (cur == NULL) return;
        traversal(cur->left);   // 左
        if (pre != NULL){       // 中
            result = min(result, cur->val - pre->val);
        }
        pre = cur; // 记录前一个
        traversal(cur->right);  // 右
    }
    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;
    }
};
// @lc code=end

