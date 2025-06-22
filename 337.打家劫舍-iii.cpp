/*
 * @lc app=leetcode.cn id=337 lang=cpp
 * 动态规划（打家劫舍），树形dp
 ! [337] 打家劫舍 III
 */

// @lc code=start
#include <vector>
#include <queue>
#include <unordered_map>
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

//* 题解解法
class Solution {
public:
    //* 长度为2的数组，考虑当前节点为根节点的子树
    //* 下标0：不偷此节点时能获得的最大金额，
    //* 下标1：偷此节点时能获得的最大金额
    vector<int> robTree(TreeNode* cur) {
        if (cur == NULL) return vector<int>{0, 0};
        
        vector<int> left = robTree(cur->left);
        vector<int> right = robTree(cur->right);

        //* 偷cur，那么就不能偷左右节点。
        int val1 = cur->val + left[0] + right[0];
        //! 不偷cur，那么可以偷也可以不偷左右节点，则取较大的情况
        int val2 = max(left[0], left[1]) + max(right[0], right[1]);

        return {val2, val1};
    }

    int rob(TreeNode* root) {
        vector<int> result = robTree(root);
        return max(result[0], result[1]);
    }
};

//! 错误
//* 我的解法一
//* 思路：用一个value数组把整个树的节点存起来，包括空节点，
//* 让节点i的左孩子是2*i+1、右孩子是2*i+2。
//* 可以从value数组的尾部向头部遍历
//! vector初始化大小有问题，n个节点往一个方向走，vector需要有2^n-1的大小
class Solution {
public:
    void setNull(vector<int>& value, int i) {
        if (i >= 1000) return;
        value[i] = 0;
        setNull(value, i*2+1);
        setNull(value, i*2+2);
    }

    int rob(TreeNode* root) {
        int cnt = 0;
        //! 节点i的左孩子是2*i+1、右孩子是2*i+2的情况下，1000远远不够
        vector<int> value(1000, -1);
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            if (value[cnt] == 0) {
                cnt++;
                continue;
            }
            TreeNode* cur = que.front();
            que.pop();
            value[cnt] = cur->val;
            if (cur->left) que.push(cur->left);
            else setNull(value, cnt*2+1);
            if (cur->right) que.push(cur->right);
            else setNull(value, cnt*2+2);
            cnt++;
        }
        value.resize(cnt);

        vector<int> dp(cnt, 0);
        for (int i = cnt-1; i >= 0; i--){
            int left = i * 2 + 1, right = i * 2 + 2;
            int leftDP = 0, rightDP = 0; 
            int leftSub = 0, rightSub = 0;
            if (left < cnt) {
                leftDP = dp[left];
                if (left*2+1 < cnt) leftSub += dp[left*2+1];
                if (left*2+2 < cnt) leftSub += dp[left*2+2];
            }
            if (right < cnt) {
                rightDP = dp[right];
                if (right*2+1 < cnt) rightSub += dp[right*2+1];
                if (right*2+2 < cnt) rightSub += dp[right*2+2];
            }
            dp[i] = max(value[i]+leftSub+rightSub, leftDP+rightDP);
        }

        return dp[0];
    }
};

//! 错误
//* 我的解法二，递归法
//* 和题解解法很像，但多了很多重复计算。
//* 最后两个用例超时
class Solution {
public:
    int rob(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return root->val;
        //* 偷父节点
        int val1 = root->val;
        if (root->left) val1 += rob(root->left->left) + rob(root->left->right);     //* 跳过root->left，相当于不考虑左孩子了
        if (root->right) val1 += rob(root->right->left) + rob(root->right->right);  //* 跳过root->right，相当于不考虑右孩子了
        //* 不偷父节点
        int val2 = rob(root->left) + rob(root->right);  //* 考虑root的左右孩子
        return max(val1, val2);
    }
};

//* 我的解法三
//* 思路：解法二的基础上，用unordered_map存储中间状态
class Solution {
public:
    unordered_map<TreeNode*, int> umap;     //* 记录计算过的结果

    int rob(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return root->val;
        if (umap[root]) {                   //* 如果umap里已经有记录则直接返回
            return umap[root];
        }
        //* 偷父节点
        int val1 = root->val;
        if (root->left) val1 += rob(root->left->left) + rob(root->left->right);     //* 跳过root->left
        if (root->right) val1 += rob(root->right->left) + rob(root->right->right);  //* 跳过root->right
        //* 不偷父节点
        int val2 = rob(root->left) + rob(root->right);  //* 考虑root的左右孩子
        umap[root] = max(val1, val2);                   //* umap记录一下结果
        return umap[root];
    }
};
// @lc code=end

