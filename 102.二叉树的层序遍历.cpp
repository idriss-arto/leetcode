/*
 * @lc app=leetcode.cn id=102 lang=cpp
 * 树的层次遍历,BFS
 * [102] 二叉树的层序遍历
 */

//* 层序遍历（BFS，广度优先遍历），使用队列

// @lc code=start
#include <vector>
#include <queue>
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) que.push(root);
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            //* vec用来装一层的节点
            vector<int> vec;
            //! 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            //* 将一层的节点放入答案
            result.push_back(vec);
        }
        return result;
    }
};
// @lc code=end

