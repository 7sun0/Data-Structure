排队买票，先来的先买，后来的人只能站末尾，不允许插队，**先进者先出**
# 队列是什么
队列是**先进先出**的线性表，和栈一样，也是一种加了限制的线性表：
- 只允许在 **队尾（rear** 插入数据（入队）
- 只允许在 **队头（front** 删除数据（出队）
和栈刚好相反，但本质思路一模一样：限制操作位置，保证安全、减少出错。
核心操作（全 O (1)）
- EnQueue：入队（队尾加），类似于栈的入栈push()操作。
- DeQueue：出队（队头删），类似于栈的出栈pop()操作，不过需要注意是在前面一端出队，这与栈相反。
- GetFront：取队头元素。
- IsEmpty：判空。
- IsFull：仅顺序队列、循环队列需要。
# 顺序队列（数组实现）
用数组模拟队列，和顺序表的实现类似，front 指向队头前一位，rear 指向队尾，相当于顺序表中的last，存储数据总个数为rear-front。  
初始化：front = rear = -1，每入队rear+1，出队front+1，不难发现，front和rear都在不断+1，这会导致一个问题：**假溢出**：数组后面明明还有空间，但 rear 已经走到末尾，无法入队，这就是假溢出。
所以普通顺序队列基本不用，直接学循环队列。
# 循环队列
为了解决假溢出，把数组逻辑上变成环形，用 **取模 % MaxSize** 实现绕圈。（同时这也就说明，在循环链表的初始化中，rear和first应该初始化为0，因为取余数是没有-1的，所以在初始化上会有所差异）。缺点是**容量固定**。
## 通用规则（牺牲一个存储单元法，最常用，可以防止我们误判是队列满还是队列空）
- 初始化：front = rear = 0
- 判空：front == rear
- 判满：(rear + 1) % MaxSize == front
- 入队：rear = (rear + 1) % MaxSize
- 出队：front = (front + 1) % MaxSize
- 队长：(rear - front + MaxSize) % MaxSize
```cpp
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
```
# 链队列（链表实现）
和链表实现栈思路几乎一样，只是：
- 栈：头插法 + 头删法
- 队列：尾插法 + 头删法
同样的用带头结点设计，不用判满，不存在溢出，也避免二级指针，让代码更加简洁。（与链表实现栈和数组实现栈的区别类似）缺点是会**有指针开销**。
```cpp
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
```
# 阻塞队列
# 并发队列
# 队列典型应用
- 约瑟夫环问题（最经典）
- 二叉树层次遍历
- 操作系统进程排队、打印队列
- 消息队列、缓冲区
- 食堂排队、银行叫号模拟
# 总结
队列最大的特点就是**先进先出**，主要的两个操作是**入队**和**出队**。跟栈一样，它既可以用数组来实现，也可以用链表来实现。用数组实现的叫顺序队列，用链表实现的叫链式队列。特别是长得像一个环的循环队列。在数组实现队列的时候，会有数据搬移操作，要想解决**数据搬移**的问题，我们就需要像环一样的循环队列。