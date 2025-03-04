/*
 * @lc app=leetcode.cn id=572 lang=cpp
 *
 * [572] 另一棵树的子树
 */

// @lc code=start
#include <vector>
#include <queue>
#include <climits>
#include <stack>
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
    // 深度优先搜索暴力匹配
    /*
        bool check(TreeNode *o, TreeNode *t) {
            if (!o && !t) {
                return true;
            }
            if ((o && !t) || (!o && t) || (o->val != t->val)) {
                return false;
            }
            return check(o->left, t->left) && check(o->right, t->right);
        }
    
        bool dfs(TreeNode *o, TreeNode *t) {
            if (!o) {
                return false;
            }
            return check(o, t) || dfs(o->left, t) || dfs(o->right, t);
        }
    
        bool isSubtree(TreeNode *s, TreeNode *t) {
            return dfs(s, t);
        }
    */

    // 用深度优先搜索的结果做串匹配
    vector <int> sOrder, tOrder;
    int maxElement, lNull, rNull;

    void getMaxElement(TreeNode *o) {
        if (!o) {
            return;
        }
        maxElement = max(maxElement, o->val);
        getMaxElement(o->left);
        getMaxElement(o->right);
    }

    void getDfsOrder(TreeNode *o, vector <int> &tar) {
        if (!o) {
            return;
        }
        stack<TreeNode*> sta;
        sta.emplace(o);
        while (!sta.empty()) {
            TreeNode* cur = sta.top();
            sta.pop();
            tar.emplace_back(cur->val);
            if (cur->left) sta.emplace(cur->left);
            else tar.emplace_back(lNull);
            if (cur->right) sta.emplace(cur->right);
            else tar.emplace_back(rNull);
        }
    }

    bool kmp() {
        int sLen = sOrder.size(), tLen = tOrder.size();
        vector <int> fail(tOrder.size(), -1);
        for (int i = 1, j = -1; i < tLen; ++i) {
            while (j != -1 && tOrder[i] != tOrder[j + 1]) {
                j = fail[j];
            }
            if (tOrder[i] == tOrder[j + 1]) {
                ++j;
            }
            fail[i] = j;
        }
        for (int i = 0, j = -1; i < sLen; ++i) {
            while (j != -1 && sOrder[i] != tOrder[j + 1]) {
                j = fail[j];
            }
            if (sOrder[i] == tOrder[j + 1]) {
                ++j;
            }
            if (j == tLen - 1) {
                return true;
            }
        }
        return false;
    }

    bool isSubtree(TreeNode* s, TreeNode* t) {
        maxElement = INT_MIN;
        getMaxElement(s);
        getMaxElement(t);
        lNull = maxElement + 1;
        rNull = maxElement + 2;

        getDfsOrder(s, sOrder);
        getDfsOrder(t, tOrder);

        return kmp();
    }
};
// @lc code=end

