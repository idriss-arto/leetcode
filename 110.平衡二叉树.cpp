/*
 * @lc app=leetcode.cn id=110 lang=cpp
 * 二叉树
 * [110] 平衡二叉树
 */

// @lc code=start
#include <vector>
#include <queue>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//* 后序递归法
class Solution {
public:
    //* 返回以该节点为根节点的二叉树的高度，如果不是平衡二叉树了则返回-1
    int getHeight(TreeNode* node) {
        if (node == NULL) {
            return 0;
        }
        int leftHeight = getHeight(node->left);
        if (leftHeight == -1) return -1;
        int rightHeight = getHeight(node->right);
        if (rightHeight == -1) return -1;
        return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);
    }
    bool isBalanced(TreeNode* root) {
        return getHeight(root) == -1 ? false : true;
    }
};

//* 迭代法
class Solution {
private:
    //* 求以传入节点为根节点的子树的最大深度，即传入节点的高度
    //* 这里用的后序遍历+回溯，但其实层序遍历简单些
    //* 还有后序递归遍历、前序+回溯等方法，详见104
    int getDepth(TreeNode* cur) {
        stack<TreeNode*> st;
        if (cur != NULL) st.push(cur);
        int depth = 0;                  //* 记录深度
        int result = 0;
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != NULL) {
                st.pop();
                st.push(node);                          //* 中
                st.push(NULL);
                depth++;
                if (node->right) st.push(node->right);  //* 右
                if (node->left) st.push(node->left);    //* 左

            } else {
                st.pop();
                node = st.top();
                st.pop();
                depth--;
            }
            result = result > depth ? result : depth;
        }
        return result;
    }

public:
    bool isBalanced(TreeNode* root) {
        stack<TreeNode*> st;
        if (root == NULL) return true;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();                       //* 中
            st.pop();
            if (abs(getDepth(node->left) - getDepth(node->right)) > 1) {
                return false;
            }
            if (node->right) st.push(node->right);           //* 右（空节点不入栈）
            if (node->left) st.push(node->left);             //* 左（空节点不入栈）
        }
        return true;
    }
};
// @lc code=end

