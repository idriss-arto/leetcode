/*
 * @lc app=leetcode.cn id=230 lang=cpp
 * 二叉树
 * [230] 二叉搜索树中第 K 小的元素
 */

/*
 * 思路一：生成一个数组储存二叉树中序遍历的结果
 * 思路二：直接中序遍历过程中找第k小的值
*/

// @lc code=start
#include <vector>
#include <stack>
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

//* 递归法，生成一个数组储存二叉树中序遍历的结果
class Solution {
public:
    vector<int> nums;

    void traversal(TreeNode* root) {
        if (!root) return;
        traversal(root->left);
        nums.push_back(root->val);
        traversal(root->right);
    }

    int kthSmallest(TreeNode* root, int k) {
        traversal(root);
        return nums[k-1];
    }
};

//* 迭代法，直接中序遍历过程中找第k小的值
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> sta;
        sta.push(root);

        while (!sta.empty()) {
            TreeNode* cur = sta.top();
            sta.pop();
            if (cur) {
                if (cur->right) sta.push(cur->right);
                sta.push(cur);
                sta.push(nullptr);
                if (cur->left) sta.push(cur->left);
            }
            else {
                cur = sta.top();
                sta.pop();
                k--;
                if (k == 0) {
                    return cur->val;
                }
            }
        }
        
        return 0;
    }
};

//* 进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化算法？
/*
 * 思路：
 * 记录下以每个结点为根结点的子树的结点数，并在查找第 k 小的值时，使用如下方法搜索：
 * 令 node 等于根结点，开始搜索。
 * 对当前结点 node 进行如下操作：
 * 如果 node 的左子树的结点数 left 小于 k−1，则第 k 小的元素一定在 node 的右子树中，令 node 等于其的右子结点，k 等于 k−left−1，并继续搜索；
 * 如果 node 的左子树的结点数 left 等于 k−1，则第 k 小的元素即为 node ，结束搜索并返回 node 即可；
 * 如果 node 的左子树的结点数 left 大于 k−1，则第 k 小的元素一定在 node 的左子树中，令 node 等于其左子结点，并继续搜索。
*/ 
class MyBst {
public:
    MyBst(TreeNode *root) {
        this->root = root;
        countNodeNum(root);
    }

    //* 返回二叉搜索树中第k小的元素
    int kthSmallest(int k) {
        TreeNode *node = root;
        while (node != nullptr) {
            int left = getNodeNum(node->left);
            if (left < k - 1) {
                node = node->right;
                k -= left + 1;
            } else if (left == k - 1) {
                break;
            } else {
                node = node->left;
            }
        }
        return node->val;
    }

private:
    TreeNode *root;
    unordered_map<TreeNode *, int> nodeNum;

    //* 统计以node为根结点的子树的结点数
    int countNodeNum(TreeNode * node) {
        if (node == nullptr) {
            return 0;
        }
        nodeNum[node] = 1 + countNodeNum(node->left) + countNodeNum(node->right);
        return nodeNum[node];
    }

    //* 获取以node为根结点的子树的结点数
    int getNodeNum(TreeNode * node) {
        if (node != nullptr && nodeNum.count(node)) {
            return nodeNum[node];
        }
        else {
            return 0;
        }
    }
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        MyBst bst(root);
        return bst.kthSmallest(k);
    }
};
// @lc code=end

