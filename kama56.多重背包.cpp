//* 动态规划（多重背包）
//* 多重背包可以看成特殊的01背包，因为可以把个数为n的物品1看成n个重量、价值相等的物品
#include<vector>
#include<iostream>
using namespace std;
//* 实现方式一，把个数为n的物品1展开为n个重量、价值相等的物品
//! 会超时，因为vector底层扩容。可以计算好一共要扩容多少再用resize一次解决
int main() {
    int bagWeight,n;
    cin >> bagWeight >> n;
    vector<int> weight(n, 0); 
    vector<int> value(n, 0);
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) cin >> weight[i];
    for (int i = 0; i < n; i++) cin >> value[i];
    for (int i = 0; i < n; i++) cin >> nums[i];    
    
    for (int i = 0; i < n; i++) {
        while (nums[i] > 1) {                   //* 物品数量不是一的，都展开
            weight.push_back(weight[i]);
            value.push_back(value[i]);
            nums[i]--;
        }
    }
 
    vector<int> dp(bagWeight + 1, 0);
    for(int i = 0; i < weight.size(); i++) {    //* 遍历物品，注意此时的物品数量不是n
        for(int j = bagWeight; j >= weight[i]; j--) {           //* 遍历背包容量
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    cout << dp[bagWeight] << endl;
}

//* 另一种实现方式，就是把每种商品遍历的个数放在01背包里面再遍历一遍。
int main2() {
    int bagWeight,n;
    cin >> bagWeight >> n;
    vector<int> weight(n, 0);
    vector<int> value(n, 0);
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) cin >> weight[i];
    for (int i = 0; i < n; i++) cin >> value[i];
    for (int i = 0; i < n; i++) cin >> nums[i];

    vector<int> dp(bagWeight + 1, 0);

    for(int i = 0; i < n; i++) {                        //* 遍历物品
        for(int j = bagWeight; j >= weight[i]; j--) {   //* 遍历背包容量
            //* 以上为01背包，然后加一个遍历个数
            for (int k = 1; k <= nums[i] && (j - k * weight[i]) >= 0; k++) {    //* 遍历个数
                dp[j] = max(dp[j], dp[j - k * weight[i]] + k * value[i]);
            }
        }
    }

    cout << dp[bagWeight] << endl;
}