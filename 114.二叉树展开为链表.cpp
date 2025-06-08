/*
 * @lc app=leetcode.cn id=114 lang=cpp
 * 二叉树
 * [114] 二叉树展开为链表
 */

/*
 * 思路一：用一个节点数组储存先序遍历的结果，然后用数组实现节点之间连接关系的改变
 * 思路二：类似验证二叉树的思路，前序遍历的过程中维护prev节点
 * 思路三：如果当前节点有左子树，将左子树插在当前节点和右孩子之间
*/

// @lc code=start
#include <vector>
#include <stack>
using namespace std;

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//* 思路一：
//* 最直接的思路，用一个节点数组储存先序遍历的结果，然后用数组实现节点之间连接关系的改变
//* 这里用的递归法，也可以用迭代法
class Solution {
public:
    void preorderTraversal(TreeNode* root, vector<TreeNode*> &l) {
        if (root != nullptr) {
            l.push_back(root);
            preorderTraversal(root->left, l);
            preorderTraversal(root->right, l);
        }
    }

    void flatten(TreeNode* root) {
        vector<TreeNode*> l;
        preorderTraversal(root, l);
        int n = l.size();
        for (int i = 1; i < n; i++) {
            TreeNode *prev = l[i-1], *curr = l[i];
            prev->left = nullptr;
            prev->right = curr;
        }
    }
};

//* 思路二：
//* 类似验证二叉树的思路，前序遍历的过程中维护prev节点
//* 这里用的迭代法，也可以用递归法
class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root) return;
        stack<TreeNode*> sta;
        sta.push(root);

        TreeNode* cur;
        TreeNode* prev = nullptr;
        while (!sta.empty()) {
            cur = sta.top();
            sta.pop();
            if (cur != nullptr) {
                if (cur->right) sta.push(cur->right);

                if (cur->left) sta.push(cur->left);

                sta.push(cur);
                sta.push(nullptr);
            }
            else {
                cur = sta.top();
                sta.pop();
                if (prev == nullptr) {
                    prev = cur;
                }
                else {
                    prev->left = nullptr;
                    prev->right = cur;
                    prev = cur;
                }
            }
        }
    }
};

//* 思路三，寻找前驱节点
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode *cur = root;
        while (cur != nullptr) {
            if (cur->left != nullptr) {
                //* 在cur左子树中找到最右边的节点，作为前驱节点
                auto next = cur->left;
                auto predecessor = next;
                while (predecessor->right != nullptr) {
                    predecessor = predecessor->right;
                }
                //* 将cur节点的右孩子赋给前驱节点的右孩子
                predecessor->right = cur->right;
                //* 然后将cur的左孩子赋给cur的右孩子
                cur->left = nullptr;
                //* 并将cur的左孩子设为空
                cur->right = next;
            }
            //* 对当前节点处理结束后，继续处理链表中的下一个节点
            cur = cur->right;
        }
    }
};
// @lc code=end

