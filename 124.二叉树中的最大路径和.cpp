/*
 * @lc app=leetcode.cn id=124 lang=cpp
 * 二叉树（递归）
 ! [124] 二叉树中的最大路径和
 */

/*
 * 思路：后续递归计算当前最大值和贡献值
 * 注意，计算当前节点的 最大路径和 可以包含左右节点，但最大贡献度不能同时包括左右节点。
 * 因为对于某节点，他的贡献只能带其中一个孩子（带大孩子走），整个路径才能向上延伸
*/

//! 不要想着用递归函数返回值记录全局最大值，
//! 上层节点无法利用下层节点返回的全局最大值（因为不一定能连成一条路径）。

// @lc code=start
#include <climits>
#include <algorithm>
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

class Solution {
private:
    int maxSum = INT_MIN;

public:
    int maxGain(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        //* 递归计算左右子节点的最大贡献值
        //* 只有在最大贡献值大于 0 时，才会选取对应子节点
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        //* 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
        int priceNewpath = node->val + leftGain + rightGain;

        //* 更新答案
        maxSum = max(maxSum, priceNewpath);

        //* 返回节点的最大贡献值
        return node->val + max(leftGain, rightGain);
    }

    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
};
// @lc code=end

