/*
 * @lc app=leetcode.cn id=968 lang=cpp
 * 贪心，状态记录
 ! [968] 监控二叉树
 */

// @lc code=start
#include <stack>
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

/*
 * 思路：
 * 显然，此题应用后序遍历，也就是从下往上遍历，
 * 这是因为头结点放不放摄像头也就省下一个摄像头， 
 * 叶子节点放不放摄像头省下了的摄像头数量是指数阶别的。
 * 
 * 将每个节点状态分为以下三种：
 * 0：该节点无覆盖
 * 1：本节点设置摄像头
 * 2：本节点有覆盖
 * 
 * 每个节点状态优自己子节点状态推出，具体以下几种情况
 * 情况1：
 * 左右节点都为2：有覆盖
 * 这种情况应该返回0：无覆盖
 * 
 * 情况2：
 * 左右节点中至少有一个为0：无覆盖
 * 这种情况应该返回1：设置摄像头
 * 
 * 情况3：
 * 左右孩子至少有1个为1：设置摄像头
 * 这种情况应该返回2：有覆盖
 * 
 * 
 * 特殊情况：
 * 对于空节点，因为我们想让空节点的父节点也就是叶子节点不放摄像头，也不能是被覆盖的状态
 * 所以，空节点状态设为2：本节点有覆盖
 * 
 * 对于根节点，如果发现最后状态是0：该节点无覆盖，则放一个摄像头
*/
class Solution {
private:
    int result;
    int traversal(TreeNode* cur) {

        //* 特殊处理，空节点，当做该节点有覆盖
        if (cur == nullptr) return 2;

        int left = traversal(cur->left);
        int right = traversal(cur->right);

        //* 情况1，无覆盖
        //* 左右节点都有覆盖
        if (left == 2 && right == 2) return 0;

        //* 情况2，放摄像头
        //* left == 0 && right == 0 左右节点无覆盖
        //* left == 1 && right == 0 左节点有摄像头，右节点无覆盖
        //* left == 0 && right == 1 左节点有无覆盖，右节点摄像头
        //* left == 0 && right == 2 左节点无覆盖，右节点覆盖
        //* left == 2 && right == 0 左节点覆盖，右节点无覆盖
        if (left == 0 || right == 0) {
            result++;
            return 1;
        }

        //* 情况3，有覆盖
        //* left == 1 && right == 2 左节点有摄像头，右节点有覆盖
        //* left == 2 && right == 1 左节点有覆盖，右节点有摄像头
        //* left == 1 && right == 1 左右节点都有摄像头
        //* 其他情况前段代码均已覆盖
        if (left == 1 || right == 1) return 2;

        //* 以上代码我没有使用else，主要是为了把各个分支条件展现出来，这样代码有助于读者理解
        //* 这个 return -1 逻辑不会走到这里。
        return -1;
    }

public:
    int minCameraCover(TreeNode* root) {
        result = 0;
        //* 特殊处理
        if (traversal(root) == 0) { //* root 无覆盖
            result++;
        }
        return result;
    }
};
// @lc code=end

