/*
 * @lc app=leetcode.cn id=295 lang=cpp
 * 堆（优先队列）
 ! [295] 数据流的中位数
 */

// @lc code=start
#include <set>
#include <queue>
#include <vector>
using namespace std;

//* 我的解法一，直接multiset排序
//* 最后一个用例超时
class MedianFinder {
private:
    multiset<double> uset;
    int cnt = 0;
    
public:
    MedianFinder() {}
    
    void addNum(int num) {
        cnt++;
        uset.insert(num);
    }
    
    double findMedian() {
        if (cnt % 2 == 1) {
            return *(next(uset.begin(), cnt/2));
        }
        else return (*(next(uset.begin(), cnt/2 - 1)) + *(next(uset.begin(), cnt/2))) / 2.0;
    }
};

/*
 * 官方题解，也是用multiset
 * 但不再维护总大小cnt，而是根据插入值的大小挪动left和right两个指针
 * 1.
 * 初始有序集合为空时，我们直接让左右指针指向 num 所在的位置。
 * 
 * 2.
 * 插入前有序集合元素为奇数时，left 和 right 同时指向中位数。
 * 此时如果插入的 num 小于等于中位数，那么只要让 left 左移，否则让 right 右移即可。
 * 
 * 3.
 * 插入前有序集合元素为偶数时，left 和 right 分别指向构成中位数的两个数。此时，
 * a. 
 * 当插入的 num 成为新的唯一的中位数，那么我们让 left 右移，right 左移，这样它们即可指向 num 所在的位置；
 * b.
 * 当插入的 num 大于等于 right，那么我们让 left 右移即可；
 * c.
 * 当插入的 num 小于 right 指向的值，那么我们让 right 左移，
 * 注意到如果 num 恰等于 left 指向的值，那么 num 将被插入到 left 右侧，使得 left 和 right 间距增大，
 * 所以我们还需要额外让 left 指向移动后的 right。
*/
class MedianFinder {
private:
    multiset<int> nums;
    multiset<int>::iterator left, right;

public:
    MedianFinder() : left(nums.end()), right(nums.end()) {}

    void addNum(int num) {
        const size_t n = nums.size();

        nums.insert(num);
        if (!n) {
            left = right = nums.begin();
        } else if (n & 1) {         //* 判断n是否为奇数
            if (num < *left) {
                left--;
            } else {
                right++;
            }
        } else {
            if (num > *left && num < *right) {
                left++;
                right--;
            } else if (num >= *right) {
                left++;
            } else {
                right--;
                left = right;
            }
        }
    }

    double findMedian() {
        return (*left + *right) / 2.0;
    }
};

/* 
 * 我的解法二，
 * 思路：
 * 将输入的数字按大小分到左边部分或者右边部分，
 * 左边部分是一个大顶堆，右边部分是一个小顶堆。
 * 插入一个数字后，平衡两个堆，再更新中位数。
 * 
 * 因为是手动实现堆，所以很麻烦
*/
class MedianFinder {
private:
    vector<int> leftMaxHeap;
    vector<int> rightMinHeap;
    double medianNum;

    void adjustUpLeft (int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;

        if (leftMaxHeap[parent] < leftMaxHeap[index]) {
            swap(leftMaxHeap[parent], leftMaxHeap[index]);
            adjustUpLeft(parent);
        }
    }

    void adjustDownLeft (int index) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int max = index;

        if (left < leftMaxHeap.size() && leftMaxHeap[left] > leftMaxHeap[max]) {
            max = left;
        }
        if (right < leftMaxHeap.size() && leftMaxHeap[right] > leftMaxHeap[max]) {
            max = right;
        }

