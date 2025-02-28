/*
 * @lc app=leetcode.cn id=144 lang=cpp
 * 二叉树
 * [144] 二叉树的前序遍历
 */

// @lc code=start
#include <vector>
#include <stack>
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
    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == nullptr) return;
        vec.push_back(cur->val);
        traversal(cur->left, vec);
        traversal(cur->right, vec);
    }

    // 递归法
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;
        result.push_back(root->val);
        traversal(root->left, result);
        traversal(root->right, result);
        return result;
    }

    // 迭代法
    vector<int> preorderTraversalV2(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> result;
        if (root == nullptr) return result;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();                       // 中
            st.pop();
            result.push_back(node->val);
            if (node->right) st.push(node->right);           // 右（空节点不入栈）
            if (node->left) st.push(node->left);             // 左（空节点不入栈）
        }
        return result;
    }

    // 统一迭代法，null标记版
    vector<int> preorderTraversalV3(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != nullptr) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != nullptr) {
                st.pop(); // 将该节点弹出，避免重复操作，下面再将右左中节点添加到栈中
                if (node->right) st.push(node->right);  // 添加右节点（空节点不入栈）

                if (node->left) st.push(node->left);    // 添加左节点（空节点不入栈）

                st.push(node);                          // 添加中节点
                st.push(nullptr);                       // 中节点访问过，但是还没有处理，加入空节点做为标记。
            } 
            else { // 只有遇到空节点的时候，才将下一个节点放进结果集
                st.pop();           // 将空节点弹出
                node = st.top();    // 重新取出栈中元素
                st.pop();
                result.push_back(node->val); // 加入到结果集
            }
        }
        return result;
    }

    // 统一迭代法，bool判断版
    vector<int> preorderTraversalV4(TreeNode* root) {
        vector<int> result;
        stack<pair<TreeNode*, bool>> st;
        if (root != nullptr)
            st.push(make_pair(root, false)); // 多加一个参数，false 为默认值，含义见下文注释

        while (!st.empty()) {
            auto node = st.top().first;
            auto visited = st.top().second; //多加一个 visited 参数，使“迭代统一写法”成为一件简单的事
            st.pop();

            if (visited) { // visited 为 True，表示该节点和两个儿子位次之前已经安排过了，现在可以收割节点了
                result.push_back(node->val);
                continue;
            }

            // visited 当前为 false, 表示初次访问本节点，此次访问的目的是“把自己和两个儿子在栈中安排好位次”。
            
            // 前序遍历是'中左右'，右儿子最先入栈，最后出栈。
            // 右儿子
            if (node->right)
                st.push(make_pair(node->right, false));

            // 左儿子
            if (node->left)
                st.push(make_pair(node->left, false)); 

            // 自己
            // 同时，设置 visited 为 true，表示下次再访问本节点时，允许收割。
            st.push(make_pair(node, true));
        }
        
        return result;
    }
};
// @lc code=end

