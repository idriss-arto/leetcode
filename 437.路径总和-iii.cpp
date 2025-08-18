/*
 * @lc app=leetcode.cn id=437 lang=cpp
 * 二叉树，前缀和
 ! [437] 路径总和 III
 */

/*
 * 思路一：
 * 递归遍历每一个节点。
 * 计算以该节点为路径首节点的情况下，满足条件的路径数。
 * 最后求和。
 * 时间复杂度O(N^2)，空间复杂度O(N)
 * 
 * 思路二：
 * 前缀和
 * 时间复杂度O(N)，空间复杂度O(N)
*/

// @lc code=start
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

/*
 * 官方题解一：递归搜索
 * 访问每一个节点 node，检测以 node 为起始节点且向下延深的路径中满足要求的有多少种。
 * 递归遍历每一个节点的所有可能的路径，然后将这些满足要求的路径数目加起来即为返回结果。
 * 时间复杂度O(N^2)，空间复杂度O(N)
*/
class Solution {
public:
    //* rootSum计算的是以 root 为起始节点且向下延深的路径，即 root 一定在路径中
    int rootSum(TreeNode* root, int targetSum) {
        if (!root) {
            return 0;
        }

        int ret = 0;
        if (root->val == targetSum) {
            ret++;
        } 

        ret += rootSum(root->left, targetSum - root->val);
        ret += rootSum(root->right, targetSum - root->val);
        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return 0;
        }
        
        int ret = rootSum(root, targetSum);
        
        //! 这里必须对左右孩子都调用pathSum函数，也就是都尝试当做路径第一个节点
        ret += pathSum(root->left, targetSum);
        ret += pathSum(root->right, targetSum);
        return ret;
    }
};

/*
 * 官方题解二：前缀和
 * 假设根节点为 root，我们当前刚好访问节点 node，
 * 则此时从根节点 root 到节点 node 的路径（无重复节点）刚好为 root→p1→p2→…→pk→node，
 * 此时我们可以已经保存了节点 p1,p2,p3,…,pk的前缀和，并且计算出了节点 node 的前缀和。
 * 假设当前从根节点 root 到节点 node 的前缀和为 curr，
 * 则此时我们在已保存的前缀和查找是否存在前缀和刚好等于 curr−targetSum。
 * 假设从根节点 root 到节点 node 的路径中存在节点 pi 满足：
 * 从根节点 root 到节点 pi 的前缀和为 curr−targetSum，
 * 则节点 p(i+1)到 node 的路径上所有节点的和一定为 targetSum。
 * 
 ! 注意过程中需要回溯
 * 
 * 时间复杂度O(N)，空间复杂度O(N)
*/
class Solution {
public:
    //* prefix 记录出现过的前缀和
    unordered_map<long long, int> prefix;

    //* curr 记录从根节点 root 到当前节点 node 的前缀和
    int dfs(TreeNode *node, long long curr, int targetSum) {
        if (!node) {
            return 0;
        }

        int ret = 0;
        curr += node->val;

        //* 在已保存的前缀和查找是否存在前缀和刚好等于 curr−targetSum
        if (prefix.count(curr - targetSum)) {
            ret = prefix[curr - targetSum];
        }

        //* 必须在查找完之前的前缀和后才能插入当前前缀和
        //* 否则可能导致错误，如target为6，树只有一个节点3
        prefix[curr]++;

        ret += dfs(node->left, curr, targetSum);
        ret += dfs(node->right, curr, targetSum);

        //! 关键一步，回溯
        prefix[curr]--;

        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        //! 对于空路径我们也需要保存预先处理一下，
        //* 此时因为空路径不经过任何节点，因此它的前缀和为 0。
        prefix[0] = 1;
        return dfs(root, 0, targetSum);
    }
};
// @lc code=end

