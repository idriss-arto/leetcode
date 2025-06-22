/*
 * @lc app=leetcode.cn id=215 lang=cpp
 * 变种快排，小顶堆（优先队列）
 ! [215] 数组中的第K个最大元素
 */

// @lc code=start
#include <vector>
#include <functional>
#include <set>
#include <queue>
using namespace std;

//* multiset排序
//* 能通过，但耗时长
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int, greater<int>> uset(nums.begin(), nums.end());

        int i = 1;
        for (auto& p : uset) {
            if (i++ == k) return p;
        }
        //* 或者 auto it = next(uset.begin(), k-1);

        return -1;
    }
};

//* 变种快排一，升序找第 n-k 小
//* 时间复杂度O(N)，空间复杂度O(logN)
class Solution {
public:
    int quickselect(vector<int> &nums, int left, int right, int k) {
        if (left == right)
            return nums[k];

        int privot = nums[(left + right) >> 1];
        
        //! 注意这里i和j的初始化
        int i = left - 1;
        int j = right + 1;
        while (i < j) {
            //! 注意这里是do-while循环
            do i++; while (nums[i] < privot);
            do j--; while (nums[j] > privot);
            if (i < j)
                swap(nums[i], nums[j]);
        }

        /*
         * do-while循环等价于以下代码
        int i = left;
        int j = right;
        while (i < j) {
            while (nums[i] < privot) {
                i++;
            } 
            while (nums[j] > privot) {
                j--;
            }
            if (i < j) {
                if (nums[i] == nums[j]) {
                    i++;
                    j--;
                }
                else swap(nums[i], nums[j]);
                
            }
                
        }
        */

        if (k <= j) {
            return quickselect(nums, left, j, k);
        }
        else {
            return quickselect(nums, j + 1, right, k);
        }
    }

    int findKthLargest(vector<int> &nums, int k) {
        int n = nums.size();
        return quickselect(nums, 0, n - 1, n - k);
    }
};

//* 变种快排二，降序找第 k-1 大
//* 时间复杂度O(N)，空间复杂度O(logN)
class Solution {
public:
    int qsort(vector<int>& nums, int left, int right, int k) {
        if (left == right) {
            return nums[k];
        }
        //! 注意这里i和j的初始化
        int i = left - 1;
        int j = right + 1;
        int privot = nums[(left + right) >> 1];
        while (i < j) {
            //! 注意这里是do-while循环
            do i++; while (nums[i] > privot);
            do j--; while (nums[j] < privot);
            if (i < j) {
                swap(nums[i], nums[j]);
            }
        }
        if (j >= k) return qsort(nums, left, j, k);
        else return qsort(nums, j+1, right, k);
    }

    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return qsort(nums, 0, n-1, k-1);
    }
};

//* 大顶堆+（k-1）次删除
//* 时间复杂度O(N+K*logN)，空间复杂度O(logN)
class Solution {
public:
    //* 节点向下调整的函数
    void adjustDown(vector<int>& heap, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && heap[l] > heap[largest]) {
            largest = l;
        } 
        if (r < heapSize && heap[r] > heap[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(heap[i], heap[largest]);
            adjustDown(heap, largest, heapSize);
        }
    }

    //* 建堆函数，从第一个非叶子节点向下调整
    void buildMaxHeap(vector<int>& heap, int heapSize) {
        for (int i = heapSize / 2 - 1; i >= 0; --i) {
            adjustDown(heap, i, heapSize);
        } 
    }

    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
            swap(nums[0], nums[i]);
            --heapSize;
            adjustDown(nums, 0, heapSize);
        }
        return nums[0];
    }
};

//* 大小为k的小顶堆
//* 时间复杂度O(K + (N-K)logK)，空间复杂度O(logK)
class Solution {
public:
    //* 节点向下调整的函数
    void adjustDown(vector<int>& heap, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, minIndex = i;
        if (l < heapSize && heap[l] < heap[minIndex]) {
            minIndex = l;
        } 
        if (r < heapSize && heap[r] < heap[minIndex]) {
            minIndex = r;
        }
        if (minIndex != i) {
            swap(heap[i], heap[minIndex]);
            adjustDown(heap, minIndex, heapSize);
        }
    }

    //* 建堆函数，从第一个非叶子节点向下调整
    void buildMinHeap(vector<int>& heap, int heapSize) {
        for (int i = heapSize / 2 - 1; i >= 0; --i) {
            adjustDown(heap, i, heapSize);
        } 
    }

    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = k;
        buildMinHeap(nums, heapSize);
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] > nums[0]) {
                swap(nums[0], nums[i]);
                adjustDown(nums, 0, heapSize);
            }
        }
        return nums[0];
    }
};

//* 小顶堆（优先队列实现）
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> que;
        for (const int& num : nums) {
            que.push(num);
            if (que.size() > k) que.pop();
        }
        return que.top();
    }
};
// @lc code=end

