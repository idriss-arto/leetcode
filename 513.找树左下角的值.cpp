/*
 * @lc app=leetcode.cn id=513 lang=cpp
 *
 * [513] 找树左下角的值
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
    // 题解的递归法，不会对一个节点重复求深度
    int maxDepth = INT_MIN;
    int result;
    void traversal(TreeNode* root, int depth) {
        if (root->left == NULL && root->right == NULL) {
            if (depth > maxDepth) {
                maxDepth = depth;
                result = root->val;
            }
            return;
        }
        if (root->left) {
            traversal(root->left, depth + 1); // 隐藏着回溯
        }
        if (root->right) {
            traversal(root->right, depth + 1); // 隐藏着回溯
        }
        return;
    }
    int findBottomLeftValue(TreeNode* root) {
        traversal(root, 0);
        return result;
    }

    // 递归法
    int getDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        else return max(getDepth(root->left), getDepth(root->right)) + 1;
    }

    int findBottomLeftValue(TreeNode* root) {
        if (root == nullptr) return 0;
        else if (root->left == nullptr && root->right == nullptr) return root->val;
        else {
            int leftDepth = getDepth(root->left);
            int rightDepth = getDepth(root->right);
            return getDepth(root->right) > getDepth(root->left) ? findBottomLeftValue(root->right) : findBottomLeftValue(root->left);
        }
    }

    // 迭代法
    int findBottomLeftValue(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> que;
        que.emplace(root);
        int result = 0;
        while (!que.empty()) {
            int size = que.size();
            TreeNode* cur;
            for (int i = 0; i < size; i++) {
                cur = que.front();
                que.pop();
                if (i == 0) result = cur->val;
                if (cur->left) que.emplace(cur->left);
                if (cur->right) que.emplace(cur->right);
            }
        }
        return result;
    }
};
// @lc code=end

