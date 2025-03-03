/*
 * @lc app=leetcode.cn id=111 lang=cpp
 * 树的层次遍历,BFS
 * [111] 二叉树的最小深度
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
class Solution {
public:
    // 迭代法
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> que;
        que.push(root);
        int depth = 0;
        int flag = 0;
        while (!que.empty()) {
            depth++;
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* cur = que.front();
                que.pop();
                if (!cur->left && !cur->right) {
                    flag = 1;
                    break;
                }
                if (cur->left) que.push(cur->left);
                if (cur->right) que.push(cur->right);
            }
            if (flag) break;
        }
        return depth;
    }
};
// @lc code=end

