/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 */

// @lc code=start
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <unordered_map>
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
    //* 递归法
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q || !root) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p ,q);
        TreeNode* right = lowestCommonAncestor(root->right, p ,q);
        if (left != nullptr && right != nullptr) return root;
        else if (left == nullptr && right) return right;
        else if (right == nullptr && left) return left;
        else return nullptr;
    }

    /*
     * 存储父节点
     * 用哈希表存储所有节点的父节点，然后我们就可以利用节点的父节点信息从 p 结点开始不断往上跳，
     * 并记录已经访问过的节点，再从 q 节点开始不断往上跳，如果碰到已经访问过的节点，
     * 那么这个节点就是我们要找的最近公共祖先。
    */
    unordered_map<TreeNode*, TreeNode*> fa;
    unordered_map<TreeNode*, bool> vis;
    void dfs(TreeNode* root){
        if (root->left != nullptr) {
            fa[root->left] = root;
            dfs(root->left);
        }
        if (root->right != nullptr) {
            fa[root->right] = root;
            dfs(root->right);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        fa[root] = nullptr;
        dfs(root);
        while (p != nullptr) {
            vis[p] = true;
            p = fa[p];
        }
        while (q != nullptr) {
            if (vis[q]) return q;
            q = fa[q];
        }
        return nullptr;
    }
};
// @lc code=end

