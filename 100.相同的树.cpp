/*
 * @lc app=leetcode.cn id=100 lang=cpp
 *
 * [100] 相同的树
 */

// @lc code=start
#include <vector>
#include <queue>
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
    bool compare(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        else if (!p || !q || p->val != q->val) return false;
        else {
            return compare(p->left, q->left) && compare(p->right, q->right);
        }
    }

    // 递归法
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        else if (!p || !q || p->val != q->val) return false;
        else {
            return compare(p->left, q->left) && compare(p->right, q->right);
        }
    }

    // 迭代法
    bool isSameTreeV2(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        else if (!p || !q || p->val != q->val) return false;
        else {
            queue<TreeNode*> que;
            que.push(p);
            que.push(q);
            while (!que.empty()) {
                TreeNode* a = que.front();
                que.pop();
                TreeNode* b = que.front();
                que.pop();
                if (!a && !b) continue;
                else if (!a || !b || a->val != b->val) return false;
                que.push(a->left);
                que.push(b->left);
                que.push(a->right);
                que.push(b->right);
            }
            return true;
        }
    }
};
// @lc code=end

