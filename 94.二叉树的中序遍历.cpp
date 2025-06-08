/*
 * @lc app=leetcode.cn id=94 lang=cpp
 * 二叉树
 * [94] 二叉树的中序遍历
 */

/*
 * 中序为根左右
 * 有以下几种方案，
 * 递归法
 * 迭代法
 * 统一迭代法，null标记版
 * 统一迭代法，bool判断版
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

//* 递归法
class Solution {
public:
    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == nullptr) return;
        traversal(cur->left, vec);
        vec.push_back(cur->val);
        traversal(cur->right, vec);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;
        traversal(root->left, result);
        result.push_back(root->val);
        traversal(root->right, result);
        return result;
    }
};

//* 迭代法
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur != nullptr || !st.empty()) {
            if (cur != nullptr) {   //* 指针来访问节点，访问到最底层
                st.push(cur);       //* 将访问的节点放进栈
                cur = cur->left;                //* 左
            } 
            else {
                cur = st.top();     //* 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
                st.pop();
                result.push_back(cur->val);     //* 中
                cur = cur->right;               //* 右
            }
        }
        return result;
    }
};

//* 统一迭代法，null标记版
class Solution {
public:
    vector<int> inorderTraversalV3(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        if (root != nullptr) st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            if (node != nullptr) {
                st.pop();                               //* 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
                if (node->right) st.push(node->right);  //* 添加右节点（空节点不入栈）

                st.push(node);                          //* 添加中节点
                st.push(nullptr);                       //* 中节点访问过，但是还没有处理，加入空节点做为标记。

                if (node->left) st.push(node->left);    //* 添加左节点（空节点不入栈）
            }
            else {                  //! 只有遇到空节点的时候，才将下一个节点放进结果集
                st.pop();           //* 将空节点弹出
                node = st.top();    //* 重新取出栈中元素
                st.pop();
                result.push_back(node->val);    //* 加入到结果集
            }
        }
        return result;
    }
};

//* 统一迭代法，bool判断版
class Solution {
    vector<int> inorderTraversalV4(TreeNode* root) {
        vector<int> result;
        stack<pair<TreeNode*, bool>> st;
        if (root != nullptr)
            st.push(make_pair(root, false));    //* 多加一个参数，false 为默认值，含义见下文注释

        while (!st.empty()) {
            auto node = st.top().first;
            auto visited = st.top().second;     //* 多加一个 visited 参数，使“迭代统一写法”成为一件简单的事
            st.pop();

            if (visited) {          //! visited 为 True，表示该节点和两个儿子位次之前已经安排过了，现在可以收割节点了
                result.push_back(node->val);
                continue;
            }

            //! visited 当前为 false, 表示初次访问本节点，此次访问的目的是“把自己和两个儿子在栈中安排好位次”。
            
            //* 中序遍历是'左中右'，右儿子最先入栈，最后出栈。
            //* 右儿子
            if (node->right)
                st.push(make_pair(node->right, false));

            //* 自己
            //* 同时，设置 visited 为 true，表示下次再访问本节点时，允许收割。
            st.push(make_pair(node, true));

            //* 左儿子
            if (node->left)
                st.push(make_pair(node->left, false)); 
        }
        
        return result;
    }
};
// @lc code=end

