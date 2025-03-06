/*
 * @lc app=leetcode.cn id=257 lang=cpp
 *
 * [257] 二叉树的所有路径
 */

// @lc code=start
#include <vector>
#include <stack>
#include <algorithm>
#include <math.h>
#include <string>
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<int> path;
        vector<string> result;
        stack<TreeNode*> sta;
        sta.emplace(root);
        while (!sta.empty()) {
            TreeNode* cur = sta.top();
            if (cur) {
                sta.pop();
                sta.push(cur);
                sta.push(nullptr);
                path.emplace_back(cur->val);
                if (cur->right) sta.emplace(cur->right);
                if (cur->left) sta.emplace(cur->left);
            }
            else {
                sta.pop();
                cur = sta.top();
                sta.pop();
                if (!cur->left && !cur->right) {
                    string s = "";
                    for (int i = 0; i < path.size(); i++) {
                        if (i != 0) s += "->";
                        s += to_string(path[i]);;
                    }
                    result.emplace_back(s);
                }
                path.pop_back();
            }
        }
        return result;
    }

    // 题解迭代法
    vector<string> binaryTreePaths(TreeNode* root) {
        stack<TreeNode*> treeSt;// 保存树的遍历节点
        stack<string> pathSt;   // 保存遍历路径的节点
        vector<string> result;  // 保存最终路径集合
        if (root == NULL) return result;
        treeSt.push(root);
        pathSt.push(to_string(root->val));
        while (!treeSt.empty()) {
            TreeNode* node = treeSt.top();
            treeSt.pop();                                       // 取出节点 中
            string path = pathSt.top();
            pathSt.pop();                                       // 取出该节点对应的路径
            if (node->left == NULL && node->right == NULL) {    // 遇到叶子节点
                result.push_back(path);
            }
            if (node->right) { // 右
                treeSt.push(node->right);
                pathSt.push(path + "->" + to_string(node->right->val));
            }
            if (node->left) { // 左
                treeSt.push(node->left);
                pathSt.push(path + "->" + to_string(node->left->val));
            }
        }
        return result;
    }

    // 题解递归法
    // 因为参数列表里path没有加引用，所以是值传递，间接起到回溯作用
    void traversal(TreeNode* cur, string path, vector<string>& result) {
        path += to_string(cur->val); // 中
        if (cur->left == NULL && cur->right == NULL) {
            result.push_back(path);
            return;
        }
        if (cur->left) traversal(cur->left, path + "->", result); // 左
        if (cur->right) traversal(cur->right, path + "->", result); // 右
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        string path;
        if (root == NULL) return result;
        traversal(root, path, result);
        return result;

    }
};
// @lc code=end

