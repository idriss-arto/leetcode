/*
 * @lc app=leetcode.cn id=513 lang=cpp
 * 二叉树
 * [513] 找树左下角的值
 */

/*
 * 思路：
 * 题解递归法：用先序遍历+回溯找到深度最大的节点，同时有多个深度最大的节点时，因为遍历顺序以及最大深度判断式子，会选中最左边的
 * 我的递归法：判断当前节点左子树和右子树谁更深，要求的节点一定在更深的子树里。但会对中间的节点重复求深度
 * 迭代法：层序遍历，最简单
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
//* 题解的递归法，不会对一个节点重复求深度
class Solution {
public:
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
            traversal(root->left, depth + 1);       //* 隐藏着回溯
        }
        if (root->right) {
            traversal(root->right, depth + 1);      //* 隐藏着回溯
        }
        return;
    }
    int findBottomLeftValue(TreeNode* root) {
        traversal(root, 0);
        return result;
    }
};

//* 我的递归法
class Solution {
public:
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
};

//* 迭代法
class Solution {
public:
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

