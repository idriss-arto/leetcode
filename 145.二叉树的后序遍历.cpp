/*
 * @lc app=leetcode.cn id=144 lang=cpp
 * 二叉树
 * [144] 二叉树的前序遍历
 */

// @lc code=start
#include <vector>
#include <stack>
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
    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == nullptr) return;
        traversal(cur->left, vec);
        traversal(cur->right, vec);
        vec.push_back(cur->val);
    }

    // 递归法
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;
        traversal(root->left, result);
        traversal(root->right, result);
        result.push_back(root->val);
        return result;
    }

    // 迭代法
    vector<int> postorderTraversalV2(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> result;
        if (root == nullptr) return result;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            result.push_back(node->val);
            if (node->left) st.push(node->left); // 相对于前序遍历，这更改一下入栈顺序 （空节点不入栈）
            if (node->right) st.push(node->right); // 空节点不入栈
        }
        reverse(result.begin(), result.end()); // 将结果反转之后就是左右中的顺序了
        return result;
    }

    // 统一迭代法，null标记版
    vector<int> postorderTraversalV3(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != nullptr) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != nullptr) {
                st.pop(); // 将该节点弹出，避免重复操作，下面再将中右左节点添加到栈中

                st.push(node);                          // 添加中节点
                st.push(nullptr);                       // 中节点访问过，但是还没有处理，加入空节点做为标记。

                if (node->right) st.push(node->right);  // 添加右节点（空节点不入栈）

                if (node->left) st.push(node->left);    // 添加左节点（空节点不入栈）
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
    vector<int> postorderTraversalV4(TreeNode* root) {
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
            
            // 后序遍历是'左右中'，自己最先入栈，最后出栈。
            // 同时，设置 visited 为 true，表示下次再访问本节点时，允许收割。
            st.push(make_pair(node, true));

            // 右儿子
            if (node->right)
                st.push(make_pair(node->right, false));

            // 左儿子
            if (node->left)
                st.push(make_pair(node->left, false)); 
        }
        
        return result;
    }
};
// @lc code=end

