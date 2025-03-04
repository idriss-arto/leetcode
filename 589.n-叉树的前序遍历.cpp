/*
 * @lc app=leetcode.cn id=589 lang=cpp
 *
 * [589] N 叉树的前序遍历
 */

// @lc code=start
#include <vector>
#include <stack>
using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> result;
        if (root == nullptr) return result;
        stack<Node*> sta;
        sta.push(root);
        while (!sta.empty()) {
            Node* cur = sta.top();
            sta.pop();
            result.push_back(cur->val);
            auto it = cur->children.rbegin();
            for (; it != cur->children.rend(); it++) {
                sta.push(*it);
            }
        }
        return result;
    }
};
// @lc code=end

