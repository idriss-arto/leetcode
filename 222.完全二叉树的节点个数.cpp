/*
 * @lc app=leetcode.cn id=222 lang=cpp
 * 二叉树
 * [222] 完全二叉树的节点个数
 */

/*
 * 思路：
 * 普通二叉树：任意遍历加计数 
 * 完全二叉树：可对比向左递归深度和向右递归深度，判断当前完全二叉树是否为满二叉树
*/

// @lc code=start
#include <vector>
#include <queue>
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

//* 普通二叉树，迭代法，层次遍历
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        int cnt = 0;
        queue <TreeNode*> que;
        que.emplace(root);
        while (!que.empty()) {
            int size = que.size();
            TreeNode* cur;
            for (int i = 0; i < size; i++) {
                cur = que.front();
                cnt++;
                que.pop();
                if (cur->left) que.emplace(cur->left);
                if (cur->right) que.emplace(cur->right);
            }
        }
        return cnt;
    }
};

//* 完美二叉树，递归法
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        int leftDepth = 0, rightDepth = 0;  //* 这里初始为0是有目的的，为了下面求指数方便
        while (left) {                      //* 求向左递归深度
            left = left->left;
            leftDepth++;
        }
        while (right) {                     //* 求向右递归深度
            right = right->right;
            rightDepth++;
        }
        if (leftDepth == rightDepth) {
            return (2 << leftDepth) - 1;    //* 注意(2<<1) 相当于2^2，所以leftDepth初始为0
        }
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};
// @lc code=end

