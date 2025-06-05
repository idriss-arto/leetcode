/*
 * @lc app=leetcode.cn id=199 lang=cpp
 * 树的层次遍历,BFS
 * [199] 二叉树的右视图
 */

//* 层序遍历（BFS，广度优先遍历），使用队列
//! 要求答案中只存储每一层的最后一个节点，则queue遍历时多加一个判断即可

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

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) que.push(root);
        vector<int> result;
        while (!que.empty()) {
            int size = que.size();
            //! 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (i == size - 1) result.push_back(node->val);     //! 判断是否是某一层最后一个值
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
        }
        return result;
    }
};
// @lc code=end

