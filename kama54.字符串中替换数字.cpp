/*
* 字符串，双指针
*/ 

/*
 * 思路：
 * 先遍历整个字符串求出数字个数，再resize字符串大小
 * 双指针，都从后往前遍历（避免非数字被覆盖）
*/

#include<iostream>
#include<string>
using namespace std;

string replaceNumber(string& s) {
    int n = s.size(), cnt = 0;
    for (char c : s) {
        if (c >= '0' && c <= '9') {
            cnt += 1;
        }
    }
    s.resize(n + cnt * 5);
    
    int pos = n - 1;
    int newPos = s.size() - 1;
    while (pos >= 0) {
        if (s[pos] < '0' || s[pos] > '9') {
            s[newPos--] = s[pos--];
        }
        else {
            s[newPos--] = 'r';
            s[newPos--] = 'e';
            s[newPos--] = 'b';
            s[newPos--] = 'm';
            s[newPos--] = 'u';
            s[newPos--] = 'n';
            pos--;
        }
    }

    return s;
}

int main() {
    string s;
    cin >> s;
    replaceNumber(s);
    cout << s;
    return 0;
}