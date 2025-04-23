/*
 * @lc app=leetcode.cn id=235 lang=cpp
 * 二叉搜索树
 * [235] 二叉搜索树的最近公共祖先
 */

/*
 * 思路：
 * 依据二叉搜索树的性质，从上往下走
 * 当给定的两个节点都小于当前节点时，到当前节点的左子树
 * 当给定的两个节点都大于当前节点时，到当前节点的右子树
 * 当第一次满足给定两个节点分别在当前节点左子树和右子树上时，当前节点即为最近公共祖先
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

//* 递归法
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return root;
        if (p->val >  q->val) {
            TreeNode* tmp = p;
            p = q;
            q = tmp;
        }
        if (p->val <= root->val && q->val >= root->val) return root;
        else if (p->val > root->val) return lowestCommonAncestor(root->right, p, q);
        else return lowestCommonAncestor(root->left, p, q);
    }
};


//* 迭代法
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p->val >  q->val) {
            TreeNode* tmp = p;
            p = q;
            q = tmp;
        }
        while (root) {
            if (p->val > root->val) root = root->right;
            else if (q->val < root->val) root = root->left;
            else return root;
        }
        return root;
    }
};
// @lc code=end

