/*
 * @lc app=leetcode.cn id=538 lang=cpp
 * 二叉搜索树
 * [538] 把二叉搜索树转换为累加树
 */

/*
 * 思路：
 * 注意遍历顺序（右中左）即可
*/

// @lc code=start
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <unordered_map>
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

//* 递归法
class Solution {
public:
    int pre = 0;                    //* 记录前一个节点的数值
    void traversal(TreeNode* cur) { //* 右中左遍历
        if (cur == NULL) return;
        traversal(cur->right);
        cur->val += pre;
        pre = cur->val;
        traversal(cur->left);
    }

    TreeNode* convertBST(TreeNode* root) {
        pre = 0;
        traversal(root);
        return root;
    }
};

//* 迭代法
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        if (root == nullptr) return root;
        stack<TreeNode*> sta;
        int sum = 0;
        sta.push(root);
        TreeNode* cur = root;
        while (!sta.empty()) {
            cur = sta.top();
            sta.pop();
            //* 右，根，左。按此顺序，节点的值递减
            if (cur != nullptr) {
                if (cur->left) sta.push(cur->left);

                sta.push(cur);
                sta.push(nullptr);

                if (cur->right) sta.push(cur->right);
            }
            else {
                cur = sta.top();
                sta.pop();
                int val = cur->val;
                cur->val += sum;
                sum += val;
            }
        }
        return root;
    }
};
// @lc code=end

