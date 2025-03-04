/*
 * @lc app=leetcode.cn id=590 lang=cpp
 *
 * [590] N 叉树的后序遍历
 */

// @lc code=start
#include <vector>
#include <stack>
#include <algorithm>
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
    vector<int> postorder(Node* root) {
        vector<int> result;
        if (root == nullptr) return result;
        stack<Node*> sta;
        sta.push(root);
        while (!sta.empty()) {
            Node* cur = sta.top();
            sta.pop();
            result.push_back(cur->val);
            auto it = cur->children.begin();
            for (; it != cur->children.end(); it++) {
                sta.push(*it);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
// @lc code=end

