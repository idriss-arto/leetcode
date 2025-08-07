/*
 * @lc app=leetcode.cn id=146 lang=cpp
 * 链表
 ! [146] LRU 缓存
 */

/*
 * 思路：
 * 用一个哈希表和一个双向链表维护所有在 LRU缓存 中的键值对。
 * 双向链表按照被使用的顺序存储了这些键值对，靠近头部的键值对是最近使用的，而靠近尾部的键值对是最久未使用的。
 * 哈希表即为普通的哈希映射（HashMap），通过缓存数据的键映射到其在双向链表中的位置。
 * 以下为get和put操作的实现思路：
 * 
 * 
 * 对于 get 操作，首先判断 key 是否存在：
 * 1.
 * 如果 key 不存在，则返回 −1。
 * 2.
 * 如果 key 存在，则 key 对应的节点是最近被使用的节点。
 * 通过哈希表定位到该节点在双向链表中的位置，并将其移动到双向链表的头部，最后返回该节点的值。
 * 将一个节点移到双向链表的头部，可以分成「删除该节点」和「在双向链表的头部添加节点」两步操作。
 * 
 * 对于 put 操作，首先判断 key 是否存在：
 * 1.
 * 如果 key 不存在，使用 key 和 value 创建一个新的节点。
 * 在双向链表的头部添加该节点，并将 key 和该节点添加进哈希表中。
 ! 然后判断双向链表的节点数是否超出容量，如果超出容量，则删除双向链表的尾部节点，并删除哈希表中对应的项。
 * 2.
 * 如果 key 存在，则与 get 操作类似。
 * 先通过哈希表定位，再将对应的节点的值更新为 value，并将该节点移到双向链表的头部。
*/

// @lc code=start
#include <unordered_map>
using namespace std;

//* 官方题解，自己定义了一个双向链表
class LRUCache {
private:
//* 双向链表节点
struct DLinkedNode {
    int key_;
    int value_;
    DLinkedNode* prev;
    DLinkedNode* next;

    DLinkedNode(): key_(0), value_(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int key, int value): key_(key), value_(value), prev(nullptr), next(nullptr) {}
};

    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* dummyHead;
    DLinkedNode* dummyTail;
    int size;
    int capacity;

    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        size--;
    }

    void addToHead(DLinkedNode* node) {
        node->prev = dummyHead;
        node->next = dummyHead->next;
        dummyHead->next->prev = node;
        dummyHead->next = node;
        size++;
    }

    //* 这里返回节点是因为删除尾部节点时需要在哈希表中也删除对应的key
    DLinkedNode* removeTailNode() {
        DLinkedNode* node = dummyTail->prev;
        dummyTail->prev = node->prev;
        node->prev->next = dummyTail;
        size--;
        return node;
    }

public:
    LRUCache(int capacity_): capacity(capacity_), size(0) {
        dummyHead = new DLinkedNode();
        dummyTail = new DLinkedNode();
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        else {
            DLinkedNode* node = cache[key];
            removeNode(node);
            addToHead(node);
            return node->value_;
        }
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            //* 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            //* 添加至双向链表的头部
            addToHead(node);
            //* 添加进哈希表
            cache[key] = node;

            //* 判断是否超容
            if (size > capacity) {
                //* 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removedNode = removeTailNode();
                //* 删除哈希表中对应的项
                cache.erase(removedNode->key_);
                //* 防止内存泄漏
                delete removedNode;
            }
        }
        else {
            //* 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            removeNode(node);
            node->value_ = value;
            addToHead(node);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

