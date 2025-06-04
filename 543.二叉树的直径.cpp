/*
 * @lc app=leetcode.cn id=543 lang=cpp
 * 二叉树，树的高度
 * [543] 二叉树的直径
 */

// @lc code=start


//* Definition for a binary tree node.
#include <utility>
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

//* 我的题解
class Solution {
public:
    //* 返回值中第一个是可以继续拼接的，第二个参数是已经是一条路
    pair<int, int> maxLen(TreeNode* root) {
        if (!root) return {0, 0};
        pair<int, int> leftResult = maxLen(root->left);
        pair<int, int> rightResult = maxLen(root->right);
        return {max(leftResult.first, rightResult.first), 
                max({leftResult.second, rightResult.second, leftResult.first + rightResult.first})
                };
    }

    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        pair<int, int> leftResult = maxLen(root->left);
        pair<int, int> rightResult = maxLen(root->right);
        return max({max(leftResult.first, rightResult.first), leftResult.second, rightResult.second});
    }
};

//* 官方题解
class Solution {
    int ans;

    //* 获取rt节点的高度，叶子节点的高度为0
    int getHeight(TreeNode* rt){
        if (rt == NULL) {
            return -1;                  //* 访问到空节点了，返回0
        }
        int L = getHeight(rt->left);    //* 左儿子为根的子树的高度
        int R = getHeight(rt->right);   //* 右儿子为根的子树的高度
        ans = max(ans, L + R + 2);      //* 计算以root为根的子树中，包含root的最长路径的边数，即 L+R+2 并更新ans
        return max(L, R) + 1;           //* 返回该节点为根的子树的高度
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        getHeight(root);
        return ans - 1;
    }
};
// @lc code=end

