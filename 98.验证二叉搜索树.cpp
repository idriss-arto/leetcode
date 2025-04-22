/*
 * @lc app=leetcode.cn id=98 lang=cpp
 * 二叉搜索树
 * [98] 验证二叉搜索树
 */

/*
 * 陷阱一
 * 不能单纯的比较左节点小于中间节点，右节点大于中间节点就完事了，而是左子树都小于中间节点，右子树都大于中间节点。
 * 陷阱二
 * 在一个有序序列求最值的时候，不要定义一个全局变量，然后遍历序列更新全局变量求最值。因为最值可能就是int 或者 longlong的最小值。
*/

/*
 * 思路：中序遍历，看数字是不是从小到大
*/

// @lc code=start
#include <vector>
#include <queue>
#include <stack>
#include <climits>
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
//* 递归法
//* 先递归生成中序序列，再判断序列是否是递增的
class Solution {
private:
    vector<int> vec;
    void traversal(TreeNode* root) {
        if (root == nullptr) return;
        traversal(root->left);
        vec.push_back(root->val);   //* 将二叉搜索树转换为有序数组
        traversal(root->right);
    }
public:
    bool isValidBST(TreeNode* root) {
        vec.clear();                //* 不加这句在leetcode上也可以过，但最好加上
        traversal(root);
        for (int i = 1; i < vec.size(); i++) {
            //* 注意要小于等于，搜索树里不能有相同元素
            if (vec[i] <= vec[i - 1]) return false;
        }
        return true;
    }
};

//* 递归法
//* 递归过程中直接比较
class Solution {
public:
    long long maxVal = LONG_MIN;    //* 因为后台测试数据中有int最小值
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;

        bool left = isValidBST(root->left);
        //* 中序遍历，验证遍历的元素是不是从小到大
        if (maxVal < root->val) maxVal = root->val;
        else return false;
        bool right = isValidBST(root->right);

        return left && right;
    }
};

//* 递归法第二种写法，避免节点值可以取到LONG_MIN
class Solution {
public:
    TreeNode* pre = nullptr;            //* 用来记录前一个节点
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        bool left = isValidBST(root->left);

        if (pre != nullptr && pre->val >= root->val) return false;
        pre = root;                     //* 记录前一个节点

        bool right = isValidBST(root->right);
        return left && right;
    }
};

//* 迭代法
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> sta;
        sta.push(root);
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        while (!sta.empty()) {
            cur = sta.top();
            sta.pop();
            //* 二叉搜索树的中序遍历是递增序列
            if (cur != nullptr) {
                if (cur->right) sta.push(cur->right);

                sta.push(cur);
                sta.push(nullptr);

                if (cur->left) sta.push(cur->left);
            }
            else {
                cur = sta.top();
                sta.pop();
                if (pre == nullptr) {
                    pre = cur;
                    continue;
                }
                else if (cur->val <= pre->val) return false;
                else {
                    pre = cur;
                }
            }
        }
        return true;
    }
};
// @lc code=end

