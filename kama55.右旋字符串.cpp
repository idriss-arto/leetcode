/*
* 字符串
*/ 
#include<iostream>
#include<algorithm>
using namespace std;
int main() {
    int n;
    string s;
    cin >> n;
    cin >> s;
    int len = s.size();                         //获取长度
    reverse(s.begin(), s.end());                // 整体反转
    reverse(s.begin(), s.begin() + n);          // 先反转前一段，长度n
    reverse(s.begin() + n, s.end());            // 再反转后一段
    cout << s << endl;
    return 0;
}