        if (max != index) {
            swap(leftMaxHeap[max], leftMaxHeap[index]);
            adjustDownLeft(max);
        }
    }

    void addNodeLeft (int num) {
        leftMaxHeap.push_back(num);
        adjustUpLeft(leftMaxHeap.size() - 1);
        if (leftMaxHeap.size() - rightMinHeap.size() > 1) {
            int tmp = leftMaxHeap[0];

            swap(leftMaxHeap[0], leftMaxHeap[leftMaxHeap.size() - 1]);
            leftMaxHeap.pop_back();
            adjustDownLeft(0);

            //* 调整完左边再加入右边，否则容易出错
            addNodeRight(tmp);
        }
    }

    void adjustUpRight (int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;

        if (rightMinHeap[parent] > rightMinHeap[index]) {
            swap(rightMinHeap[parent], rightMinHeap[index]);
            adjustUpRight(parent);
        }
    }

    void adjustDownRight (int index) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int min = index;

        if (left < rightMinHeap.size() && rightMinHeap[left] < rightMinHeap[min]) {
            min = left;
        }
        if (right < rightMinHeap.size() && rightMinHeap[right] < rightMinHeap[min]) {
            min = right;
        }

        if (min != index) {
            swap(rightMinHeap[min], rightMinHeap[index]);
            adjustDownRight(min);
        }
    }

    void addNodeRight (int num) {
        rightMinHeap.push_back(num);
        adjustUpRight(rightMinHeap.size() - 1);
        if (rightMinHeap.size() - leftMaxHeap.size() > 1) {
            int tmp = rightMinHeap[0];

            swap(rightMinHeap[0], rightMinHeap[rightMinHeap.size() - 1]);
            rightMinHeap.pop_back();
            adjustDownRight(0);

            //* 调整完右边再加入左边，否则容易出错
            addNodeLeft(tmp);       
        }
    }

public:
    MedianFinder() {}
    
    void addNum(int num) {
        if (leftMaxHeap.size() == 0) {
            addNodeLeft(num);
            medianNum = leftMaxHeap[0];
            return;
        }
        if (rightMinHeap.size() == 0) {
            addNodeRight(num);
            if (leftMaxHeap[0] > rightMinHeap[0]) {
                swap(leftMaxHeap[0], rightMinHeap[0]);
            }
            medianNum = (leftMaxHeap[0] + rightMinHeap[0]) / 2.0;
            return;
        }
       
        if (num < medianNum) {
            addNodeLeft(num);
        }
        else {
            addNodeRight(num);
        }

        if ((leftMaxHeap.size() + rightMinHeap.size()) % 2 == 1) {
            if (leftMaxHeap.size() > rightMinHeap.size()) {
                medianNum = leftMaxHeap[0];
            }
            else medianNum = rightMinHeap[0];
        }
        else {
            medianNum = (leftMaxHeap[0] + rightMinHeap[0]) / 2.0;
        }
    }
    
    double findMedian() {
        return medianNum;
    }
};

//* 题解解法，用优先队列实现堆
class MedianFinder {
private:
    //* 左堆：最大堆，存储较小的一半元素
    priority_queue<int> leftMaxHeap;
    //* 右堆：最小堆，存储较大的一半元素
    priority_queue<int, vector<int>, greater<int>> rightMinHeap;
    double medianNum;   //* 存储中位数，支持浮点型

public:
    MedianFinder() : medianNum(0.0) {}
    
    void addNum(int num) {
        //* 优先插入左堆（最大堆），保证左堆元素 ≤ 右堆元素
        if (leftMaxHeap.empty() || num <= leftMaxHeap.top()) {
            leftMaxHeap.push(num);
        } else {
            rightMinHeap.push(num);
        }

        //* 平衡两堆大小，确保左堆大小与右堆大小相差不超过 1
        if (leftMaxHeap.size() > rightMinHeap.size() + 1) {
            //* 左堆过大，移动堆顶到右堆
            rightMinHeap.push(leftMaxHeap.top());
            leftMaxHeap.pop();
        } else if (rightMinHeap.size() > leftMaxHeap.size()) {
            //* 右堆过大，移动堆顶到左堆
            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();
        }

        //* 计算中位数
        int totalSize = leftMaxHeap.size() + rightMinHeap.size();
        if (totalSize % 2 == 1) {
            //* 奇数个元素，中位数为较大堆的堆顶
            medianNum = (leftMaxHeap.size() > rightMinHeap.size()) ? 
                        static_cast<double>(leftMaxHeap.top()) : 
                        static_cast<double>(rightMinHeap.top());
        } else {
            //* 偶数个元素，中位数为两堆堆顶的平均值
            medianNum = (leftMaxHeap.top() + rightMinHeap.top()) / 2.0;
        }
    }
    
    double findMedian() {
        return medianNum;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
// @lc code=end

