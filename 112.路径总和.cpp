/*
 * @lc app=leetcode.cn id=112 lang=cpp
 *
 * [112] 路径总和
 */
/*
如果需要搜索整棵二叉树且不用处理递归返回值，递归函数就不要返回值。（这种情况就是本文下半部分介绍的113.路径总和ii）
如果需要搜索整棵二叉树且需要处理递归返回值，递归函数就需要返回值。 （这种情况我们在236. 二叉树的最近公共祖先 (opens new window)中介绍）
如果要搜索其中一条符合条件的路径，那么递归一定需要返回值，因为遇到符合条件的路径了就要及时返回。（本题的情况）
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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr && root->val == targetSum) return true;
        return (hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val));
    }

    // 迭代法
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
                // 应该是后序，因为路径和中根节点的值应该是最后减去的
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
                if (!cur->left && !cur->right) {
                    if (sum == targetSum) return true;
                }
                path.pop_back();
                sum -= cur->val;
            }
        }
        return false;
    }
};
// @lc code=end

