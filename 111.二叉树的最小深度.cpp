/*
 * @lc app=leetcode.cn id=111 lang=cpp
 * 树的层次遍历,BFS
 * 节点的高度（后序递归）
 * 节点的深度（前序递归）
 * [111] 二叉树的最小深度
 */

//* 节点的深度：指从根节点到该节点的最长简单路径边的条数或者节点数（取决于深度从0开始还是从1开始）
//* 节点的高度：指从该节点到叶子节点的最长简单路径边的条数或者节点数（取决于高度从0开始还是从1开始）

//* 迭代法：层序遍历（BFS，广度优先遍历），使用队列
//* 递归法：节点的高度（后序递归），节点的深度（前序递归）

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

//* 迭代法
class Solution {
public:
    int minDepth(TreeNode* root) {
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
                //! 左右孩子均为空，说明为叶子结点
                if (!cur->left && !cur->right) {
                    return depth;
                }
                if (cur->left) que.push(cur->left);
                if (cur->right) que.push(cur->right);
            }
        }
        return depth;
    }
};

//* 递归法一
//* 求树的最小深度，即求根节点的最小高度
//* 求高度可用后序遍历
//! 注意，不能用后序遍历的迭代法，因为不知道当前栈顶的节点是哪一层
class Solution {
public:
    int getDepth(TreeNode* node) {
        if (node == NULL) return 0;
        int leftDepth = getDepth(node->left);           //* 左
        int rightDepth = getDepth(node->right);         //* 右
                                                        //* 中
        //* 当一个左子树为空，右不为空，这时并不是最低点
        if (node->left == NULL && node->right != NULL) { 
            return 1 + rightDepth;
        }   
        //* 当一个右子树为空，左不为空，这时并不是最低点
        if (node->left != NULL && node->right == NULL) { 
            return 1 + leftDepth;
        }
        int result = 1 + min(leftDepth, rightDepth);
        return result;
    }

    int minDepth(TreeNode* root) {
        return getDepth(root);
    }
};

//* 递归法二
//* 直接求二叉树的最小深度
//* 求深度可用前序遍历（根左右）
class Solution {
private:
    int result;
    void getdepth(TreeNode* node, int depth) {
        //* 函数递归终止条件
        if (node == nullptr) {
            return;
        }
        //* 中，处理逻辑：判断是不是叶子结点
        if (node -> left == nullptr && node->right == nullptr) {
            result = min(result, depth);
        }
        if (node->left) {   //* 左
            getdepth(node->left, depth + 1);
        }
        if (node->right) {  //* 右
            getdepth(node->right, depth + 1);
        }
        return ;
    }

public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        result = INT_MAX;
        getdepth(root, 1);
        return result;
    }
};
// @lc code=end

