/*
 * @lc app=leetcode.cn id=108 lang=cpp
 *
 * [108] 将有序数组转换为二叉搜索树
 */

// @lc code=start
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <unordered_map>
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
    //* 递归法
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if (right < left) return nullptr;
        int middle = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[middle]);
        root->left = traversal(nums, left, middle - 1);
        root->right = traversal(nums, middle + 1, right);
        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return traversal(nums, 0, nums.size() - 1);
    }

    //* 迭代法
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.size() == 0) return nullptr;

        TreeNode* root = new TreeNode(0);   //* 初始根节点
        queue<TreeNode*> nodeQue;           //* 放遍历的节点
        queue<int> leftQue;                 //* 保存左区间下标
        queue<int> rightQue;                //* 保存右区间下标
        nodeQue.push(root);                 //* 根节点入队列
        leftQue.push(0);                    //* 0为左区间下标初始位置
        rightQue.push(nums.size() - 1);     //* nums.size() - 1为右区间下标初始位置

        while (!nodeQue.empty()) {
            TreeNode* curNode = nodeQue.front();
            nodeQue.pop();
            int left = leftQue.front(); leftQue.pop();
            int right = rightQue.front(); rightQue.pop();
            int mid = left + ((right - left) / 2);

            curNode->val = nums[mid];       //* 将mid对应的元素给中间节点

            if (left <= mid - 1) {          //* 处理左区间
                curNode->left = new TreeNode(0);
                nodeQue.push(curNode->left);
                leftQue.push(left);
                rightQue.push(mid - 1);
            }

            if (right >= mid + 1) {         //* 处理右区间
                curNode->right = new TreeNode(0);
                nodeQue.push(curNode->right);
                leftQue.push(mid + 1);
                rightQue.push(right);
            }
        }
        return root;
    }
};
// @lc code=end

