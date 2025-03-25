/*
 * @lc app=leetcode.cn id=202 lang=cpp
 * 哈希，或者快慢指针
 * [202] 快乐数
 */

/*
 * 思路：
 * 如果不是快乐数，在无限循环中会出现重复的数
 * 用哈希记录现在的数，如果后面再次出现了，说明进入死循环了，退出就可以了
*/

// @lc code=start
#include<vector>
#include<math.h>
#include<unordered_set>
using namespace std;
//* 正统hash写法
class Solution {
public:
    int bitSquareSum(int n) {
        int sum = 0;
        while(n > 0)
        {
            int bit = n % 10;
            sum += bit * bit;
            n = n / 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set <int> cnt;
        while (1) {
            long sum = bitSquareSum(n);
            if (sum == 1) {
                return true;
            }
            if (cnt.find(sum) != cnt.end()) {
                return false;
            }
            else {
                cnt.insert(sum);
                n = sum;
            }
        }
    }
};

//* 快慢指针写法
class Solution2 {
public:
    int bitSquareSum(int n) {
        int sum = 0;
        while(n > 0)
        {
            int bit = n % 10;
            sum += bit * bit;
            n = n / 10;
        }
        return sum;
    }

    
    bool isHappy(int n) {
        int slow = n, fast = n;
        do{
            slow = bitSquareSum(slow);
            fast = bitSquareSum(fast);
            fast = bitSquareSum(fast);
        }while(slow != fast);
        
        return slow == 1;
    }
};
// @lc code=end

