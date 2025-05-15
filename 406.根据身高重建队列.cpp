/*
 * @lc app=leetcode.cn id=406 lang=cpp
 * 贪心
 ! [406] 根据身高重建队列
 */

/*
 * 遇到两个维度权衡的时候，
 ! 一定要先确定一个维度，再确定另一个维度。
 * 如果两个维度一起考虑一定会顾此失彼。
*/

// @lc code=start
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

/*
 * 身高从低往高排，思路：
 ! 身高从低往高排之后，之前的人站哪没有影响，有影响的是之后比自己高的人。
 * 设人数为n，在进行排序后，它们的身高依次为h_0,h_1,...,h_i,...,h_n，
 * 且在目标队列里排在h_i之前且身高高于它的人数为k_i。
 * 假设我们在初始时建立一个包含 n 个位置的空队列，
 * 而我们每次将一个人放入队列中时，会将一个「空」位置变成「满」位置，
 * 那么当我们放入第 i 个人时，我们需要给他安排一个「空」位置，
 * 并且这个「空」位置前面恰好还有 k_i 个「空」位置，用来安排给后面身高更高的人。
 ! 也就是说，第 i 个人的位置，就是队列中从左往右数第 k_i +1 个「空」位置。
 *
 * 其实对于目标队列[h,k]序列，[5, 0]一定在[5, 1]前面，可以将[5, 1]看作[(5-0.01*1), 1]，将[5, 2]看作[(5-0.01*2), 1]
 ! 注意，按照以上转换思路，身高从低往高排时，对于身高相同的，应该让k大的放前面
 * 总结则是，先按h升序，再按k降序 
*/
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
        });
        int n = people.size();
        vector<vector<int>> ans(n);
        for (const vector<int>& person: people) {
            //* 自己放在第 k_i + 1 个空上
            int spaces = person[1] + 1;
            for (int i = 0; i < n; ++i) {
                if (ans[i].empty()) {
                    --spaces;
                    if (!spaces) {
                        ans[i] = person;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};

/*
 * 身高从大往小排，思路：
 ! 身高从大往小排之后，之后的人站哪没有影响，有影响的是之前比自己高的人。
 * 还是设人数为n，在进行排序后，它们的身高依次为h_0,h_1,...,h_i,...,h_n，
 * 且在目标队列里排在h_i之前且身高高于它的人数为k_i。
 * 无从得知应该给后面的人安排多少个「空」位置，因此就不能沿用方法一安排空的方式。
 * 
 * 但我们可以发现，后面的人既然不会对第 i 个人造成影响，我们可以采用「插空」的方法，
 * 依次给每一个人在当前的队列中选择一个插入的位置。也就是说，
 ! 当我们放入第 i 个人时，只需要将其插入队列中，使得他的前面恰好有 k_i 个人即可
 * 
 * 其实对于目标队列[h,k]序列，[5, 0]一定在[5, 1]前面，可以将[5, 1]看作[(5-0.01*1), 1]，将[5, 2]看作[(5-0.01*2), 1]
 ! 注意，按照以上转换思路，身高从大往小排时，对于身高相同的，应该让k小的放前面
 * 总结则是，先按h升序，再按k降序 
*/

//* 版本一
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort (people.begin(), people.end(), cmp);
        vector<vector<int>> que;
        for (int i = 0; i < people.size(); i++) {
            int position = people[i][1];
            que.insert(que.begin() + position, people[i]);
        }
        return que;
    }
};

//* 版本二，用list结构，插入效率更高
class Solution {
public:
    //* 身高从大到小排（身高相同k小的站前面）
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort (people.begin(), people.end(), cmp);
        list<vector<int>> que;                      //* list底层是链表实现，插入效率比vector高的多
        for (int i = 0; i < people.size(); i++) {
            int position = people[i][1];            //* 插入到下标为position的位置
            std::list<vector<int>>::iterator it = que.begin();
            while (position--) {                    //* 寻找插入位置
                it++;
            }
            que.insert(it, people[i]);
        }
        return vector<vector<int>>(que.begin(), que.end());
    }
};
// @lc code=end

