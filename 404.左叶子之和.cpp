/*
 * @lc app=leetcode.cn id=404 lang=cpp
 * 二叉树
 * [404] 左叶子之和
 */

/*
 * 递归法思路：在递归函数参数中加一个参数分辨当前节点是否为父节点左孩子
 * 迭代法思路：前序遍历，某节点出栈时，分辨是否有左孩子以及左孩子是否为叶子结点
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
};

//* 迭代法
class Solution {
public:
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

