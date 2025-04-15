/*
 * @lc app=leetcode.cn id=429 lang=cpp
 * 树的层次遍历,BFS
 * [429] N 叉树的层序遍历
 */

//* 层序遍历（BFS，广度优先遍历），使用队列
//! 要求答案中只存储每一层的最后一个节点，则queue遍历时多加一个判断即可

// @lc code=start
#include <vector>
#include <queue>
using namespace std;
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
    vector<vector<int>> levelOrder(Node* root) {
        queue<Node*> que;
        if (root != nullptr) que.push(root);
        vector<vector<int>> result;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            //! 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
            for (int i = 0; i < size; i++) {
                Node* node = que.front();
                que.pop();
                vec.push_back(node->val);
                for (Node* it : node->children) {
                    que.push(it);
                }
            }
            result.push_back(vec);
        }
        return result;
    }
};
// @lc code=end

