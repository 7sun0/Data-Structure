#include <iostream>
#define MaxSize 10
using namespace std;

struct CircleQueue {
    int data[MaxSize];
    int front, rear;
};
typedef CircleQueue* Queue;

// 创建队列
Queue CreateQueue() {
    Queue q = new CircleQueue;
    q->front = q->rear = 0;
    return q;
}

// 判空
bool IsEmpty(Queue q) {
    return q->front == q->rear;
}

// 判满
bool IsFull(Queue q) {
    return (q->rear + 1) % MaxSize == q->front;
}

// 入队
void EnQueue(Queue q, int val) {
    if (IsFull(q)) {
        cout << "队满" << endl;
        return;
    }
    q->data[q->rear] = val;
    q->rear = (q->rear + 1) % MaxSize;
}

// 出队
int DeQueue(Queue q) {
    if (IsEmpty(q)) {
        cout << "队空" << endl;
        return -1;
    }
    int val = q->data[q->front];
    q->front = (q->front + 1) % MaxSize;
    return val;
}

// 取队头
int GetFront(Queue q) {
    if (IsEmpty(q)) return -1;
    return q->data[q->front];
}

// 销毁队列
void DestroyQueue(Queue q) {
    delete q;
    q = NULL;
}