/*
 * @lc app=leetcode.cn id=654 lang=cpp
 * 二叉树
 * [654] 最大二叉树
 */

/*
 * 基本思路与105、106差不多，都是找到分割点然后分割数组
 * 重点看下两个优化思路
*/

 #include <vector>
 #include <queue>
 #include <climits>
 #include <stack>
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.empty()) return nullptr;
        if (nums.size() == 1) {
            TreeNode* node = new TreeNode(nums[0]);
            return node;
        }

        int index = 0;
        int max = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > max) {
                max = nums[i];
                index = i;
            }
        }

        TreeNode* node = new TreeNode(nums[index]);

        vector<int> left(nums.begin(), nums.begin() + index);
        vector<int> right(nums.begin() + index + 1, nums.end());
        
        node->left = constructMaximumBinaryTree(left);
        node->right = constructMaximumBinaryTree(right);

        return node;
    }
};

//* 优化思路：使用下标索引避免每次创建新vector
//* 时间复杂度 O(n*n)，空间复杂度 O(n)
class Solution {
private:
    //* 在左闭右开区间[left, right)，构造二叉树
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if (left >= right) return nullptr;

        //* 分割点下标：maxValueIndex
        int maxValueIndex = left;
        for (int i = left + 1; i < right; ++i) {
            if (nums[i] > nums[maxValueIndex]) maxValueIndex = i;
        }

        TreeNode* root = new TreeNode(nums[maxValueIndex]);

        //* 左闭右开：[left, maxValueIndex)
        root->left = traversal(nums, left, maxValueIndex);

        //* 左闭右开：[maxValueIndex + 1, right)
        root->right = traversal(nums, maxValueIndex + 1, right);

        return root;
    }
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return traversal(nums, 0, nums.size());
    }
};

/*
 * 优化思路：
 * 单调栈解法：时间复杂度 O(n)，空间复杂度 O(n)
 * 使用单调栈可以找到每个元素左侧和右侧的最近的比自身大的元素
 ! 其中较小的元素对应的节点是自身的父节点
 * 思路与排序解法类似
*/
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int n = nums.size();
        vector<int> stk;
        vector<int> left(n, -1), right(n, -1);
        vector<TreeNode*> tree(n);
        for (int i = 0; i < n; ++i) {
            tree[i] = new TreeNode(nums[i]);
            while (!stk.empty() && nums[i] > nums[stk.back()]) {    //* nums[i] 是 nums[stk.back()] 右侧第一个比它大的元素
                right[stk.back()] = i;
                stk.pop_back();
            }
            if (!stk.empty()) {                 //* nums[stk.back()] 是 nums[i] 左侧第一个比它大的元素
                left[i] = stk.back();
            }
            stk.push_back(i);
        }

        TreeNode* root = nullptr;
        for (int i = 0; i < n; ++i) {
            if (left[i] == -1 && right[i] == -1) {  //* nums[i] 是整个数组最大值
                root = tree[i];
            }
            else if (right[i] == -1 || (left[i] != -1 && nums[left[i]] < nums[right[i]])) {
                tree[left[i]]->right = tree[i];
            }
            else {
                tree[right[i]]->left = tree[i];
            }
        }
        return root;
    }
};
// @lc code=end

