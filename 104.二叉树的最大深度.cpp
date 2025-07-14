/*
 * @lc app=leetcode.cn id=104 lang=cpp
 * 树的层次遍历，BFS
 * 节点的高度（后序递归）
 * 节点的深度（前序递归）
 * [104] 二叉树的最大深度
 */

//* 节点的深度：指从根节点到该节点的最长简单路径边的条数或者节点数（取决于深度从0开始还是从1开始）
//* 节点的高度：指从该节点到叶子节点的最长简单路径边的条数或者节点数（取决于高度从0开始还是从1开始）

//* 迭代法：层序遍历（BFS，广度优先遍历），使用队列
//* 递归法：节点的高度（后序递归），节点的深度（前序递归+回溯）

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

//* 迭代法（层序遍历，队列）
//* 每进入新的一层，深度加一
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> que;
        que.push(root);
        int depth = 0;
        while (!que.empty()) {
            depth++;
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* cur = que.front();
                que.pop();
                if (cur->left) que.push(cur->left);
                if (cur->right) que.push(cur->right);
            }
        }
        return depth;
    }
};

//* 递归法一
//* 求二叉树的最大深度，即求根节点的最大高度
//* 求高度可用后序遍历（左右根），当前节点高度为左右节点高度中的较大值加一
//! 注意，如果用后序遍历的迭代法，需要用额外的数据结构记录每个节点的高度
class Solution {
public:
    int getdepth(TreeNode* node) {
        if (node == NULL) return 0;
        int leftdepth = getdepth(node->left);           //* 左
        int rightdepth = getdepth(node->right);         //* 右
        int depth = 1 + max(leftdepth, rightdepth);     //* 中
        return depth;
    }
    int maxDepth(TreeNode* root) {
        return getdepth(root);
    }
};

//* 递归法二
//* 直接求二叉树的最大深度
//* 求深度可用前序遍历（根左右）+回溯，进入左右子节点时深度加一，返回当前节点时深度减一
class Solution {
public:
    int result;
    void getdepth(TreeNode* node, int depth) {
        result = depth > result ? depth : result;   //* 中

        if (node->left == NULL && node->right == NULL) return ;

        if (node->left) {   //* 左
            depth++;        //* 深度+1
            getdepth(node->left, depth);
            depth--;        //* 回溯，深度-1
        }
        if (node->right) {  //* 右
            depth++;        //* 深度+1
            getdepth(node->right, depth);
            depth--;        //* 回溯，深度-1
        }
        return ;
    }
    int maxDepth(TreeNode* root) {
        result = 0;
        if (root == NULL) return result;
        getdepth(root, 1);
        return result;
    }
};
// @lc code=end

