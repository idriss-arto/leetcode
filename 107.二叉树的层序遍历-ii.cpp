/*
 * @lc app=leetcode.cn id=107 lang=cpp
 * 树的层次遍历,BFS
 * [107] 二叉树的层序遍历 II
 */

//* 层序遍历（BFS，广度优先遍历），使用队列
//! 要求自底往上，按照自顶往下求完后反转一下即可

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != nullptr) que.push(root);
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            //! 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(vec);
        }
        //! 要求result里最底层的放最前面，在这里反转一下数组即可
        reverse(result.begin(), result.end()); 
        return result;
    }
};
// @lc code=end
// @lc code=end

