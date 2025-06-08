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

//* 官方题解
//* 全局维护一个变量来记录当前最大直径，递归函数只返回自己能做的贡献
//* 递归函数内部判断更简单
class Solution {
    int ans;

    //* 获取rt节点的高度，叶子节点的高度为0
    int getHeight(TreeNode* rt){
        if (rt == NULL) {
            return -1;                  //* 访问到空节点了，返回-1
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

//* 我的题解
//* 递归函数同时返回自己能做的贡献，和当前最大直径
//* 不建议这种写法，处理左右孩子返回的数据时很麻烦
class Solution {
public:
    //* 返回值中第一个是可以继续拼接的，第二个参数是已经是一条路
    pair<int, int> maxLen(TreeNode* root) {
        if (!root) return {-1, 0};
        pair<int, int> leftResult = maxLen(root->left);
        pair<int, int> rightResult = maxLen(root->right);
        return {1 + max(leftResult.first, rightResult.first), 
                max({leftResult.second, rightResult.second, 2 + leftResult.first + rightResult.first})
                };
    }

    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        pair<int, int> leftResult = maxLen(root->left);
        pair<int, int> rightResult = maxLen(root->right);
        return max({2 + leftResult.first + rightResult.first, leftResult.second, rightResult.second});
    }
};
// @lc code=end

