/*
 * @lc app=leetcode.cn id=146 lang=cpp
 * 链表
 ! [146] LRU 缓存
 */

// @lc code=start
#include <unordered_map>
using namespace std;

//* 官方题解，自己定义了一个双向链表
class LRUCache {
//* 双向链表节点
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* dummyHead;
    DLinkedNode* dummyTail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        //* 使用伪头部和伪尾部节点
        dummyHead = new DLinkedNode();
        dummyTail = new DLinkedNode();
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        //* 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            //* 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            //* 添加进哈希表
            cache[key] = node;
            //* 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                //* 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                //* 删除哈希表中对应的项
                cache.erase(removed->key);
                //* 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            //* 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = dummyHead;
        node->next = dummyHead->next;
        dummyHead->next->prev = node;
        dummyHead->next = node;
    }
    
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    //* 这里返回节点是因为删除尾部节点时需要在哈希表中也删除对应的key
    DLinkedNode* removeTail() {
        DLinkedNode* node = dummyTail->prev;
        removeNode(node);
        return node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

