#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct LinkQueue {
    Node* front;  // 队头指针
    Node* rear;   // 队尾指针
};
typedef LinkQueue* Queue;

// 创建队列（带头结点）
Queue CreateQueue() {
    Queue q = new LinkQueue;
    Node* head = new Node;
    head->next = NULL;
    q->front = q->rear = head;
    return q;
}

// 判空
bool IsEmpty(Queue q) {
    return q->front == q->rear;
}

// 入队（尾插）
void EnQueue(Queue q, int val) {
    Node* s = new Node;
    s->data = val;
    s->next = NULL;
    q->rear->next = s;
    q->rear = s;
}

// 出队（头删）
int DeQueue(Queue q) {
    if (IsEmpty(q)) {
        cout << "队空" << endl;
        return -1;
    }
    Node* p = q->front->next;
    int val = p->data;
    q->front->next = p->next;

    // 如果最后一个节点出队，rear 要回指头结点
    if (q->rear == p)
        q->rear = q->front;

    delete p;
    return val;
}

// 取队头
int GetFront(Queue q) {
    if (IsEmpty(q)) return -1;
    return q->front->next->data;
}