/*
 * @lc app=leetcode.cn id=230 lang=cpp
 * 二叉树
 * [230] 二叉搜索树中第 K 小的元素
 */

/*
 * 思路一：生成一个数组储存二叉树中序遍历的结果
 * 思路二：直接中序遍历过程中找第k小的值
*/

// @lc code=start
#include <vector>
#include <stack>
using namespace std;

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//* 递归法，生成一个数组储存二叉树中序遍历的结果
class Solution {
public:
    vector<int> nums;

    void traversal(TreeNode* root) {
        if (!root) return;
        traversal(root->left);
        nums.push_back(root->val);
        traversal(root->right);
    }

    int kthSmallest(TreeNode* root, int k) {
        traversal(root);
        return nums[k-1];
    }
};

//* 迭代法，直接中序遍历过程中找第k小的值
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> sta;
        sta.push(root);

        while (!sta.empty()) {
            TreeNode* cur = sta.top();
            sta.pop();
            if (cur) {
                if (cur->right) sta.push(cur->right);
                sta.push(cur);
                sta.push(nullptr);
                if (cur->left) sta.push(cur->left);
            }
            else {
                cur = sta.top();
                sta.pop();
                k--;
                if (k == 0) {
                    return cur->val;
                }
            }
        }
        
        return 0;
    }
};
// @lc code=end

