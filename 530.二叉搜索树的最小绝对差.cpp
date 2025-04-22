/*
 * @lc app=leetcode.cn id=530 lang=cpp
 * 二叉搜索树
 * [530] 二叉搜索树的最小绝对差
 */

// @lc code=start
#include <vector>
#include <queue>
#include <stack>
#include <climits>
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
//* 先递归生成中序序列，再判断序列是否是递增的
class Solution {
private:
vector<int> vec;
void traversal(TreeNode* root) {
    if (root == nullptr) return;
    traversal(root->left);
    vec.push_back(root->val);                   //* 将二叉搜索树转换为有序数组
    traversal(root->right);
}
public:
    int getMinimumDifference(TreeNode* root) {
        vec.clear();
        traversal(root);
        if (vec.size() < 2) return 0;
        int result = INT_MAX;
        for (int i = 1; i < vec.size(); i++) {  //* 统计有序数组的最小差值
            result = min(result, vec[i] - vec[i-1]);
        }
        return result;
    }
};

//* 递归法
//* 递归过程中直接比较
class Solution {
public:
    int result = INT_MAX;
    TreeNode* pre = nullptr;
    void traversal(TreeNode* cur) {
        if (cur == nullptr) return;
        traversal(cur->left);           //* 左
        if (pre != nullptr){            //* 中
            result = min(result, cur->val - pre->val);
        }
        pre = cur;                      //* 记录前一个
        traversal(cur->right);          //* 右
    }
    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;
    }
};

//* 迭代法
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int min = INT_MAX;
        stack<TreeNode*> sta;
        sta.push(root);
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        while (!sta.empty()) {
            cur = sta.top();
            sta.pop();
            if (cur != nullptr) {
                if (cur->right) sta.push(cur->right);

                sta.push(cur);
                sta.push(nullptr);

                if (cur->left) sta.push(cur->left);
            }
            else {
                cur = sta.top();
                sta.pop();
                if (pre == nullptr) {
                    pre = cur;
                    continue;
                }
                else {
                    int x = cur->val - pre->val;
                    min = min < x ? min : x;
                    pre = cur;
                }
            }
        }
        return min;
    }
};
// @lc code=end

