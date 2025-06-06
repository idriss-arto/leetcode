/*
 * @lc app=leetcode.cn id=617 lang=cpp
 * 二叉树，同时处理多棵树
 * [617] 合并二叉树
 */

/*
 * 两种思路
 * 要不就创建一颗新的树，要不就在原来的一颗树上改
*/

// @lc code=start
#include <vector>
#include <queue>
#include <stack>
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
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr) return t2;
        if (t2 == nullptr) return t1;
        //* 重新定义新的节点，不修改原有两个树的结构
        TreeNode* root = new TreeNode(0);
        root->val = t1->val + t2->val;
        root->left = mergeTrees(t1->left, t2->left);
        root->right = mergeTrees(t1->right, t2->right);
        return root;
    }

    //* 迭代法
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr) return t2;
        if (t2 == nullptr) return t1;
        queue<TreeNode*> que;
        que.push(t1);
        que.push(t2);
        while(!que.empty()) {
            TreeNode* node1 = que.front(); que.pop();
            TreeNode* node2 = que.front(); que.pop();
            //* 此时两个节点一定不为空，val相加
            node1->val += node2->val;

            //* 如果两棵树左节点都不为空，加入队列
            if (node1->left != nullptr && node2->left != nullptr) {
                que.push(node1->left);
                que.push(node2->left);
            }
            //* 如果两棵树右节点都不为空，加入队列
            if (node1->right != nullptr && node2->right != nullptr) {
                que.push(node1->right);
                que.push(node2->right);
            }

            //* 当t1的左节点为空 t2左节点不为空，就赋值过去
            if (node1->left == nullptr && node2->left != nullptr) {
                node1->left = node2->left;
            }
            //* 当t1的右节点为空 t2右节点不为空，就赋值过去
            if (node1->right == nullptr && node2->right != nullptr) {
                node1->right = node2->right;
            }
        }
        return t1;
    }
};
// @lc code=end

