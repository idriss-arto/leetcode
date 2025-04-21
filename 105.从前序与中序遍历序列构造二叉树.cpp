/*
 * @lc app=leetcode.cn id=105 lang=cpp
 * 二叉树
 * [105] 从前序与中序遍历序列构造二叉树
 */

/*
 * 思路：递归
 * 第一步：如果数组大小为零的话，说明是空节点了。
 * 第二步：如果不为空，那么取前序数组第一个元素作为节点元素。
 * 第三步：找到前序数组第一个元素在中序数组的位置，作为切割点
 * 第四步：切割中序数组，切成中序左数组和中序右数组 （顺序别搞反了，一定是先切中序数组）
 * 第五步：去掉前序第一个元素后，切割前序数组，切成前序左数组和前序右数组
 * 第六步：递归处理左区间和右区间
 ! 注意确定切割的标准，是左闭右开，还有左开右闭，还是左闭右闭，这个就是不变量，要在递归中保持这个不变量。

 ! 这种题边界判断容易出问题，可以打日志判断对错
*/

// @lc code=start
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
private:
    TreeNode* traversal (vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return NULL;

        //* 前序遍历数组第一个元素，就是当前的中间节点
        int rootValue = preorder[0];
        TreeNode* root = new TreeNode(rootValue);

        //* 叶子节点
        if (preorder.size() == 1) return root;

        //* 找到中序遍历的切割点
        int delimiterIndex;
        for (delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex++) {
            if (inorder[delimiterIndex] == rootValue) break;
        }

        //* 切割中序数组
        //! 左闭右开区间：[0, delimiterIndex)
        vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
        //! [delimiterIndex + 1, end)
        vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());

        //* 也可以这么写
        /*
        auto index = inorder.find(inoreder.begin(), inorder.end(), rootValue);
        vector<int> leftInorder(inorder.begin(), index);
        vector<int> rightInorder(index + 1, inorder.end());
        */

        //! preorder 舍弃开头元素
        preorder.erase(preorder.begin());

        //* 切割前序数组
        //* 依然左闭右开，注意这里使用了左中序数组大小作为切割点
        //! [0, leftInorder.size)
        vector<int> leftPreorder(preorder.begin(), preorder.begin() + leftInorder.size());
        //! [leftInorder.size(), end)
        vector<int> rightPreorder(preorder.begin() + leftInorder.size(), preorder.end());

        root->left = traversal(leftPreorder, leftInorder);
        root->right = traversal(rightPreorder, rightInorder);

        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return traversal(preorder, inorder);
    }
};

//* 以上代码每层递归定义了新的vector（就是数组），既耗时又耗空间
//* 下标索引版本
class Solution {
private:
private:
    TreeNode* traversal (vector<int>& inorder, int inorderBegin, int inorderEnd, vector<int>& preorder, int preorderBegin, int preorderEnd) {
        if (preorderBegin == preorderEnd) return NULL;

        int rootValue = preorder[preorderBegin];    //* 注意用preorderBegin 不要用0
        TreeNode* root = new TreeNode(rootValue);

        if (preorderEnd - preorderBegin == 1) return root;

        int delimiterIndex;
        for (delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++) {
            if (inorder[delimiterIndex] == rootValue) break;
        }
        //* 切割中序数组
        //! 中序左区间，左闭右开[leftInorderBegin, leftInorderEnd)
        int leftInorderBegin = inorderBegin;
        int leftInorderEnd = delimiterIndex;
        //! 中序右区间，左闭右开[rightInorderBegin, rightInorderEnd)
        int rightInorderBegin = delimiterIndex + 1;
        int rightInorderEnd = inorderEnd;

        //* 切割前序数组
        //! 前序左区间，左闭右开[leftPreorderBegin, leftPreorderEnd)
        int leftPreorderBegin =  preorderBegin + 1;
        int leftPreorderEnd = preorderBegin + 1 + delimiterIndex - inorderBegin;    //* 终止位置是起始位置加上中序左区间的大小size
        //! 前序右区间, 左闭右开[rightPreorderBegin, rightPreorderEnd)
        int rightPreorderBegin = preorderBegin + 1 + (delimiterIndex - inorderBegin);
        int rightPreorderEnd = preorderEnd;

        root->left = traversal(inorder, leftInorderBegin, leftInorderEnd,  preorder, leftPreorderBegin, leftPreorderEnd);
        root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, preorder, rightPreorderBegin, rightPreorderEnd);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (inorder.size() == 0 || preorder.size() == 0) return NULL;

        //* 参数坚持左闭右开的原则
        return traversal(inorder, 0, inorder.size(), preorder, 0, preorder.size());
    }
};
// @lc code=end

