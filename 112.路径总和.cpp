/*
 * @lc app=leetcode.cn id=112 lang=cpp
 * 二叉树，回溯
 * [112] 路径总和
 */

/*
 * 思路：
 * 递归法：将target减去自己的值，再递归左孩子和右孩子。因为递归函数中target是值引用，所以隐含回溯
 * 迭代法：后序遍历，因为回溯时应该先删叶子节点的值，即叶子节点最先弹出
 * 题解迭代法：栈中不止放节点指针，还有对应到该节点的路径数值，即pair<节点指针，路径数值>
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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr && root->val == targetSum) return true;
        return (hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val));
    }
};

//* 迭代法
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;
        vector<int> path;
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
                    if (sum == targetSum) return true;
                }
                path.pop_back();
                //* 回溯
                sum -= cur->val;
            }
        }
        return false;
    }
};

//* 题解迭代法
class solution {
public:
    bool haspathsum(TreeNode* root, int sum) {
        if (root == nullptr) return false;
        //* 此时栈里要放的是pair<节点指针，路径数值>
        stack<pair<TreeNode*, int>> st;
        st.push(pair<TreeNode*, int>(root, root->val));
        while (!st.empty()) {
            pair<TreeNode*, int> node = st.top();
            st.pop();
            //* 如果该节点是叶子节点了，同时该节点的路径数值等于sum，那么就返回true
            if (!node.first->left && !node.first->right && sum == node.second) return true;

            //* 右节点，压进去一个节点的时候，将该节点的路径数值也记录下来
            if (node.first->right) {
                st.push(pair<TreeNode*, int>(node.first->right, node.second + node.first->right->val));
            }

            //* 左节点，压进去一个节点的时候，将该节点的路径数值也记录下来
            if (node.first->left) {
                st.push(pair<TreeNode*, int>(node.first->left, node.second + node.first->left->val));
            }
        }
        return false;
    }
};
// @lc code=end

