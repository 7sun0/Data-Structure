#include <iostream>
using namespace std;

const int MAXN = 100;

struct Node {
    int data;
    int next;
} SLL[MAXN];

int head = -1;
int tot = 0;

// 尾插建立链表
void add(int val) {
    SLL[tot].data = val;
    SLL[tot].next = -1;
    if (head == -1) head = tot;
    else {
        int p = head;
        while (SLL[p].next != -1) p = SLL[p].next;
        SLL[p].next = tot;
    }
    tot++;
}

// 遍历
void print() {
    for (int p = head; p != -1; p = SLL[p].next)
        cout << SLL[p].data << " ";
    cout << endl;
}
// 在第 pos 个节点后面插入 val（pos从0开始）
void insert(int pos, int val) {
    // 1. 申请新节点
    SLL[tot].data = val;

    // 2. 找到要插入的位置
    int p = head;
    for (int i = 0; i < pos; ++i) {
        p = SLL[p].next;
    }

    // 3. 核心插入逻辑
    SLL[tot].next = SLL[p].next;
    SLL[p].next = tot;

    tot++;
}
// 删除第 pos 个节点（pos从0开始）
void del(int pos) {
    int p = head;

    // 如果删第一个节点
    if (pos == 0) {
        head = SLL[head].next;
        return;
    }

    // 找到 pos 的前一个节点
    for (int i = 0; i < pos - 1; ++i) {
        p = SLL[p].next;
    }

    // 核心删除逻辑
    int toDel = SLL[p].next;
    SLL[p].next = SLL[toDel].next;
}
int main() {
    add(10);
    add(20);
    add(30);
    print();           // 10 20 30

    insert(1, 25);
    print();           // 10 20 25 30

    del(2);
    print();           // 10 20 30
}