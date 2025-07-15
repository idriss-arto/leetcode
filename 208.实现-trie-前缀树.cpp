/*
 * @lc app=leetcode.cn id=208 lang=cpp
 * 图论
 ! [208] 实现 Trie (前缀树)
 */

// @lc code=start
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
 * 官方题解解法：
 * Trie，又称前缀树或字典树，是一棵有根树，其每个节点包含以下字段：
 * 指向子节点的指针数组 children。对于本题而言，数组长度为 26，即小写英文字母的数量。
 * 此时 children[0] 对应小写字母 a，children[1] 对应小写字母 b，…，children[25] 对应小写字母 z。
 * 布尔字段 isEnd，表示该节点是否为字符串的结尾。
 * 
 * 
 * 插入字符串：
 * 从字典树的根开始，插入字符串。对于当前字符对应的子节点，有两种情况。
 * 1.
 * 子节点存在。沿着指针移动到子节点，继续处理下一个字符。
 * 2.
 * 子节点不存在。创建一个新的子节点，记录在 children 数组的对应位置上，然后沿着指针移动到子节点，继续搜索下一个字符。
 * 
 * 重复以上步骤，直到处理字符串的最后一个字符，然后将当前节点标记为字符串的结尾。
 * 
 * 
 * 查找前缀
 * 从字典树的根开始，查找前缀。对于当前字符对应的子节点，有两种情况：
 * 1.
 * 子节点存在。沿着指针移动到子节点，继续搜索下一个字符。
 * 2.
 * 子节点不存在。说明字典树中不包含该前缀，返回空指针。
 * 
 * 重复以上步骤，直到返回空指针或搜索完前缀的最后一个字符。
 * 若搜索到了前缀的末尾，就说明字典树中存在该前缀。
 * 此外，若前缀末尾对应节点的 isEnd 为真，则说明字典树中存在该字符串。 
*/
class Trie {
private:
    vector<Trie*> children;
    bool isEnd;

    Trie* searchPrefix(string prefix) {
        //* 搜索和插入的一开始都要使指针指向根节点
        Trie* node = this;
        for (char ch : prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }

public:
    //* 注意这里的初始化
    Trie() : children(26), isEnd(false) {}

    void insert(string word) {
        //* 搜索和插入的一开始都要使指针指向根节点
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};

/*
 * 我的解法
 * 插入一个字符串时，
 * 用unordered_map存储字符串的所有前缀到字符串的映射，
 * 用unordered_set存储字符串本身。
 * 后续检查字符串是否存在时，用unordered_set。
 * 检查前缀是否存在时，用unordered_map。
 * 
 * 简单易懂，但速度非常慢
*/
class Trie {
private:
    unordered_map<string, vector<string>> pre;
    unordered_set<string> words;

public:
    Trie() {
        
    }
    
    void insert(string word) {
        words.insert(word);
        int len = word.size();
        for (int i = 1; i <= len; i++) {
            string tmp = word.substr(0, i);
            pre[tmp].push_back(word);
        }
    }
    
    bool search(string word) {
        if (words.count(word)) return true;
        else return false;
    }
    
    bool startsWith(string prefix) {
        if (pre.count(prefix)) return true;
        else return false;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end

