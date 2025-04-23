/*
 * @lc app=leetcode.cn id=450 lang=cpp
 * 二叉搜索树
 * [450] 删除二叉搜索树中的节点
 */

/*
 * 我的递归法思路
 * 先在二叉搜索树中找到要删除的节点
 * 如果节点是叶子节点，删除节点就结束
 * 否则，找到左子树中最大值（即左子树中最右边的节点）来顶替自己
 * 没有左子树就找右子树中最小值（即右子树中最左边的节点）来顶替自己
 * 但是找到的顶替节点如果不是叶子节点的话也有自己的孩子，这时候处理很麻烦
 * 
 * 题解递归法一思路
 * 第一种情况：没找到删除的节点，遍历到空节点直接返回了
 * 找到删除的节点
 * 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
 * 第三种情况：删除节点的左孩子为空，右孩子不为空，删除节点，右孩子补位，返回右孩子为根节点
 * 第四种情况：删除节点的右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
 * 第五种情况：左右孩子节点都不为空，则将删除节点的左子树头结点（左孩子）放到删除节点的右子树的最左面节点的左孩子上，返回删除节点右孩子为新的根节点。
 * 
 * 题解递归法二思路
 * 可用于普通二叉树，先序递归
 * 先找到目标节点，然后找右子树中最左边节点，交换这两个节点的值
 * 然后进入右子树，进行同样的处理
 * 递归执行上述步骤数次，直到某次目标节点无右子树，则返回左子树即可
 * 
 * 题解迭代法思路
 * 和递归法一思路一致
 * 目标节点（删除节点）的右子树为空则返回左子树
 * 否则将目标节点（删除节点）的左子树放到目标节点的右子树的最左面节点的左孩子位置上
 * 并返回目标节点右孩子为新的根节点
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

//* 我的递归法，麻烦
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        if (root->val == key) {
            TreeNode* left = root->left;
            TreeNode* right = root->right;
            //* 被删除的节点是叶子结点
            if (left == nullptr && right == nullptr) return nullptr;
            else {      //* 有左子树或右子树
                if (left) {
                    //* 找到左子树中最大的值，即最右下方的值
                    TreeNode* parent = root;
                    TreeNode* cur = left;
                    while (cur && cur->right) {
                        parent = cur;
                        cur = cur->right;
                    }
                    if (parent == root) {
                        cur->right = right;
                        delete root;
                        return cur;
                    }
                    else {
                        parent->right = cur->left;
                        cur->left = left;
                        cur->right = right;
                        delete root;
                        return cur;
                    }   
                }
                else {
                    //* 找到右子树中最小的值，即最左下方的值
                    TreeNode* parent = root;
                    TreeNode* cur = right;
                    while (cur && cur->left) {
                        parent = cur;
                        cur = cur->left;
                    }
                    if (parent == root) {
                        cur->left = left;
                        delete root;
                        return cur;
                    }
                    else{
                        parent->left = cur->right;
                        cur->left = left;
                        cur->right = right;
                        delete root;
                        return cur;
                    }
                }
            }
        }
        else if (root->val > key) root->left = deleteNode(root->left, key);
        else root->right = deleteNode(root->right, key);
        return root;
    }
};

//* 题解递归法1
/*
 * 思路： 
 * 第一种情况：没找到删除的节点，遍历到空节点直接返回了
 * 找到删除的节点
 * 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
 * 第三种情况：删除节点的左孩子为空，右孩子不为空，删除节点，右孩子补位，返回右孩子为根节点
 * 第四种情况：删除节点的右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
 * 第五种情况：左右孩子节点都不为空，则将删除节点的左子树头结点（左孩子）放到删除节点的右子树的最左面节点的左孩子上，返回删除节点右孩子为新的根节点。
*/
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root; //* 第一种情况：没找到删除的节点，遍历到空节点直接返回了
        if (root->val == key) {
            //* 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
            if (root->left == nullptr && root->right == nullptr) {
                //! 内存释放
                delete root;
                return nullptr;
            }
            //* 第三种情况：其左孩子为空，右孩子不为空，删除节点，右孩子补位 ，返回右孩子为根节点
            else if (root->left == nullptr) {
                auto retNode = root->right;
                //! 内存释放
                delete root;
                return retNode;
            }
            //* 第四种情况：其右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
            else if (root->right == nullptr) {
                auto retNode = root->left;
                //! 内存释放
                delete root;
                return retNode;
            }
            //* 第五种情况：左右孩子节点都不为空，则将删除节点的左子树放到删除节点的右子树的最左面节点的左孩子的位置
            //* 并返回删除节点右孩子为新的根节点。
            else {
                TreeNode* cur = root->right; //* 找右子树最左面的节点
                while(cur->left != nullptr) {
                    cur = cur->left;
                }
                cur->left = root->left; //* 把要删除的节点（root）左子树放在cur的左孩子的位置
                TreeNode* tmp = root;   //* 把root节点保存一下，下面来删除
                root = root->right;     //* 返回旧root的右孩子作为新root
                delete tmp;             //* 释放节点内存（这里不写也可以，但C++最好手动释放一下吧）
                return root;
            }
        }
        if (root->val > key) root->left = deleteNode(root->left, key);
        if (root->val < key) root->right = deleteNode(root->right, key);
        return root;
    }
};

//* 题解递归法2
//* 交换值完成覆盖，可用于普通二叉树
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;
        if (root->val == key) {
            if (root->right == nullptr) {   //* 这里第二次操作目标值：最终删除的作用
                return root->left;
            }
            TreeNode *cur = root->right;
            while (cur->left) {
                cur = cur->left;
            }
            swap(root->val, cur->val);      //* 这里第一次操作目标值：交换目标值其右子树最左面节点。
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
};

//* 题解迭代法
//* 目标节点（删除节点）的右子树为空则返回左子树
//* 否则将目标节点（删除节点）的左子树放到目标节点的右子树的最左面节点的左孩子位置上
//* 并返回目标节点右孩子为新的根节点
class Solution {
public:
    TreeNode* deleteOneNode(TreeNode* target) {
        if (target == nullptr) return target;
        TreeNode* left = target->left;
        TreeNode* right = target->right;
        delete target;
        
        if (right == nullptr) return left;
        TreeNode* cur = right;
        while (cur->left) {
            cur = cur->left;
        }
        cur->left = left;
        return right;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;
        TreeNode* cur = root;
        TreeNode* pre = nullptr;        //* 记录cur的父节点，用来删除cur
        while (cur) {
            if (cur->val == key) break;
            pre = cur;
            if (cur->val > key) cur = cur->left;
            else cur = cur->right;
        }
        if (pre == nullptr) {           //* 如果搜索树只有头结点
            return deleteOneNode(cur);
        }
        //* pre 要知道是删左孩子还是右孩子
        if (pre->left && pre->left->val == key) {
            pre->left = deleteOneNode(cur);
        }
        if (pre->right && pre->right->val == key) {
            pre->right = deleteOneNode(cur);
        }
        return root;
    }
};
// @lc code=end

